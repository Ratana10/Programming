#include <EEPROM.h>

#include <SPI.h>
#include <MFRC522.h>

#define SSPin 10
#define RSTPin 9

MFRC522 mfrc522(SSPin, RSTPin );

void setup() {

  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Input your card to reader : ");
  Serial.println();
}

void loop() {
//lokking for new card
  if( !mfrc522.PICC_IsNewCardPresent()){
    Serial.println("Error 1");
    return ;
  }
  //Select one of the cards
  if( !mfrc522.PICC_ReadCardSerial() ){
    Serial.println("Error 2");
    return ;
  }
  // Show UID on Serial. Number
  Serial.print("UID tage number : ");

  String content="";
  byte letter;
  String arrstr[100];

  for(byte i=0; i<mfrc522.uid.size; i++){

    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
    
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
    
  if( content.substring(1)==  "00000")
  {
    Serial.println("Authorized Access ");   
   delay(3000);
  }
  else{
    Serial.println("Access Denied");
    delay(3000);
  }

 
}

int writeStringToEEPROM(int addrOffset, const String &strToWrite)
{
  byte len = strToWrite.length();
  EEPROM.write(addrOffset, len);

  for (int i = 0; i < len; i++)
  {
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
  }

  return addrOffset + 1 + len;
}

int readStringFromEEPROM(int addrOffset, String *strToRead)
{
  int newStrLen = EEPROM.read(addrOffset);
  char data[newStrLen + 1];

  for (int i = 0; i < newStrLen; i++)
  {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[newStrLen] = '\0'; // !!! NOTE !!! Remove the space between the slash "/" and "0" (I've added a space because otherwise there is a display bug)

  *strToRead = String(data);
  return addrOffset + 1 + newStrLen;
}
