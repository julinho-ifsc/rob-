#include <MFRC522.h>

MFRC522 mfrc522(53, 5);

const int melody[] ={
  390, //g
  330, //e
  262, //low c
  262, //low c
  262, //low c
  294, //low d
  330, //e
  348, //f
  390 //g
};

const int time[] ={
  16,
  16,
  8,
  8,
  16,
  16,
  16,
  16,
  8
};

void setup() {
  Serial.begin(9600);

  SPI.begin();
  mfrc522.PCD_Init();
  mfrc522.PCD_AntennaOn();

  pinMode(4, OUTPUT);
  Serial.println("setup completo");
}

void dixieHorn() {
  for (int i=0; i<= 8; i++){
    tone(4, melody[i], 2980/time[i]);
    delay(3000/time[i]);
  }
  digitalWrite(4, HIGH);
}

void loop() {
  digitalWrite(4, HIGH);

  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  String rfidUid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    rfidUid += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    rfidUid += String(mfrc522.uid.uidByte[i], HEX);
  }

  rfidUid.toLowerCase();
  rfidUid.trim();

  Serial.println(rfidUid);

  if (rfidUid == "c29d77d4") {
    Serial.println("right");
    dixieHorn();
  } else {
    Serial.println("wrong");
    digitalWrite(4, LOW);
    delay(200);
    digitalWrite(4, HIGH);
    delay(200);
    digitalWrite(4, LOW);
    delay(200);
    digitalWrite(4, HIGH);
    delay(200);
    digitalWrite(4, HIGH);
  }

  delay(1500);
}

