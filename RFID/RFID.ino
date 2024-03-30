//https://www.aranacorp.com/fr/utilisation-dun-module-rfid-avec-arduino/
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);
byte nuidPICC[4];
byte password[] = {186, 232, 26, 63};

void setup() {
 Serial.begin(9600);
 SPI.begin();
 rfid.PCD_Init();
 Serial.println(F("Scan RFID NUID..."));
}

void loop() {
 readRFID();
 delay(200);
}

void readRFID() {
 if (!rfid.PICC_IsNewCardPresent())
  return;

 if (!rfid.PICC_ReadCardSerial())
  return;

 if (rfid.uid.uidByte[0] != nuidPICC[0] ||
     rfid.uid.uidByte[1] != nuidPICC[1] ||
     rfid.uid.uidByte[2] != nuidPICC[2] ||
     rfid.uid.uidByte[3] != nuidPICC[3]) {
  Serial.println(F("A new card has been detected."));
  
  for (byte i = 0; i < 4; i++) {
   nuidPICC[i] = rfid.uid.uidByte[i];
  }
  
  Serial.print(F("RFID tag in dec: "));
  printDec(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();
 }

 if (compareUID(rfid.uid.uidByte, password)) {
  Serial.println("Password detected");
  // Envoyer un signal au PC
  Serial.println("PC_SIGNAL");
 }

 rfid.PICC_HaltA();
 rfid.PCD_StopCrypto1();
}

bool compareUID(byte* uid, byte* password) {
 for (int i = 0; i < 4; i++) {
  if (uid[i] != password[i]) {
   return false;
  }
 }
 return true;
}

void printDec(byte* buffer, byte bufferSize) {
 for (byte i = 0; i < bufferSize; i++) {
  Serial.print(buffer[i] < 0x10 ? " 0" : " ");
  Serial.print(buffer[i], DEC);
 }
}
