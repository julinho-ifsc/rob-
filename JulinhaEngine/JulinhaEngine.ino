#include <NewPing.h>
#include <MFRC522.h>
#include <EngineControl.h>

const EnginePins FRONT_LEFT_ENGINE_PINS = {13, 11, 12};
const EnginePins FRONT_RIGHT_ENGINE_PINS = {8, 9, 10};
const EnginePins BACK_LEFT_ENGINE_PINS = {3, 38, 39};
const EnginePins BACK_RIGHT_ENGINE_PINS = {2, 40, 41};
const SensorPins SENSOR_PINS = {A11, A12, A13, A14, A15};

MFRC522 mfrc522(53, 5);
EngineControl engineControl(40, 200);
NewPing sonar(23, 22);
String message = "";
String initialTag = "";
int rfidIndex = 0;
boolean leavedBase = false;

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
  
  SPI.begin();
  mfrc522.PCD_Init();
  mfrc522.PCD_AntennaOn();
  mfrc522.PCD_SetAntennaGain(0x07 << 4);

  pinMode(4, OUTPUT);

  engineControl.setFrontLeftPins(FRONT_LEFT_ENGINE_PINS);
  engineControl.setBackLeftPins(BACK_LEFT_ENGINE_PINS);
  engineControl.setFrontRightPins(FRONT_RIGHT_ENGINE_PINS);
  engineControl.setBackRightPins(BACK_RIGHT_ENGINE_PINS);
  engineControl.setSensorPins(SENSOR_PINS);
  Serial.println("Setup completo");
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
  digitalWrite(4, HIGH);
  String currentDirection;

  if (message == "") {
    if (Serial1.available()) {
      message = Serial1.readString();
    }
    return;
  }


  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    if (leavedBase == true) {
      loopEngine();
    }
    return;
  }

  
  Serial.println(message);
  Serial.println();

  Serial.println("rfid encontrado");
  String rfidUid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    rfidUid += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    rfidUid += String(mfrc522.uid.uidByte[i], HEX);
  }

  rfidUid.toLowerCase();
  rfidUid.trim();
  Serial.println(rfidUid);

  if (initialTag == rfidUid){
    return;
  }

  initialTag = rfidUid;

  if (rfidUid == "bc521a14") {
    Serial.println("julinho na base");
    loopEngine();
    leavedBase = true;
    return;
  }
  
  int incomingRfidIndex = message.indexOf(rfidUid);

  if (incomingRfidIndex == rfidIndex) {
    currentDirection = message.substring(rfidIndex + 9, rfidIndex + 10);
    rfidIndex += 11;
  }

  Serial.print("nova direção: ");
  Serial.println(currentDirection);

  if (currentDirection == "d") {
    engineControl.direita();
  } else if (currentDirection == "e") {
    engineControl.esquerda();
  } else if (currentDirection == "f") {
    engineControl.frente();
    Serial.println("ligando buzzer");
    digitalWrite(4, LOW);
    delay(150);
    digitalWrite(4, HIGH);
    delay(150);
    digitalWrite(4, LOW);
    delay(150);
    digitalWrite(4, HIGH);
  } else if (currentDirection == "t") {
    engineControl.tras();
  } else if (currentDirection == "p") {
    engineControl.parar();
    Serial.println("ligando buzzer");
    digitalWrite(4, LOW);
    delay(150);
    digitalWrite(4, HIGH);
    message = "";
    rfidIndex = 0;
    leavedBase = false;
  }
}

