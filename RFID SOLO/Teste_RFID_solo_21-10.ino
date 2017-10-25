/*
 * --------------------------------------------------------------------------------------------------------------------
 * Example sketch/program showing how to read data from a PICC to serial.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 * 
 * Example sketch/program showing how to read data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID
 * Reader on the Arduino SPI interface.
 * 
 * When the Arduino and the MFRC522 module are connected (see the pin layout below), load this sketch into Arduino IDE
 * then verify/compile and upload it. To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shft+M). When
 * you present a PICC (that is: a RFID Tag or Card) at reading distance of the MFRC522 Reader/PCD, the serial output
 * will show the ID/UID, type and any data blocks it can read. Note: you may see "Timeout in communication" messages
 * when removing the PICC from reading distance too early.
 * 
 * If your reader supports it, this sketch/program will read all the PICCs presented (that is: multiple tag reading).
 * So if you stack two or more PICCs on top of each other and present them to the reader, it will first output all
 * details of the first and then the next PICC. Note that this may take some time as all data blocks are dumped, so
 * keep the PICCs at reading distance until complete.
 * 
 * @license Released into the public domain.
 * 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

//INCLUSAO DAS BIBLIOTECAS
#include <SPI.h>       //inclui a biblioteca SPI.h --> biblioteca de interface serial --> permite a comunicação entre o arduino e o periférico (leitor rfid)
#include <MFRC522.h>  //inclui a biblioteca MFRC522.h --> ela permite usar as funcoes especificas do leitor RFID (MFRC522.h) --> 

//DECLARACAO DE VARIAVEIS
constexpr uint8_t RST_PIN = 5;          // Configurable, see typical pin layout above   --> Vai usar o pino 9 para o RESET do Leitor RFID
constexpr uint8_t SS_PIN = 53;         // Configurable, see typical pin layout above    --> Vai usar o pino 10 para ACIONAR OU NAO um determinado periférico (no nosso caso o Leitor RFID)
//float 0.23123445 1.898 
//int 0 , 1 , 2 ... 100
//char a, b, c...
//boolean 0 1 V F
//uint8_t  é um "unsigned integer of length 8 bits" --> um inteiro sem o bit de sinal, de tamanho 8 bits, portanto ele se refere a um byte. --> portanto o pino 9 é passado para o microcontrolador do arduino como 10010000


MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance  --> essa função vai dizer pro arduino através da biblioteca, que o leitor RFID vai utilizar os pinos 9 e 10

//INICIO DA CONFIGURACAO DO ARDUINO (void setup)
void setup() {
    Serial.begin(9600);        // Initialize serial communications with the PC --> essa instrução vai permitir que o arduino forneça informações para o monitor serial do PC
    while (!Serial);        // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4) --> caso der erro na função serial
    SPI.begin();            // Init SPI bus  --> inicia a permissão da comunicação entre o arduino e o periférico
 
    mfrc522.PCD_Init();        // Init MFRC522 --> iniciar o leitor RFId baseado nas pinagens descritas na funcao (MFRC522 mfrc522(SS_PIN, RST_PIN);
    mfrc522.PCD_DumpVersionToSerial();    // Show details of PCD - MFRC522 Card Reader details --> apresenta detalhes do cartão ou tag próximas ao leitor RFId
  mfrc522.PCD_AntennaOn(); //Inicia o modo de configuração da antena, porque vou ajustar o ganho na proxima funcao abaixo (mfrc522.PCD_SetAntennaGain(0x07 << 4); )
  mfrc522.PCD_SetAntennaGain(0x07 << 4); //ajusta o ganho da antena (a tabela está na propria biblioteca --> 0x07 << 4 equivale a 48 dB)
    Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks...")); //simplesmente escreve no monitor serial
}

//AS ACOES QUE O ARDUINO VAI EXECUTAR EM LOOP (void loop)
void loop() {
    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()) {  //SE tiver um novo cartao proximo no leitor do RDId (essa funcao esta dentro da biblioteca...acessando os 2 pinos especificados inicialmente), ENTAO vai para a proxima condicional IF (SE)
        return;
    }

    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()) { //SE ele achou um cartao, então vai ler esse cartao
        return;
    }

    // Dump debug info about the card; PICC_HaltA() is automatically called
    mfrc522.PICC_DumpToSerial(&(mfrc522.uid)); //Essa funcao vai buscar as informacoes contigas na EPROM das tags, cartoes ou tokens

//Show UID on serial monitor
//As informacoes estao mapeadas conforme explica esse site: https://learn.adafruit.com/adafruit-pn532-rfid-nfc/mifare
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)  //ele vai percorrer todo o mapa da EPROM (memoria)
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "); //vai fazer a leitura byte a byte desse mapa da EPROM (memoria)
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX)); //--> vai fazer uma traducao do mapa da EPROM para um identificador (UID) do carta/tag/token
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase(); //só pra transformar a tradução em caracteres em caixa alta (CAPS) 
  if (content.substring(1) == "71 4A 2C 2B") //change here the UID of the card/cards that you want to give access //SE essa tradução for igual a essa string/frase "71 4A 2C 2B" , ele vai escrever no monitor serial (Acesso autorizado)
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(3000); //Ele vai esperar 3 segundos para fazer o novo LOOP
  }
 
 else   { //SENAO (caso nao seja aquela frase/string , ele vai escrever no monitor serial (Acesso negado)
    Serial.println(" Access denied");
    delay(3000); //Ele vai esperar 3 segundos para fazer o novo LOOP
  }
}