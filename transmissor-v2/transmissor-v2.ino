//#include <WiFiEsp.h>
//#include <WiFiEspClient.h>
//#include <PubSubClient.h>

//#define DEBUG true

//char ssid[] = "julinho";
//char pass[] = "123456789";

//String message = "";

//IPAddress server(191, 36, 8, 4);
//int PORT = 1883;

//WiFiEspClient espClient;
//PubSubClient mqttClient(espClient);

//long lastReconnectAttempt = 0;

//int status = WL_IDLE_STATUS;

//const int RED_LED = 10;
//const int GREEN_LED = 8;

//void callback(char* topic, byte* payload, unsigned int length) {
//  Serial.print("Message arrived [");
//  Serial.print(topic);
//  Serial.print("]: ");
//  Serial.println();
//
//  Serial.print("Length: ");
//  Serial.print(length);
//  Serial.println();
//
//  message = "";
//  for (int i = 0; i < length; i++) {
//    message += (char) payload[i];
//  }
//  message.toLowerCase();
//  message.trim();
//}

void setup() {
  Serial.begin(9600);
//  Serial1.begin(115200);
  Serial2.begin(9600);

//  Serial.println("- Configurando modulo...");
//  sendData("AT+CWMODE=1\r\n", 1000, DEBUG); // modo de operação STA
//  Serial.println("- Resetando modulo...");
//  sendData("AT+RST\r\n", 1000, DEBUG); // resetar módulo
//  Serial.println("- Conectando no roteador");
//  sendData("AT+CWJAP=\"julinho\",\"123456789\"\r\n", 5000, DEBUG); // conectar na rede wifi
//  WiFi.init(&Serial1);

//  if (WiFi.status() == WL_NO_SHIELD) {
//    Serial.println("WiFi shield not present");
//    while (true);
//  }
//
//  while (status != WL_CONNECTED) {
//    Serial.print("Attempting to connect to WPA SSID: ");
//    Serial.println(ssid);
//
//    status = WiFi.begin(ssid, pass);
//  }
//
//  Serial.println("You're connected to the network");
//
//  mqttClient.setServer(server, PORT);
//  mqttClient.setCallback(callback);
//
//  pinMode(RED_LED, OUTPUT);
//  pinMode(GREEN_LED, OUTPUT);
//}

//boolean reconnect() {
//  if (mqttClient.connect("arduinoClient")) {
//    Serial.println("connected");
//    mqttClient.publish("julinho/enable", "1");
//    mqttClient.publish("julinho/sos", "0");
//    mqttClient.subscribe("julinho/rota");
//  }
//  return mqttClient.connected();
//}

//String sendData(const char* command, const int timeout, boolean debug) {
//  String response = "";
//  Serial1.print(command); // send the read character to the esp8266
//  long int time = millis();
//
//  while ( (time + timeout) > millis()) {
//    while (Serial1.available()) {
//      // The esp has data so display its message to the serial window
//      char c = Serial1.read(); // read the next character.
//      response += c;
//    }
//  }
//  return response;
}

void loop() {
  
//  if (!mqttClient.connected()) {
//    long now = millis();
//    if (now - lastReconnectAttempt > 5000) {
//      lastReconnectAttempt = now;
//      if (reconnect()) {
//        lastReconnectAttempt = 0;
//      }
//    }
//    return;
//  }

//  boolean routeExists = message.compareTo("") != 0;

//  if (!routeExists) {
//    delay(100);
//    mqttClient.loop();
//    return;
//  }
  
  Serial2.print("bc521a14-e;d2f7e4d4-d");
  delay(3000);
//  Serial.println(message);
//  message = "";

}

