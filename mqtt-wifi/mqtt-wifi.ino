/*
Código baseado em:
- https://github.com/knolleary/pubsubclient/blob/master/examples/mqtt_esp8266/mqtt_esp8266.ino
- https://github.com/knolleary/pubsubclient/blob/master/examples/mqtt_reconnect_nonblocking/mqtt_reconnect_nonblocking.ino
- https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/ESP8266WiFi.h
*/

#include <SPI.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "julinho";
const char* password = "123456789";
const char* mqtt_server = "nuvem2.sj.ifsc.edu.br";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi conectado!");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

boolean reconnect() {
  if (client.connect("julinho")) {
    Serial.println("conectado ao broker!");
    client.publish("arduino/check","1");
    client.subscribe("arduino/rota");
  }
  return client.connected();
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Messagem recebida [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// Timestamp da última (re)conexão WiFi
long lastReconnectAttempt = 0;

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  lastReconnectAttempt = 0;
}

void loop() {
  // WiFi?
  if (WiFi.status() != WL_CONNECTED) {
    setup_wifi();
  } else {
    // MQTT?
    if (!client.connected()) {
      long now = millis();
      // Intervalo de 5s para reconexão WiFi
      if (now - lastReconnectAttempt > 5000) {
        lastReconnectAttempt = now;
        if (reconnect()) {
          lastReconnectAttempt = 0;
        }
      }
    } else {
      // WiFi + MQTT
      client.loop();
    }
  }

}
