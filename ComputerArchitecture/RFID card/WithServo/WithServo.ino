#include<SPI.h>
#include<MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include<Servo.h>

#define RST_PIN 9
#define SS_PIN 10

char* myTags[100]= {};
byte readCard[4];
int tagsCount = 0;
String tagID = "";
boolean successRead = false;
boolean correctTag = false;

int proximitySensor;
boolean doorOpened = false;

MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myServo;


void setup() {
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.begin();
  myServo.attach(8);

  myServo.write(10);
  lcd.print("No Master Tag!-");
  lcd.setCursor(0,1);
  lcd.print("Scan Now");

  while(!successRead){
    successRead = getID();
    if(successRead == true){
      myTags[tagsCount] = strdup(tagID.c_str()); // set he master tag into position 0
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Master Tag Set!");
      tagsCount++;
    }
  }

  successRead = false;
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
boolean getID(){
    if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
    return 0;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {   //Since a PICC placed get Serial and continue
    return 0;
  }
  tagID= "";
  for(uint8_t i=0; i<4; i++){
    readCard[i] = mfrc522.uid.uidByte[i];
    tagID.concat(String(mfrc522.uid.uidByte[i], HEX);
    
  }
  tagID.toUpperCase();
  mfrc522.PICC_HaltA(); // stop reading
  return 1;
}
void printNormarlModeMessage(){
  delay(1500);
  lcd.clear();
  lcd.print("Access Control");
  lcd.setCursor(0,1);
  lcd.print("Scan Your Tag!");
}
