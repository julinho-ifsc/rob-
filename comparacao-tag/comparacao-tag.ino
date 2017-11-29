#include <MFRC522.h>
#include <SPI.h>

String rfidUid = "";
String comp = "batata";

constexpr uint8_t RST_PIN = 5;
constexpr uint8_t SS_PIN = 53;

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  
 Serial.begin(9600);
 SPI.begin();

 Serial.println("Configurando RFID");
 mfrc522.PCD_Init();
 Serial.println("Feito");

}

void loop() {
  
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    rfidUid += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    rfidUid += String(mfrc522.uid.uidByte[i], HEX);
  }

  rfidUid.toLowerCase();
  rfidUid.trim();
  
  if (comp == rfidUid){
    return;
  } else {
    if (rfidUid == "bc521a14"){
      Serial.println("Estacao base");
    } else if (rfidUid == "d2f7e4d4"){
      Serial.println("Tag A");
    } else if (rfidUid == "827277d4"){
      Serial.println("Tag B");
    } else {
      Serial.println("Nao cadastrada");
    }
    comp = rfidUid;
    rfidUid = "";
  }
}
