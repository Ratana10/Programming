#include <dht11.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <LiquidCrystal_I2C.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27,16,2);

dht11 DHT11;

 int led= 1;
 int soilSensor = A0;
 int ldrSensor = A1;
 int tempSensor = 5;
int waterPump= 5;

int soilValue = 0;
int ldrValue = 0;
float tempValue = 0;
float celsius =0.0;
float voltage = 0.0;

void setup() {
  // put your setup code here, to run once:
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3,0);
  //lcd.print("Hak Sopheak");
  Serial.begin(9600);
  pinMode(waterPump, OUTPUT);
  pinMode(led,OUTPUT);
}
void testCode(){

  
}
void loop() {
  soilValue = analogRead(soilSensor);
  ldrValue = analogRead(ldrSensor);
  int chk = DHT11.read(tempSensor);
  tempValue = (DHT11.temperature);
  Serial.print("Temperature C : ");
  Serial.println(ldrValue);
  lcd.clear();
  lcd.print(ldrValue);
  if(soilValue >700)
  {
    digitalWrite(waterPump, 1);
    delay(100);
   
    }
    else if( ldrValue< 100)
    { 
      digitalWrite(waterPump,1);
    }
    else if ( tempValue > 32){ 
      digitalWrite(waterPump,1);
    }
  else
  {
    
    digitalWrite(waterPump, 0);

  }
 // Serial.println((float)DHT11.temperature, 2);
  
 

 delay(1000);
} 
