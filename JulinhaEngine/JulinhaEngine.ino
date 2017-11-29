#include <NewPing.h>
#include <EngineControl.h>

const EnginePins FRONT_LEFT_ENGINE_PINS = {3, 38, 39};
const EnginePins FRONT_RIGHT_ENGINE_PINS = {2, 40, 41};
const EnginePins BACK_LEFT_ENGINE_PINS = {13, 12, 11};
const EnginePins BACK_RIGHT_ENGINE_PINS = {8, 10, 9};
const SensorPins SENSOR_PINS = {A11, A12, A13, A14, A15};

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

  if (distance < 15 & distance > 0) {
    engineControl.parar();
  } else {
    engineControl.loop();
  }
}
