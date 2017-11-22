#include <SPI.h>
#include <MFRC522.h>

constexpr uint8_t RST_PIN = 5;
constexpr uint8_t SS_PIN = 53;

char message_buff[8];

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  while (!Serial);

  SPI.begin();
  mfrc522.PCD_Init();
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  String rfidUid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    rfidUid += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    rfidUid += String(mfrc522.uid.uidByte[i], HEX);
  }
  rfidUid.toUpperCase();
  rfidUid.trim();
  
  if (rfidUid != message_buff) {  
    Serial.println(rfidUid);
    rfidUid.toCharArray(message_buff, rfidUid.length() + 1);
    Serial1.print(message_buff);
  }
}
