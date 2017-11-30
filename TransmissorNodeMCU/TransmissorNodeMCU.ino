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
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println();

  Serial.print("Length: ");
  Serial.print(length);
  Serial.println();

  message = "";
  for (int i = 0; i < length; i++) {
    message += (char) payload[i];
  }
  message.toLowerCase();
  message.trim();
}

boolean reconnect() {
  if (mqttClient.connect("arduinoClient")) {
    Serial.println("connected");
    mqttClient.publish("julinho/enable", "1");
    mqttClient.publish("julinho/sos", "0");
    mqttClient.subscribe("julinho/rota");
  }
  return mqttClient.connected();
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
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

  boolean routeExists = message.compareTo("") != 0;

  if (!routeExists) {
    delay(100);
    mqttClient.loop();
    return;
  }
  
  Serial1.print(message);
  Serial.println(message);
  message = "";

  delay(2000);
}

