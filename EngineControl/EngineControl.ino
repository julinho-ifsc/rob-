#include <NewPing.h>

struct EnginePins {
  int velocity;
  int rotation1;
  int rotation2;
};

const int PIN_BUZZER = 24;
const int PIN_LEFT_END_SENSOR = A15;
const int PIN_LEFT_SENSOR = A14;
const int PIN_CENTER_SENSOR = A13;
const int PIN_RIGHT_SENSOR = A12;
const int PIN_RIGHT_END_SENSOR = A11;

const EnginePins FRONT_LEFT_ENGINE_PINS = {7, 35, 36};
const EnginePins FRONT_RIGHT_ENGINE_PINS = {6, 37, 38};
const EnginePins BACK_LEFT_ENGINE_PINS = {8, 9, 10};
const EnginePins BACK_RIGHT_ENGINE_PINS = {13, 11, 12};

const int SENSOR_REFERENCE_VALUE = 200;
const int BASE_VELOCITY = 75;

const float TINY_FACTOR = 0.4;
const float SMALL_FACTOR = 0.7;
const float MEDIUM_FACTOR = 0.9;
const float NORMAL_FACTOR = 1.0;

NewPing sonar(23, 22);

void setup() {
  Serial.begin(9600);

  pinMode(BUZZER, OUTPUT);
  pinMode(FRONT_LEFT_ENGINE_PINS.rotation1, OUTPUT);
  pinMode(FRONT_LEFT_ENGINE_PINS.rotation2, OUTPUT);
  pinMode(FRONT_RIGHT_ENGINE_PINS.rotation1, OUTPUT);
  pinMode(FRONT_RIGHT_ENGINE_PINS.rotation2, OUTPUT);
  pinMode(BACK_LEFT_ENGINE_PINS.rotation2, OUTPUT);
  pinMode(BACK_LEFT_ENGINE_PINS.rotation2, OUTPUT);
  pinMode(BACK_RIGHT_ENGINE_PINS.rotation1, OUTPUT);
  pinMode(BACK_RIGHT_ENGINE_PINS.rotation2, OUTPUT);
  pinMode(FRONT_RIGHT_ENGINE_PINS.velocity, OUTPUT);
  pinMode(BACK_LEFT_ENGINE_PINS.velocity, OUTPUT);
  pinMode(BACK_RIGHT_ENGINE_PINS.velocity, OUTPUT);
}

void frontLeftEngine(int velocity, int rotation1, int rotation2) {
  digitalWrite(FRONT_LEFT_ENGINE_PINS.rotation1, rotation1);
  digitalWrite(FRONT_LEFT_ENGINE_PINS.rotation2, rotation2);
  digitalWrite(FRONT_LEFT_ENGINE_PINS.velocity, rotation2);
}

void frontRightEngine(int velocity, int rotation1, int rotation2) {
  digitalWrite(FRONT_RIGHT_ENGINE_PINS.rotation1, rotation1);
  digitalWrite(FRONT_RIGHT_ENGINE_PINS.rotation2, rotation2);
  analogWrite(FRONT_RIGHT_ENGINE_PINS.velocity, velocity);
}

void backLeftEngine(int velocity, int rotation1, int rotation2) {
  digitalWrite(BACK_LEFT_ENGINE_PINS.rotation2, rotation1);
  digitalWrite(BACK_LEFT_ENGINE_PINS.rotation2, rotation2);
  analogWrite(BACK_LEFT_ENGINE_PINS.velocity, velocity);
}

void backRightEngine(int velocity, int rotation1, int rotation2) {
  digitalWrite(BACK_RIGHT_ENGINE_PINS.rotation1, rotation1);
  digitalWrite(BACK_RIGHT_ENGINE_PINS.rotation2, rotation2);
  analogWrite(BACK_RIGHT_ENGINE_PINS.velocity, velocity);
}

void forward() {
  frontLeftEngine(BASE_VELOCITY, HIGH, LOW);
  frontRightEngine(BASE_VELOCITY, HIGH, LOW);
  backLeftEngine(BASE_VELOCITY, HIGH, LOW);
  backRightEngine(BASE_VELOCITY, HIGH, LOW);
}

void turnRight(float factor) {
  frontLeftEngine(BASE_VELOCITY, HIGH, LOW);
  frontRightEngine(BASE_VELOCITY * factor, HIGH, LOW);
  backLeftEngine(BASE_VELOCITY, HIGH, LOW);
  backRightEngine(BASE_VELOCITY * factor, HIGH, LOW);
}

void turnLeft(float factor) {
  frontLeftEngine(BASE_VELOCITY * factor, LOW, HIGH);
  frontRightEngine(BASE_VELOCITY, HIGH, LOW);
  backLeftEngine(BASE_VELOCITY * factor, LOW, HIGH);
  backRightEngine(BASE_VELOCITY, HIGH, LOW);
}

void stop() {
  digitalWrite(FRONT_LEFT_ENGINE_PINS.rotation1, HIGH);
  digitalWrite(FRONT_LEFT_ENGINE_PINS.rotation2, HIGH);

  digitalWrite(FRONT_RIGHT_ENGINE_PINS.rotation1, HIGH);
  digitalWrite(FRONT_RIGHT_ENGINE_PINS.rotation2, HIGH);

  digitalWrite(BACK_LEFT_ENGINE_PINS.rotation2, HIGH);
  digitalWrite(BACK_LEFT_ENGINE_PINS.rotation2, HIGH);

  digitalWrite(BACK_RIGHT_ENGINE_PINS.rotation1, HIGH);
  digitalWrite(BACK_RIGHT_ENGINE_PINS.rotation2, HIGH);
}

void loop() {
  float distance = sonar.ping_cm();
  int sinalEsquerda = analogRead(PIN_LEFT_SENSOR);
  int sinalCentro = analogRead(PIN_CENTER_SENSOR);
  int sinalDireita = analogRead(PIN_RIGHT_SENSOR);
  int sinalPEsquerda = analogRead(PIN_LEFT_END_SENSOR);
  int sinalPDireita = analogRead(PIN_RIGHT_END_SENSOR);

  Serial.print("Distancia: ");
  Serial.println(distance);
  Serial.print("Nivel Ponta Esquerda: ");
  Serial.println(sinalPEsquerda);
  Serial.print("Nivel Esquerda: ");
  Serial.println(sinalEsquerda);
  Serial.print("Nivel Centro: ");
  Serial.println(sinalCentro);
  Serial.print("Nivel Direita: ");
  Serial.println(sinalDireita);
  Serial.print("Nivel Ponta Direita: ");
  Serial.println(sinalPDireita);
  Serial.println("");

  if (distance < 15) {
    stop();
    return;
  }

  if (sinalPEsquerda < SENSOR_REFERENCE_VALUE && sinalEsquerda < SENSOR_REFERENCE_VALUE && sinalCentro < SENSOR_REFERENCE_VALUE && sinalDireita < SENSOR_REFERENCE_VALUE && sinalPDireita < SENSOR_REFERENCE_VALUE) {
    forward();
  } else if (sinalPEsquerda > SENSOR_REFERENCE_VALUE && sinalEsquerda < SENSOR_REFERENCE_VALUE && sinalCentro < SENSOR_REFERENCE_VALUE && sinalDireita < SENSOR_REFERENCE_VALUE && sinalPDireita < SENSOR_REFERENCE_VALUE) {
    turnRight(MEDIUM_FACTOR);
  } else if (sinalPEsquerda < SENSOR_REFERENCE_VALUE && sinalEsquerda < SENSOR_REFERENCE_VALUE && sinalCentro < SENSOR_REFERENCE_VALUE && sinalDireita < SENSOR_REFERENCE_VALUE && sinalPDireita > SENSOR_REFERENCE_VALUE) {
    turnLeft(MEDIUM_FACTOR);
  } else if (sinalPEsquerda > SENSOR_REFERENCE_VALUE && sinalEsquerda < SENSOR_REFERENCE_VALUE && sinalCentro < SENSOR_REFERENCE_VALUE && sinalDireita < SENSOR_REFERENCE_VALUE && sinalPDireita < SENSOR_REFERENCE_VALUE) {
    turnRight(SMALL_FACTOR);
  } else if (sinalPEsquerda < SENSOR_REFERENCE_VALUE && sinalEsquerda < SENSOR_REFERENCE_VALUE && sinalCentro < SENSOR_REFERENCE_VALUE && sinalDireita > SENSOR_REFERENCE_VALUE && sinalPDireita > SENSOR_REFERENCE_VALUE) {
    turnLeft(SMALL_FACTOR);
  } else if (sinalPEsquerda > SENSOR_REFERENCE_VALUE && sinalEsquerda < SENSOR_REFERENCE_VALUE && sinalCentro < SENSOR_REFERENCE_VALUE && sinalDireita < SENSOR_REFERENCE_VALUE && sinalPDireita > SENSOR_REFERENCE_VALUE) {
    forward();
  } else if (sinalPEsquerda > SENSOR_REFERENCE_VALUE && sinalEsquerda > SENSOR_REFERENCE_VALUE && sinalCentro > SENSOR_REFERENCE_VALUE && sinalDireita < SENSOR_REFERENCE_VALUE && sinalPDireita < SENSOR_REFERENCE_VALUE) {
    turnRight(TINY_FACTOR);
  } else if (sinalPEsquerda > SENSOR_REFERENCE_VALUE && sinalEsquerda > SENSOR_REFERENCE_VALUE && sinalCentro < SENSOR_REFERENCE_VALUE && sinalDireita < SENSOR_REFERENCE_VALUE && sinalPDireita > SENSOR_REFERENCE_VALUE) {
    turnLeft(MEDIUM_FACTOR);
  } else if (sinalPEsquerda > SENSOR_REFERENCE_VALUE && sinalEsquerda < SENSOR_REFERENCE_VALUE && sinalCentro < SENSOR_REFERENCE_VALUE && sinalDireita > SENSOR_REFERENCE_VALUE && sinalPDireita > SENSOR_REFERENCE_VALUE) {
    turnRight(MEDIUM_FACTOR);
  } else if (sinalPEsquerda < SENSOR_REFERENCE_VALUE && sinalEsquerda < SENSOR_REFERENCE_VALUE && sinalCentro > SENSOR_REFERENCE_VALUE && sinalDireita > SENSOR_REFERENCE_VALUE && sinalPDireita > SENSOR_REFERENCE_VALUE) {
    turnLeft(TINY_FACTOR);
  } else if (sinalPEsquerda < SENSOR_REFERENCE_VALUE && sinalEsquerda > SENSOR_REFERENCE_VALUE && sinalCentro > SENSOR_REFERENCE_VALUE && sinalDireita > SENSOR_REFERENCE_VALUE && sinalPDireita > SENSOR_REFERENCE_VALUE) {
    turnLeft(NORMAL_FACTOR);
  } else if (sinalPEsquerda > SENSOR_REFERENCE_VALUE && sinalEsquerda < SENSOR_REFERENCE_VALUE && sinalCentro > SENSOR_REFERENCE_VALUE && sinalDireita > SENSOR_REFERENCE_VALUE && sinalPDireita > SENSOR_REFERENCE_VALUE) {
    turnRight(MEDIUM_FACTOR);
  } else if (sinalPEsquerda > SENSOR_REFERENCE_VALUE && sinalEsquerda > SENSOR_REFERENCE_VALUE && sinalCentro < SENSOR_REFERENCE_VALUE && sinalDireita > SENSOR_REFERENCE_VALUE && sinalPDireita > SENSOR_REFERENCE_VALUE) {
    forward();
  } else if (sinalPEsquerda > SENSOR_REFERENCE_VALUE && sinalEsquerda > SENSOR_REFERENCE_VALUE && sinalCentro > SENSOR_REFERENCE_VALUE && sinalDireita < SENSOR_REFERENCE_VALUE && sinalPDireita > SENSOR_REFERENCE_VALUE) {
    turnLeft(MEDIUM_FACTOR);
  } else if (sinalPEsquerda > SENSOR_REFERENCE_VALUE && sinalEsquerda > SENSOR_REFERENCE_VALUE && sinalCentro > SENSOR_REFERENCE_VALUE && sinalDireita > SENSOR_REFERENCE_VALUE && sinalPDireita < SENSOR_REFERENCE_VALUE) {
    turnRight(NORMAL_FACTOR);
  } else {
    stop();
  }
}
