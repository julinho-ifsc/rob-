#include <SPI.h>
#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <PubSubClient.h>
#include <MFRC522.h>

#define DEBUG true

char ssid[] = "julinho";
char pass[] = "123456789";

IPAddress server(191,36,8,4); 
int PORT = 1883;

WiFiEspClient espClient;
PubSubClient mqttClient(espClient);

constexpr uint8_t RST_PIN = 5;
constexpr uint8_t SS_PIN = 53;

MFRC522 mfrc522(SS_PIN, RST_PIN);

char message_buff[10];

long lastReconnectAttempt = 0;

int status = WL_IDLE_STATUS;

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

  Serial.println("Hello World");

  Serial.println("Configurando RFID");
  mfrc522.PCD_Init();
  Serial.println("Feito");

  Serial.println("- Configurando modulo...");
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG); // modo de operação STA
  Serial.println("- Resetando modulo...");
  sendData("AT+RST\r\n", 1000, DEBUG); // resetar módulo
  Serial.println("- Conectando no roteador");
  sendData("AT+CWJAP=\"julinho\",\"123456789\"\r\n", 5000, DEBUG); // conectar na rede wifi
  WiFi.init(&Serial1);

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);

    status = WiFi.begin(ssid, pass);
  }

  Serial.println("You're connected to the network");

  mqttClient.setServer(server, PORT);
  mqttClient.setCallback(callback);
}

boolean reconnect() {
  if (mqttClient.connect("arduinoClient")) {
    Serial.println("connected");
    mqttClient.publish("julinho/enable","1");
    mqttClient.publish("julinho/sos","0");
    mqttClient.subscribe("julinho/rota");
  }
  return mqttClient.connected();
}

String sendData(const char* command, const int timeout, boolean debug) {
  String response = "";
  Serial1.print(command); // send the read character to the esp8266
  long int time = millis();
  
  while ( (time + timeout) > millis()) {
    while (Serial1.available()) {
      // The esp has data so display its output to the serial window
      char c = Serial1.read(); // read the next character.
      response += c;
    }
  }
  return response;
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
  } else {
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
}
