//#include <NewPing.h>

//NewPing sonar(23, 22);

const int sensorPE = A11;
const int sensorE = A12;
const int sensorC = A13;
const int sensorD = A14;
const int sensorPD = A15;

int referencia = 200;
int sinalDireita = 0;
int sinalCentro = 0;
int sinalEsquerda = 0;
int sinalPEsquerda = 0;
int sinalPDireita = 0;

// MOTORES ÍMPARES = ESQUERDA; PARES = DIREITA
//motor 1
const int velocidadeA = 3; //motor frente esquerda
const int IN1 = 39;
const int IN2 = 38;

//motor 2
const int velocidadeB = 2;
const int IN3 = 41;
const int IN4 = 40;

//motor 3
const int velocidadeC = 13;
const int IN5 = 12;
const int IN6 = 11;

//motor 4
const int velocidadeD = 8;
const int IN7 = 10;
const int IN8 = 9;

//variavel auxiliar
const int vel = 40;

String message = "0";

const int LED = 13;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);

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
  pinMode(LED, OUTPUT);
}

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

void engineLoop() {
//  int distance = sonar.ping_cm();

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

//  if (distance < 15) {
//    parar();
//  } else {
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
//  }
}

void loop() {  
  if (Serial2.available()) {
    message = Serial2.readString();
  }

  if (message == "1") {
    digitalWrite(LED, HIGH);
    engineLoop();
  } else {
    digitalWrite(LED, LOW);
    parar();
  }
}

