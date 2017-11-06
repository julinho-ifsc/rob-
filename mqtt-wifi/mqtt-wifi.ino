#include <SPI.h>
#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <PubSubClient.h>
#include <MFRC522.h>

#define DEBUG true

#define SSID "julinho"
#define PASSWORD "123456789"

IPAddress server(191,36,8,24); 
int PORT = 1883;

WiFiEspClient espClient;
PubSubClient mqttClient(espClient);

constexpr uint8_t RST_PIN = 5;
constexpr uint8_t SS_PIN = 53;

MFRC522 mfrc522(SS_PIN, RST_PIN);

char message_buff[10];

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println();

  Serial.print("Length: ");
  Serial.print(length);
  Serial.println();
  
  for (int i = 0; i < length; i++) {
    Serial.print((char) payload[i]);
  }
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
  SPI.begin();

  Serial.println("Configurando RFID");
  mfrc522.PCD_Init();
  Serial.println("Feito");

  WiFi.init(&Serial1);

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }

  WiFi.begin(SSID, PASSWORD);


  Serial.println("You're connected to the network");

  mqttClient.setServer(server, PORT);
  mqttClient.setCallback(callback);
}


void reconnect() {
  while (!mqttClient.connected()) {
    Serial.println("Attempting MQTT connection...");

    // Attempt to connect, just a name to identify the client
    if (mqttClient.connect("arduinoClient")) {
      Serial.println("connected");
      mqttClient.publish("julinho/enable","1");
      mqttClient.publish("julinho/sos","0");
      mqttClient.subscribe("julinho/rota", 1);
    } else {
      Serial.print("failed, rc = ");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");

      delay(5000);
    }
  }
}

void loop() {
  // NÃO APAGAR - Delay para não obstruir serial
  delay(100);

  if (!mqttClient.connected()) {
    reconnect();
  }

  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    mqttClient.loop();
    return;
  }

  String rfidUid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    rfidUid += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    rfidUid += String(mfrc522.uid.uidByte[i], HEX);
  }
  
  if (rfidUid == message_buff) {
    mqttClient.loop();
    return;    
  }

  rfidUid.toCharArray(message_buff, rfidUid.length() + 1);
  mqttClient.publish("julinho/check", message_buff);
  Serial.println("Message sended: ");
  Serial.println(message_buff);
}
