#include <NewPing.h>
#include <EngineControl.h>

const int PIN_LEFT_END_SENSOR = A15;
const int PIN_LEFT_SENSOR = A14;
const int PIN_CENTER_SENSOR = A13;
const int PIN_RIGHT_SENSOR = A12;
const int PIN_RIGHT_END_SENSOR = A11;

const EnginePins FRONT_LEFT_ENGINE_PINS = {6, 48, 49};
const EnginePins FRONT_RIGHT_ENGINE_PINS = {7, 46, 47};
const EnginePins BACK_LEFT_ENGINE_PINS = {8, 9, 10};
const EnginePins BACK_RIGHT_ENGINE_PINS = {13, 11, 12};
const SensorPins SENSOR_PINS = {
  PIN_LEFT_END_SENSOR,
  PIN_LEFT_SENSOR,
  PIN_CENTER_SENSOR,
  PIN_RIGHT_SENSOR,
  PIN_RIGHT_END_SENSOR
};

EngineControl engineControl(60, 200);
NewPing sonar(23, 22);

void setup() {
  Serial.begin(9600);

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

  engineControl.setFrontLeftPins(FRONT_LEFT_ENGINE_PINS);
  engineControl.setBackLeftPins(BACK_LEFT_ENGINE_PINS);
  engineControl.setFrontRightPins(FRONT_RIGHT_ENGINE_PINS);
  engineControl.setBackRightPins(BACK_RIGHT_ENGINE_PINS);
  engineControl.setSensorPins(SENSOR_PINS);
}

void loop() {
  float distance = sonar.ping_cm();

  if (distance < 15 & distance > 0) {
    engineControl.parar();
  } else {
    engineControl.loop();
  }
}
