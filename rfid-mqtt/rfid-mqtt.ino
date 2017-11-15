// Carrega as bibliotecas
#include <SPI.h>
#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <PubSubClient.h>
#include <MFRC522.h>

#define DEBUG true

// WIFI
#define SSID "julinho"
#define PASSWORD "123456789"

// MQTT
IPAddress server(191, 36, 8, 24); //Servidor
int PORT = 1883;

//RFID

constexpr uint8_t RST_PIN = 5;
constexpr uint8_t SS_PIN = 53;

MFRC522 mfrc522(SS_PIN, RST_PIN);

int status = WL_IDLE_STATUS;   // the Wifi radio's status

// Initialize the client object and MQTT
WiFiEspClient espClient;
PubSubClient mqttClient(espClient);

//Variáveis auxiliares MQTT
char message_buff[100];
const char* topico = "julinho/rota";

//TESTE CORTE DE MENSAGENS
char ROTA = "";
//String ROTA = "";
//String serialResponse = "";
//

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
  SPI.begin();

  //RFID
  Serial.println("Configurando RFID");
  mfrc522.PCD_Init();
  Serial.println("Feito");

  Serial.println("- Configurando modulo...");
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG); // modo de operação STA
  Serial.println("- Resetando modulo...");
  sendData("AT+RST\r\n", 1000, DEBUG); // resetar módulo
  Serial.println("- Conectando no roteador");
  sendData("AT+CWJAP=\"julinho\",\"123456789\"\r\n", 5000, DEBUG); // conectar na rede wifi

  // initialize ESP module
  WiFi.init(&Serial1);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(SSID);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(SSID, PASSWORD);
  }

  // you're connected now, so print out the data
  Serial.println("You're connected to the network");

  //connect to MQTT server
  mqttClient.setServer(server, PORT);
  mqttClient.setCallback(callback);

//TESTE CORTE DE MENSAGENS
//   char *p = ROTA;
//   char *str;
//   while ((str = strtok_r(p, ";", &p)) != NULL) // delimiter is the semicolon
//   Serial.println(str);
//
}

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println();
  for (int i = 0; i < length; i++) {
    ROTA = ((char)payload[i]);
    Serial.print(ROTA);

  }
  Serial.println();
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
  if (debug) {
    Serial.println(response.c_str());
  }
  return response;
}

void reconnect() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    Serial.println("Attempting MQTT connection...");
    // Attempt to connect, just a name to identify the client
    if (mqttClient.connect("arduinoClient")) {
      Serial.println("connected");
      mqttClient.publish("julinho/enable", "1");
      mqttClient.publish("julinho/sos", "0");
      mqttClient.subscribe(topico, 1);
    }
    else {
      Serial.print("failed, rc = ");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
  //TESTE CORTE DE MENSAGENS
//  if ( Serial.available()) {
//     serialResponse = Serial.readStringUntil('\r\n');
//     Serial.println(serialResponse);
//     }
//

  //  Procura tags;
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
     }

  //  Lê a tag
  if ( ! mfrc522.PICC_ReadCardSerial());
  String rfidUid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    rfidUid += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    rfidUid += String(mfrc522.uid.uidByte[i], HEX);
  }

  // put your main code here, to run repeatedly:
  if (!mqttClient.connected()) {
    reconnect();
  }
  else {
    if (rfidUid == message_buff) {
      mqttClient.loop();
      return;
    }
    else {
      rfidUid.toCharArray(message_buff, rfidUid.length() + 1);
      mqttClient.publish("julinho/check", message_buff);
      Serial.println("Message sended: ");
      Serial.println(message_buff);
    }

  }

}
