#include <EngineControl.h>
#include <Arduino.h>

EngineControl::EngineControl(int velocity, int reference) {
  _velocidade = velocity;
  _referencia = reference;
}

void EngineControl::motor1(int velocity, int rotation1, int rotation2) {
  digitalWrite(_frontLeftPins.rotation1, rotation1);
  digitalWrite(_frontLeftPins.rotation2, rotation2);
  analogWrite(_frontLeftPins.velocity, velocity);
}

void EngineControl::motor2(int velocity, int rotation1, int rotation2) {
  digitalWrite(_frontRightPins.rotation1, rotation1);
  digitalWrite(_frontRightPins.rotation2, rotation2);
  analogWrite(_frontRightPins.velocity, velocity);
}

void EngineControl::motor3(int velocity, int rotation1, int rotation2) {
  digitalWrite(_backLeftPins.rotation1, rotation1);
  digitalWrite(_backLeftPins.rotation2, rotation2);
  analogWrite(_backLeftPins.velocity, velocity);
}

void EngineControl::motor4(int velocity, int rotation1, int rotation2) {
  digitalWrite(_backRightPins.rotation1, rotation1);
  digitalWrite(_backRightPins.rotation2, rotation2);
  analogWrite(_backRightPins.velocity, velocity);
}

void EngineControl::frente() {
  motor1(_velocidade, HIGH, LOW);
  motor2(_velocidade, HIGH, LOW);
  motor3(_velocidade, HIGH, LOW);
  motor4(_velocidade, HIGH, LOW);
}

void EngineControl::direita1() {
  motor1(_velocidade, HIGH, LOW);
  motor2(_velocidade*0.7, HIGH, LOW);
  motor3(_velocidade, HIGH, LOW);
  motor4(_velocidade*0.7, HIGH, LOW);
}

void EngineControl::direita2() {
  motor1(_velocidade, HIGH, LOW);
  motor2(_velocidade*0.6, HIGH, LOW);
  motor3(_velocidade, HIGH, LOW);
  motor4(_velocidade*0.6, HIGH, LOW);
}

void EngineControl::direita3() {
  motor1(_velocidade*0.9, HIGH, LOW);
  motor2(_velocidade*0.7, HIGH, LOW);
  motor3(_velocidade*0.9, HIGH, LOW);
  motor4(_velocidade*0.7, HIGH, LOW);
}

void EngineControl::direita4() {
  motor1(_velocidade*1, HIGH, LOW);
  motor2(_velocidade*0.5, LOW, HIGH);
  motor3(_velocidade*1, HIGH, LOW);
  motor4(_velocidade*0.5, LOW, HIGH);
}

void EngineControl::esquerda1() {
  motor1(_velocidade*0.7, HIGH, LOW);
  motor2(_velocidade, HIGH, LOW);
  motor3(_velocidade*0.7, HIGH, LOW);
  motor4(_velocidade, HIGH, LOW);
}

void EngineControl::esquerda2() {
  motor1(_velocidade*0.6, HIGH, LOW);
  motor2(_velocidade, HIGH, LOW);
  motor3(_velocidade*0.6, HIGH, LOW);
  motor4(_velocidade, HIGH, LOW);
}

void EngineControl::esquerda3() {
  motor1(_velocidade*0.7, HIGH, LOW);
  motor2(_velocidade*0.9, HIGH, LOW);
  motor3(_velocidade*0.7, HIGH, LOW);
  motor4(_velocidade*0.9, HIGH, LOW);
}

void EngineControl::esquerda4() {
  motor1(_velocidade*0.5, LOW, HIGH);
  motor2(_velocidade*1, HIGH, LOW);
  motor3(_velocidade*0.5, LOW, HIGH);
  motor4(_velocidade*1, HIGH, LOW);
}

void EngineControl::parar() {
  motor1(_velocidade, HIGH, HIGH);
  motor2(_velocidade, HIGH, HIGH);
  motor3(_velocidade, HIGH, HIGH);
  motor4(_velocidade, HIGH, HIGH);
}

void EngineControl::loop() {
  int sinalEsquerda = analogRead(_sensorPins.sensorE);
  int sinalCentro = analogRead(_sensorPins.sensorC);
  int sinalDireita = analogRead(_sensorPins.sensorD);
  int sinalPEsquerda = analogRead(_sensorPins.sensorPE);
  int sinalPDireita = analogRead(_sensorPins.sensorPD);

  boolean sinalPEsquerdaIsActive = sinalPEsquerda < _referencia;
  boolean sinalEsquerdaIsActive = sinalEsquerda < _referencia;
  boolean sinalCentroIsActive = sinalCentro < _referencia;
  boolean sinalDireitaIsActive = sinalDireita < _referencia;
  boolean sinalPDireitaIsActive = sinalPDireita < _referencia;

  if (sinalPEsquerdaIsActive && sinalEsquerdaIsActive && sinalCentroIsActive && sinalDireitaIsActive && sinalPDireitaIsActive) {
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

void EngineControl::setFrontLeftPins(EnginePins enginePins) {
  _frontLeftPins = enginePins;
  pinMode(_frontLeftPins.rotation1, OUTPUT);
  pinMode(_frontLeftPins.rotation2, OUTPUT);
  pinMode(_frontLeftPins.velocity, OUTPUT);
}

void EngineControl::setFrontRightPins(EnginePins enginePins) {
  _frontRightPins = enginePins;
  pinMode(_frontRightPins.rotation1, OUTPUT);
  pinMode(_frontRightPins.rotation2, OUTPUT);
  pinMode(_frontRightPins.velocity, OUTPUT);
}

void EngineControl::setBackLeftPins(EnginePins enginePins) {
  _backLeftPins = enginePins;
  pinMode(_backLeftPins.rotation1, OUTPUT);
  pinMode(_backLeftPins.rotation2, OUTPUT);
  pinMode(_backLeftPins.velocity, OUTPUT);
}

void EngineControl::setBackRightPins(EnginePins enginePins) {
  _backRightPins = enginePins;
  pinMode(_backRightPins.rotation1, OUTPUT);
  pinMode(_backRightPins.rotation2, OUTPUT);
  pinMode(_backRightPins.velocity, OUTPUT);
}

void EngineControl::setSensorPins(SensorPins sensorPins) {
  _sensorPins = sensorPins;
}
