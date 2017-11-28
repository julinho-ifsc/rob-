#include <NewPing.h>
#include <SPI.h>
#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <PubSubClient.h>

#define DEBUG true

NewPing sonar(23, 22);

const int BUZZER = 24;

const int sensorPE = A15;
const int sensorE = A14;
const int sensorC = A13;
const int sensorD = A12;
const int sensorPD = A11;

int referencia = 200;
int sinalDireita = 0;
int sinalCentro = 0;
int sinalEsquerda = 0;
int sinalPEsquerda = 0;
int sinalPDireita = 0;

// MOTORES ÍMPARES = ESQUERDA; PARES = DIREITA
//motor 1
const int velocidadeA = 6; //motor frente esquerda
const int IN1 = 48;
const int IN2 = 49;

//motor 2
const int velocidadeB = 7;
const int IN3 = 46;
const int IN4 = 47;

//motor 3
const int velocidadeC = 8;
const int IN5 = 9;
const int IN6 = 10;

//motor 4
const int velocidadeD = 13;
const int IN7 = 11;
const int IN8 = 12;

const int vel = 60;

char ssid[] = "julinho";
char pass[] = "123456789";

IPAddress server(191, 36, 8, 4);
const int PORT = 1883;

WiFiEspClient espClient;
PubSubClient mqttClient(espClient);

long lastReconnectAttempt = 0;

int status = WL_IDLE_STATUS;

boolean shouldWalk = false;

const char stopTopic[] = "julinho/parar";
const char walkTopic[] = "julinho/andar";

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println();

  String str = "";
  for (int i = 0; i < length; i++) {
    str += (char) payload[i];
  }
  
  if (str == "1") {
    shouldWalk = true;
  } else {
    shouldWalk = false;
  }
  Serial.println(str);
  Serial.println(shouldWalk);
}

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);

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


  pinMode(BUZZER, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);
  pinMode(velocidadeA, OUTPUT);
  pinMode(velocidadeB, OUTPUT);
  pinMode(velocidadeC, OUTPUT);
  pinMode(velocidadeD, OUTPUT);
}

boolean reconnect() {
  if (mqttClient.connect("arduinoClient")) {
    Serial.println("connected");
//    mqttClient.subscribe(stopTopic);
    mqttClient.subscribe(walkTopic);
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


void motor1(int velocity, int rotation1, int rotation2) { //motor1(100,1,0)
  digitalWrite(IN1, rotation1);
  digitalWrite(IN2, rotation2);
  analogWrite(velocidadeA, velocity);
}

void motor2(int velocity, int rotation1, int rotation2) {
  digitalWrite(IN3, rotation1);
  digitalWrite(IN4, rotation2);
  analogWrite(velocidadeB, velocity);
}

void motor3(int velocity, int rotation1, int rotation2) {
  digitalWrite(IN5, rotation1);
  digitalWrite(IN6, rotation2);
  analogWrite(velocidadeC, velocity);
}

void motor4(int velocity, int rotation1, int rotation2) {
  digitalWrite(IN7, rotation1);
  digitalWrite(IN8, rotation2);
  analogWrite(velocidadeD, velocity);
}

void frente() {
  motor1(vel, HIGH, LOW);
  motor2(vel, HIGH, LOW);
  motor3(vel, HIGH, LOW);
  motor4(vel, HIGH, LOW);
}

void direita1() {
  motor1(vel, HIGH, LOW);
  motor2(vel*0.7, HIGH, LOW);
  motor3(vel, HIGH, LOW);
  motor4(vel*0.7, HIGH, LOW);
}

void direita2() {
  motor1(vel, HIGH, LOW);
  motor2(vel*0.6, HIGH, LOW);
  motor3(vel, HIGH, LOW);
  motor4(vel*0.6, HIGH, LOW);
}

void direita3() {
  motor1(vel*0.9, HIGH, LOW);
  motor2(vel*0.7, HIGH, LOW);
  motor3(vel*0.9, HIGH, LOW);
  motor4(vel*0.7, HIGH, LOW);
}

void direita4() {
  motor1(vel*1, HIGH, LOW);
  motor2(vel*0.5, LOW, HIGH);
  motor3(vel*1, HIGH, LOW);
  motor4(vel*0.5, LOW, HIGH);
}

void esquerda1() {
  motor1(vel*0.7, HIGH, LOW);
  motor2(vel, HIGH, LOW);
  motor3(vel*0.7, HIGH, LOW);
  motor4(vel, HIGH, LOW);
}

void esquerda2() {
  motor1(vel*0.6, HIGH, LOW);
  motor2(vel, HIGH, LOW);
  motor3(vel*0.6, HIGH, LOW);
  motor4(vel, HIGH, LOW);
}

void esquerda3() {
  motor1(vel*0.7, HIGH, LOW);
  motor2(vel*0.9, HIGH, LOW);
  motor3(vel*0.7, HIGH, LOW);
  motor4(vel*0.9, HIGH, LOW);
}

void esquerda4() {
  motor1(vel*0.5, LOW, HIGH);
  motor2(vel*1, HIGH, LOW);
  motor3(vel*0.5, LOW, HIGH);
  motor4(vel*1, HIGH, LOW);
}

void parar() {
  motor1(vel, HIGH, HIGH);
  motor2(vel, HIGH, HIGH);
  motor3(vel, HIGH, HIGH);
  motor4(vel, HIGH, HIGH);
}

void loopEngine() {
  float distance = sonar.ping_cm();

  sinalEsquerda = analogRead(sensorE);
  sinalCentro = analogRead(sensorC);
  sinalDireita = analogRead(sensorD);
  sinalPEsquerda = analogRead(sensorPE);
  sinalPDireita = analogRead(sensorPD);

  boolean sinalPEsquerdaIsActive = sinalPEsquerda < referencia;
  boolean sinalEsquerdaIsActive = sinalEsquerda < referencia;
  boolean sinalCentroIsActive = sinalCentro < referencia;
  boolean sinalDireitaIsActive = sinalDireita < referencia;
  boolean sinalPDireitaIsActive = sinalPDireita < referencia;

  if (distance < 15) {
    parar();
  } else {
    if (sinalPEsquerdaIsActive && sinalEsquerdaIsActive && sinalCentroIsActive && sinalDireitaIsActive && sinalPDireitaIsActive) { //ok
      frente();
    } else if (!sinalEsquerdaIsActive && sinalEsquerdaIsActive && sinalCentroIsActive && sinalDireitaIsActive && sinalPDireitaIsActive) { //ok
      direita1();
    } else if (sinalPEsquerdaIsActive && sinalEsquerdaIsActive && sinalCentroIsActive && sinalDireitaIsActive && !sinalPDireitaIsActive) { //ok
      esquerda1();
    } else if (!sinalPEsquerdaIsActive && !sinalEsquerdaIsActive && sinalCentroIsActive && sinalDireitaIsActive && sinalPDireitaIsActive) { //ok
      direita2();
    } else if (sinalPEsquerdaIsActive && sinalEsquerdaIsActive && sinalCentroIsActive && !sinalDireitaIsActive && !sinalPDireitaIsActive) { //ok
      esquerda2();
    } else if (!sinalPEsquerdaIsActive && sinalEsquerdaIsActive && sinalCentroIsActive && sinalDireitaIsActive && !sinalPDireitaIsActive) { //ok
      frente();
    } else if (!sinalPEsquerdaIsActive && !sinalEsquerdaIsActive && !sinalCentroIsActive && sinalDireitaIsActive && sinalPDireitaIsActive) { //ok
      direita2();
    } else if (!sinalPEsquerdaIsActive && !sinalEsquerdaIsActive && sinalCentroIsActive && sinalDireitaIsActive && !sinalPDireitaIsActive) { //ok
      direita2();
    } else if (!sinalPEsquerdaIsActive && sinalEsquerdaIsActive && sinalCentroIsActive && !sinalDireitaIsActive && !sinalPDireitaIsActive) { //ok
      esquerda2();
    } else if (sinalPEsquerdaIsActive && sinalEsquerdaIsActive && !sinalCentroIsActive && !sinalDireitaIsActive && !sinalPDireitaIsActive) { // ok
      esquerda2();
    } else if (sinalPEsquerdaIsActive && !sinalEsquerdaIsActive && !sinalCentroIsActive && !sinalDireitaIsActive && !sinalPDireitaIsActive) { // ok
      esquerda4();
    } else if (!sinalPEsquerdaIsActive && sinalEsquerdaIsActive && !sinalCentroIsActive && !sinalDireitaIsActive && !sinalPDireitaIsActive) { // ok
      esquerda2();
    } else if (!sinalPEsquerdaIsActive && !sinalEsquerdaIsActive && sinalCentroIsActive && !sinalDireitaIsActive && !sinalPDireitaIsActive) { // ok
      frente();
    } else if (!sinalPEsquerdaIsActive && !sinalEsquerdaIsActive && !sinalCentroIsActive && sinalDireitaIsActive && !sinalPDireitaIsActive) { // ok
      direita2();
    } else if (!sinalPEsquerdaIsActive && !sinalEsquerdaIsActive && !sinalCentroIsActive && !sinalDireitaIsActive && sinalPDireitaIsActive) { // ok
      direita4();
    } else {
      parar();
    }
  }
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

  delay(100);
  mqttCli\ent.loop();

  if (shouldWalk) {
    loopEngine();
  }
}
