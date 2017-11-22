#include <SPI.h>
#include <MFRC522.h>

constexpr uint8_t RST_PIN = 5;
constexpr uint8_t SS_PIN = 53;

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  while (!Serial);

  SPI.begin();
  mfrc522.PCD_Init();
}

void loop() {

      //  Procura tags;
    if ( ! mfrc522.PICC_IsNewCardPresent()) { 
      return;
    }

    //  Lê a tag
    if ( ! mfrc522.PICC_ReadCardSerial()){
      return;
    }
    String rfidUid = "";
   for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    rfidUid.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    rfidUid.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  rfidUid.toUpperCase();
  Serial.println(rfidUid);
  Serial1.println(rfidUid);
//  delay(10000);
  return;
}
// transmissor