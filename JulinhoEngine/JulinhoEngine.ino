#include <NewPing.h>
#include <EngineControl.h>

const EnginePins FRONT_LEFT_ENGINE_PINS = {6, 48, 49};
const EnginePins FRONT_RIGHT_ENGINE_PINS = {7, 46, 47};
const EnginePins BACK_LEFT_ENGINE_PINS = {8, 9, 10};
const EnginePins BACK_RIGHT_ENGINE_PINS = {13, 11, 12};
const SensorPins SENSOR_PINS = {A15, A14, A13, A12, A11};

EngineControl engineControl(60, 200);
NewPing sonar(23, 22);

void setup() {
  Serial.begin(9600);

  engineControl.setFrontLeftPins(FRONT_LEFT_ENGINE_PINS);
  engineControl.setBackLeftPins(BACK_LEFT_ENGINE_PINS);
  engineControl.setFrontRightPins(FRONT_RIGHT_ENGINE_PINS);
  engineControl.setBackRightPins(BACK_RIGHT_ENGINE_PINS);
  engineControl.setSensorPins(SENSOR_PINS);
}

void loop() {
  float distance = sonar.ping_cm();

  if (distance < 15 && distance > 0) {
    engineControl.parar();
  } else {
    engineControl.loop();
  }
}
