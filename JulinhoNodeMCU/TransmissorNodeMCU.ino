#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "julinho";
const char* password = "123456789";
const char* mqtt_server = "nuvem2.sj.ifsc.edu.br";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

long lastReconnectAttempt = 0;
String message = "";

SoftwareSerial wifiSerial(D7, D8);

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
    mqttClient.publish("julinho/enable", "1");
    mqttClient.publish("julinho/sos", "0");
    mqttClient.subscribe("julinho/rota");
  }
  return mqttClient.connected();
}

void setup() {
  Serial.begin(115200);
  wifiSerial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("not connected");
    delay(500);
  }

  Serial.println("connected");
  
  
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

  if (wifiSerial.available()) {
    Serial.println("check");
    String messageCheck = wifiSerial.readString();
    Serial.println(messageCheck);
    char check[messageCheck.length()];
    messageCheck.toCharArray(check, messageCheck.length());
    mqttClient.publish("julinho/check", check);
  }

  boolean routeExists = message.compareTo("") != 0;

  if (!routeExists) {
    delay(100);
    mqttClient.loop();
    return;
  }
  
  wifiSerial.print(message);
  Serial.println(message);
  message = "";

  delay(2000);
}

