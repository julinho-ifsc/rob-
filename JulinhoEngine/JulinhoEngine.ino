#include <NewPing.h>
#include <MFRC522.h>
#include <EngineControl.h>

const EnginePins FRONT_LEFT_ENGINE_PINS = {6, 48, 49};
const EnginePins FRONT_RIGHT_ENGINE_PINS = {7, 46, 47};
const EnginePins BACK_LEFT_ENGINE_PINS = {8, 9, 10};
const EnginePins BACK_RIGHT_ENGINE_PINS = {13, 11, 12};
const SensorPins SENSOR_PINS = {A15, A14, A13, A12, A11};

MFRC522 mfrc522(5, 53);
EngineControl engineControl(60, 200);
NewPing sonar(23, 22);
String message = "";
String initialTag = "";
int rfidIndex = 0;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  pinMode(24, OUTPUT);

  engineControl.setFrontLeftPins(FRONT_LEFT_ENGINE_PINS);
  engineControl.setBackLeftPins(BACK_LEFT_ENGINE_PINS);
  engineControl.setFrontRightPins(FRONT_RIGHT_ENGINE_PINS);
  engineControl.setBackRightPins(BACK_RIGHT_ENGINE_PINS);
  engineControl.setSensorPins(SENSOR_PINS);
}

void loopEngine() {
  float distance = sonar.ping_cm();

  if (distance < 15 && distance > 0) {
    engineControl.parar();
  } else {
    engineControl.loop();
  }
}

void loop() {
  String currentDirection;

  if (message == "" && Serial2.available()) {
    message = Serial2.readString();
    return;
  }

  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    loopEngine();
    return;
  }

  String rfidUid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    rfidUid += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    rfidUid += String(mfrc522.uid.uidByte[i], HEX);
  }

  rfidUid.toLowerCase();
  rfidUid.trim();

  if (initialTag == rfidUid){
    return;
  }

  if (rfidUid == "bc521a14") {
    loopEngine();
    return;
  }

  int incomingRfidIndex = message.indexOf(rfidUid);

  if (incomingRfidIndex == rfidIndex) {
    currentDirection = message.substring(rfidIndex + 9, rfidIndex + 10);
    rfidIndex += 11;
  }
  initialTag = rfidUid;

  if (currentDirection == "d") {
    engineControl.direita();
  } else if (currentDirection == "e") {
    engineControl.esquerda();
  } else if (currentDirection == "f") {
    digitalWrite(24, LOW);
    engineControl.frente();
    delay(250);
    digitalWrite(24, HIGH);
  } else if (currentDirection == "t") {
    engineControl.tras();
  } else if (currentDirection == "p") {
    engineControl.parar();
  }

  delay(2000);
}
