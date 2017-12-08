#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "julinho";
const char* password = "123456789";
const char* mqtt_server = "nuvem2.sj.ifsc.edu.br";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

long lastReconnectAttempt = 0;
String message = "";

void callback(char* topic, byte* payload, unsigned int length) {
  message = "";
  for (int i = 0; i < length; i++) {
    message += (char) payload[i];
  }
  message.toLowerCase();
  message.trim();
}

boolean reconnect() {
  if (mqttClient.connect("arduinoClient")) {
    mqttClient.publish("julinha/enable", "1");
    mqttClient.publish("julinha/sos", "0");
    mqttClient.subscribe("julinha/rota");
  }
  return mqttClient.connected();
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  mqttClient.setServer(mqtt_server, 1883);
  mqttClient.setCallback(callback);
}

void loop() {
  if (!mqttClient.connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
    return;
  }

  if (Serial.available()) {
    String messageCheck = Serial.readString();
    char check[messageCheck.length()];
    messageCheck.toCharArray(check, messageCheck.length());
    mqttClient.publish("julinha/check", check);
  }

  boolean routeExists = message.compareTo("") != 0;

  if (!routeExists) {
    delay(100);
    mqttClient.loop();
    return;
  }
  
  Serial.print(message);
  message = "";

  delay(2000);
}

