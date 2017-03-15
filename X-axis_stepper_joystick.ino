#include <Stepper.h>

#define IN1  8
#define IN2  9
#define IN3  10
#define IN4  11
int Steps = 0;
int stepsPerRevolution = 4095;
boolean xdir = true;
unsigned long last_time;
unsigned long currentMillis ;
int steps_left=4095;
long time;

Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup(){

Serial.begin(115200);
pinMode(IN1, OUTPUT); 
pinMode(IN2, OUTPUT); 
pinMode(IN3, OUTPUT); 
pinMode(IN4, OUTPUT); 
const int x = 0;
const int y = 1;
int xval = 0;
int yval = 0;
int xdir = 0;
int ydir = 0; 




}

void loop() {
  // put your main code here, to run repeatedly:
  //default 
int xval = 0;
int yval = 0;
int xdir = 0;
int ydir = 0; 
int xw = 0;


//SetDirection(){
//}

//void SetDirection(){


xval = analogRead(0);
yval = analogRead(1);

xval = map(xval, 0, 1024, 0, 100);
  
xval = xval - 49;

if (xval < 0)
{

//set the motor direction to reverse (right/left)
xdir = 0;

  
}

else {
//set the motor direction to forward (right/left)
xdir = 1;
  
}
xval = abs(xval);

yval = map(yval, 0, 1024, 0, 100);
  
yval = yval - 49;

if (yval < 0)
{

//set the motor direction to reverse  (up/down)
ydir = 1;

  }

else {
//set the motor direction to forward  (up/down)
ydir = 0;
  
}

yval = abs(yval);

Serial.print("X value"  );
Serial.println(xval);
Serial.print("Y value"  );
Serial.println(yval);
Serial.print("X dir"  );
Serial.println(xdir);
Serial.print("Y dir"  );
Serial.println(ydir);

//void stepper(int xw){
  for (int x=0;x<xw;x++){
switch(Steps){
   case 0:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
   break; 
   case 1:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, HIGH);
   break; 
   case 2:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
   break; 
   case 3:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
   break; 
   case 4:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
   case 5:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
     case 6:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
   case 7:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
   break; 
   default:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 

if(xdir==1){ 
  myStepper.setSpeed(xval);
  Steps++;}
if(xdir==0){ 
  myStepper.setSpeed(xval);
  Steps--; }
if(Steps>7){Steps=0;}
if(Steps<0){Steps=7; }

}
}
}

//delay(400);   //For stability


