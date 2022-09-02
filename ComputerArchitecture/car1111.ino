#include <AFMotor.h>

AF_DCMotor MotorFR(4);   //Motor for drive Front Right On M1
AF_DCMotor MotorFL(1);   //Motor for drive Front Left On M2
AF_DCMotor MotorBL(2);   //Motor for drive Back Left On M3
AF_DCMotor MotorBR(3);   //Motor for drive Back Right On M4

char bt;
int valSpeed= 255;

void setup()
{
  //Serial.begin(9600);
 
  MotorFR.setSpeed(255);
  MotorFL.setSpeed(255);
  MotorBL.setSpeed(255);
  MotorBR.setSpeed(255);

  Stop();
}


void loop() {

 bt=Serial.read();
  Serial.print(bt);
 switch(bt){
  case 'F':
    SetSpeed(valSpeed);
    moveForward();
  break;
  case 'B':
    SetSpeed(valSpeed);
    moveBackward();
  break;
  case 'L':
    SetSpeed(valSpeed);
    turnLeft();
  break;
  case 'R':
    SetSpeed(valSpeed);
    turnRight();
  break;
  case 'S':
    
    Stop();
  break;
  case 'G' :
    SetSpeed(valSpeed);
    forwardLeft();
  break;
  case 'H' :
    SetSpeed(valSpeed);
    backwardLeft();
  break;
  case 'I' :
    SetSpeed(valSpeed);
    forwardRight();
  break;
  case 'J' :
    SetSpeed(valSpeed);
    backwardRight();
  break;
  /*
  case '0':
    SetSpeed(0);
   break;
  case '1':
    SetSpeed(30);
  break;
  case '2':
    SetSpeed(55);
  break;
  case '3':
    SetSpeed(80);
  break;
  case '4':
    SetSpeed(106);
  break;
  case '5':
    SetSpeed(130);
  break;
  case '6':
    SetSpeed(155);
  break;
  case '7':
    SetSpeed(180);
  break;
  case '8':
    SetSpeed(205);
  break;
  case '9':
    SetSpeed(255);
  break;
  */
 }
 


}
void forwardRight(){
  MotorFR.setSpeed(valSpeed/4);
  MotorBR.setSpeed(valSpeed/4);
  moveForward();
}
void backwardRight(){
  MotorFR.setSpeed(valSpeed/4);
  MotorBR.setSpeed(valSpeed/4);
  moveBackward();
}
void forwardLeft(){
  MotorFL.setSpeed(valSpeed/4);
  MotorBL.setSpeed(valSpeed/4);
  moveForward();
}
void backwardLeft(){
  MotorFL.setSpeed(valSpeed/4);
  MotorBL.setSpeed(valSpeed/4);
  moveBackward();
}
void Stop(){
  MotorFR.run(RELEASE);  
  MotorFL.run(RELEASE);
  MotorBR.run(RELEASE);
  MotorBL.run(RELEASE);
}
void SetSpeed(int val){
  valSpeed = val;
  MotorFR.setSpeed(valSpeed);  
  MotorFL.setSpeed(valSpeed);
  MotorBR.setSpeed(valSpeed);
  MotorBL.setSpeed(valSpeed);
}
void moveForward(){
  MotorFR.run(FORWARD);
  MotorFL.run(FORWARD);
  MotorBR.run(FORWARD);
  MotorBL.run(FORWARD);
}
void moveBackward(){
  MotorFR.run(BACKWARD);
  MotorFL.run(BACKWARD);
  MotorBR.run(BACKWARD);
  MotorBL.run(BACKWARD);
}
void turnRight(){
  MotorFR.run(BACKWARD);  
  MotorFL.run(FORWARD);
  MotorBR.run(BACKWARD);
  MotorBL.run(FORWARD);
  
}
void turnLeft(){
  MotorFR.run(FORWARD);  
  MotorFL.run(BACKWARD);
  MotorBR.run(FORWARD);
  MotorBL.run(BACKWARD);
 
}
