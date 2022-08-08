#include<EEPROM.h>
#include<MFRC522.h>
#include<SPI.h>

#define SSPin 10
#define RSTPin 9
MFRC522 mfrc522(SSPin, RSTPin );

unsigned long uidDec, uidDecTemp;
int arrIndexUidCard;
int EEPROMstartAddr;

unsigned long cardUIDEEPROMread[] = {0,1,2,3,4,5,6,7,8,9};

const int yellowLed = 7;  //unlock
const int blueLed = 6; //lock
const int redLed = 5;   

const int btn = 4;
int state =0;

int LockSwitch;
long adminID = 3376454593; 

void setup(){
  SPI.begin();
  mfrc522.PCD_Init();
  EEPROM.begin();
  Serial.begin(9600);

  pinMode(btn, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  
  clearEEPROM();
  Serial.println(EEPROM.length());

  displayWaitCard();
  EEPROMreadUIDCard();
}
void loop(){
  if(digitalRead(btn) == 1){
    unlock();
    delay(100);

    lock();
    displayWaitCard();
  }
  
  //looking for new card
  if ( !mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  //Select one of the cards.
  if ( !mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  
  // Read UID
  for(byte i=0; i<  mfrc522.uid.size; i++){
    uidDecTemp = mfrc522.uid.uidByte[i];
    uidDec = uidDec * 256 + uidDecTemp;
  
  }
  Serial.print("UID : ");
  Serial.println(uidDec);

  if(uidDec == adminID || LockSwitch > 0){
    
    EEPROMwriteUIDCard();
  }

  if(LockSwitch == 0){
    for(arrIndexUidCard =0; arrIndexUidCard <= 9; arrIndexUidCard++){
      if(cardUIDEEPROMread[arrIndexUidCard] >0){
        if( cardUIDEEPROMread[arrIndexUidCard] == uidDec){
          Serial.println("Accessed ");
          unlock();
          break;
        }
      }
    }

    if(arrIndexUidCard == 10){
      Serial.println("Card not FOund");
      digitalWrite(redLed, 1);
      delay(500);
      digitalWrite(redLed, 0);
    }
    arrIndexUidCard = 0;
    displayWaitCard();
  }
  
  
}
void EEPROMwriteUIDCard(){
  if(LockSwitch == 0){
    Serial.println("Start Record card");
    
  }
  if(LockSwitch > 0){
    if(uidDec == adminID){
      Serial.println("SKIP RECORD");
      Serial.println(EEPROMstartAddr/5);
      EEPROMstartAddr += 5;
      delay(200);
    }
    else{
      EEPROM.write(EEPROMstartAddr, uidDec & 0xFF);
      EEPROM.write(EEPROMstartAddr + 1, (uidDec & 0xFF00) >> 8);
      EEPROM.write(EEPROMstartAddr + 2, (uidDec & 0xFF0000) >> 16);
      EEPROM.write(EEPROMstartAddr + 3, (uidDec & 0xFF000000) >> 24);
      //EEPROM.commit();
      delay(10);
      
      Serial.println("Record OK");
      Serial.print("MOMORY : ");
      Serial.println(EEPROMstartAddr /5);
      EEPROMstartAddr += 5;
      delay(500);
     }
  }
  LockSwitch++;
  
  

  if(EEPROMstartAddr / 5 == 10){
    Serial.println("Record Finish");
    EEPROMstartAddr=0;
    uidDec = 0;
    arrIndexUidCard = 0;
    EEPROMreadUIDCard();
    
  }
  
}
void EEPROMreadUIDCard(){
  Serial.println("Reading Card");
  for(int i=0; i<=9; i++){
    byte val = EEPROM.read(EEPROMstartAddr + 3);
    cardUIDEEPROMread[arrIndexUidCard] = (cardUIDEEPROMread[arrIndexUidCard] << 8) | val;
    val = EEPROM.read(EEPROMstartAddr + 2);
    cardUIDEEPROMread[arrIndexUidCard] = (cardUIDEEPROMread[arrIndexUidCard] << 8) | val;
    val = EEPROM.read(EEPROMstartAddr + 1);
    cardUIDEEPROMread[arrIndexUidCard] = (cardUIDEEPROMread[arrIndexUidCard] << 8) | val;
    val = EEPROM.read(EEPROMstartAddr);
    cardUIDEEPROMread[arrIndexUidCard] = (cardUIDEEPROMread[arrIndexUidCard] << 8) | val;

    arrIndexUidCard++;
    EEPROMstartAddr += 5;
    }
    arrIndexUidCard = 0;
    EEPROMstartAddr = 0;
    uidDec = 0;
    LockSwitch = 0;
   
    displayWaitCard();
}
void displayWaitCard(){
  Serial.println("Please Input Tag card ");
}
void lock(){
  Serial.println("Locked");
  digitalWrite(blueLed, 1);
  digitalWrite(yellowLed, 0);
  delay(500);
}
void unlock(){
  Serial.println("Unlocked");
  digitalWrite(blueLed, 0);
  digitalWrite(yellowLed, 1);
   delay(500);
}
void clearEEPROM(){
  for(int i=0; i<EEPROM.length(); i++){
    EEPROM.write(i, 0);
  }
  Serial.println("Memory Cleared");
}
