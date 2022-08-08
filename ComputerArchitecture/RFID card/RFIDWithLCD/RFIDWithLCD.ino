#include<EEPROM.h>
#include<MFRC522.h>
#include<SPI.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define SSPin 10
#define RSTPin 9
MFRC522 mfrc522(SSPin, RSTPin );

unsigned long uidDec, uidDecTemp;
int ARRAYindexUIDcard;
int EEPROMstartAddr;
unsigned long CardUIDeEPROMread[] = {0,1,2,3,4,5,6,7,8,9};



const int yellowLed = 5;  
const int blueLed = 6; 
const int redLed = 7;   
const int btn = 4;
const int buzz = 3;
int btnValue = 0;
int state =0;
long adminID = 434161364;
int LockSwitch;
int f=0;

int cardReaded = 0;
void setup() {
  // initialize the LCD
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
 

  
  SPI.begin();
  mfrc522.PCD_Init();
  EEPROM.begin();
  Serial.begin(9600);

  pinMode(btn, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(buzz, OUTPUT);
  
  lcd.print("................");
  displayAllLed();
  //digitalWrite(buzz, 1);
  delay(1000);
  lock();
  displayWaitCard();
  EEPROMreadUIDcard();
 
}

void loop() {
  if(digitalRead(btn)){
    clearEEPROM();
    EEPROMreadUIDcard();
  }
  
  //Look for new cards.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  //Select one of the cards.
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  digitalWrite(buzz, 1);
  delay(250);
  digitalWrite(buzz, 0);
  //Read "UID".
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    uidDecTemp = mfrc522.uid.uidByte[i];
    uidDec = uidDec * 256 + uidDecTemp;
  }

  if(uidDec == adminID || LockSwitch >0){
    EEPROMwriteUIDcard();
  }

  if(LockSwitch == 0){
    for (ARRAYindexUIDcard = 0; ARRAYindexUIDcard <= 9; ARRAYindexUIDcard++)
    {
      if (CardUIDeEPROMread[ARRAYindexUIDcard] > 0)
      {
        if (CardUIDeEPROMread[ARRAYindexUIDcard] == uidDec)
        {
          unlock();
          
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Card :"); lcd.print(uidDec);
          
          lcd.setCursor(5,1);
          lcd.print("Unlock  ");
          lcd.setCursor(14, 1);
          for(int i=9  ; i>=0; i--){
            delay(500);
            lcd.setCursor(13, 1);
            lcd.print(i);
            lcd.setCursor(15, 1);
            lcd.print("s");
          }
          break;
        }
      }
    }

    if(ARRAYindexUIDcard == 10){
    
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Card :"); lcd.print(uidDec);
      
      lcd.setCursor(2,1);
      lcd.print("Unknown Card");
      
      digitalWrite(yellowLed, 1);
     
      delay(700);
      digitalWrite(yellowLed, 0);
      
    }
    delay(1000);
    lock();
    ARRAYindexUIDcard = 0;
    displayWaitCard();
  }
}
void EEPROMwriteUIDcard(){
  if(LockSwitch == 0){
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Recording Card");
    delay(500);
    
  }
  if(LockSwitch== 1){
    lcd.clear();
  }
  if(LockSwitch >0){
    if(uidDec == adminID){
      //lcd.setCursor(0, 1);
      //lcd.print("Skip Record : ");
      //lcd.print(EEPROMstartAddr/5);
      for(int i=EEPROMstartAddr/5; i<10; i++){
        EEPROMstartAddr += 5;
      }
      //EEPROMstartAddr += 5;
      
      delay(500);
    }
    else{
      EEPROM.write(EEPROMstartAddr, uidDec & 0xFF);
      EEPROM.write(EEPROMstartAddr + 1, (uidDec & 0xFF00) >> 8);
      EEPROM.write(EEPROMstartAddr + 2, (uidDec & 0xFF0000) >> 16);
      EEPROM.write(EEPROMstartAddr + 3, (uidDec & 0xFF000000) >> 24);
      EEPROM.end();  // EEPROM.commit();
      delay(10);
      lcd.setCursor(0, 0);
      cardReaded = (EEPROMstartAddr/5)+1;
      lcd.print("Recorded : ");  lcd.print(cardReaded);
      
      
      EEPROMstartAddr += 5;
      delay(500);
      
    }
  }
  LockSwitch++;

  if(EEPROMstartAddr/5 ==10){
    //lcd.clear();
    lcd.setCursor(5, 1);
    lcd.print("Saved : ");  lcd.print(cardReaded);
    delay(500);
    yellowBlink();
    
    EEPROMstartAddr = 0;
    uidDec = 0;
    ARRAYindexUIDcard = 0;
    EEPROMreadUIDcard();
  }
  
}
void EEPROMreadUIDcard(){
  for(int i=0; i<= 9; i++){
     byte val = EEPROM.read(EEPROMstartAddr + 3);
    CardUIDeEPROMread[ARRAYindexUIDcard] = (CardUIDeEPROMread[ARRAYindexUIDcard] << 8) | val;
    val = EEPROM.read(EEPROMstartAddr + 2);
    CardUIDeEPROMread[ARRAYindexUIDcard] = (CardUIDeEPROMread[ARRAYindexUIDcard] << 8) | val;
    val = EEPROM.read(EEPROMstartAddr + 1);
    CardUIDeEPROMread[ARRAYindexUIDcard] = (CardUIDeEPROMread[ARRAYindexUIDcard] << 8) | val;
    val = EEPROM.read(EEPROMstartAddr);
    CardUIDeEPROMread[ARRAYindexUIDcard] = (CardUIDeEPROMread[ARRAYindexUIDcard] << 8) | val;

    ARRAYindexUIDcard++;
    EEPROMstartAddr += 5;
  }

   ARRAYindexUIDcard = 0;
    EEPROMstartAddr = 0;
    uidDec = 0;
    LockSwitch = 0;
    displayWaitCard();
}
void displayWaitCard(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Please Put Card");
  lcd.setCursor(5, 1);
  lcd.print("Lock");
  
}
void lock(){
  digitalWrite(redLed, 1);
  digitalWrite(yellowLed, 0);
  digitalWrite(blueLed, 0);
}
void unlock(){
  digitalWrite(redLed, 0);
  digitalWrite(yellowLed, 0);
  digitalWrite(blueLed, 1);
}
void yellowBlink(){
   digitalWrite(yellowLed, 1);
   delay(500);
   digitalWrite(yellowLed, 0);
   delay(200);
    digitalWrite(yellowLed, 1);
   delay(500);
   digitalWrite(yellowLed, 0);
}
void clearEEPROM(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Clearing Memory");
  
   for(int i=0; i<EEPROM.length(); i++){
    EEPROM.write(i, 0);
  }
  
  lcd.setCursor(1, 1);
  lcd.print("Memory Cleared");
  yellowBlink();

}
void displayAllLed(){
  digitalWrite(redLed, 1);
  digitalWrite(yellowLed, 1);
  digitalWrite(blueLed, 1);
  delay(250);
  digitalWrite(redLed, 0);
  digitalWrite(yellowLed, 0);
  digitalWrite(blueLed, 0);
  
}
