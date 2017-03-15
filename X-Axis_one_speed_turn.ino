#include <Stepper.h>

#define IN1  8
#define IN2  9
#define IN3  10
#define IN4  11

#define IN5  4
#define IN6  5
#define IN7  6
#define IN8  7


#define laser 3
boolean laserstate;
boolean laserinitial = LOW;
int button = A2;
int buttonval;
int Steps = 0;
int stepsPerRevolution = 4095;
boolean xdir = true;
unsigned long last_time;
unsigned long currentMillis ;
int steps_left=4095;
long time;

Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
Stepper myStepper2(stepsPerRevolution, 8, 9, 10, 11);


void setup(){

Serial.begin(9600);
pinMode(IN1, OUTPUT); 
pinMode(IN2, OUTPUT); 
pinMode(IN3, OUTPUT); 
pinMode(IN4, OUTPUT); 
pinMode(IN5, OUTPUT); 
pinMode(IN6, OUTPUT); 
pinMode(IN7, OUTPUT); 
pinMode(IN8, OUTPUT);
//pinMode(button, INPUT);
pinMode(laser,OUTPUT);
digitalWrite(laser, LOW);

const int x = 0;
const int y = 1;
int xval = 0;
int yval = 0;
int xdir = 0;
int ydir = 0; 




}



void loop() {
  // put your main code here, to run repeatedly:
int Steps = 0;  
int xval = 0;
int yval = 0;
int xdir = 0;
int ydir = 0; 

xval = analogRead(0);
yval = analogRead(1);

xval = map(xval, 0, 1024, 0, 100);
  
xval = xval - 49;

yval = map(yval, 0, 1024, 0, 100);
  
yval = yval - 49;

if (xval < -2){xdir=1;}
if (xval > 5){xdir=3;}

if (yval < -2){ydir=1;}
if (yval > 5){ydir=3;}



int xspeed = 1; //Delay time
if (xdir ==1){


     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
 delay(xspeed);
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, HIGH);
delay(xspeed);  
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
delay(xspeed);
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
 delay(xspeed);
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
 delay(xspeed); 
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
delay(xspeed);
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
  delay(xspeed);
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
 delay(xspeed);
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
 delay(xspeed);
}


if (xdir == 3){

digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
delay(xspeed);
    digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
delay(xspeed);
      digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
delay(xspeed);
   digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
delay(xspeed);
    digitalWrite(IN1, LOW); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
 delay(xspeed); 
      digitalWrite(IN1, LOW); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
 delay(xspeed);
    digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
delay(xspeed);
    digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, HIGH);
delay(xspeed);  
      digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
 delay(xspeed);

 
}

//motor for up down!!!!

int yspeed = 1; //Delay time
if (ydir ==1){


     digitalWrite(IN5, LOW); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, HIGH);
 delay(yspeed);
     digitalWrite(IN5, LOW); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, HIGH);
     digitalWrite(IN8, HIGH);
delay(yspeed);  
     digitalWrite(IN5, LOW); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, HIGH);
     digitalWrite(IN8, LOW);
delay(yspeed);
     digitalWrite(IN5, LOW); 
     digitalWrite(IN6, HIGH);
     digitalWrite(IN7, HIGH);
     digitalWrite(IN8, LOW);
 delay(yspeed);
     digitalWrite(IN5, LOW); 
     digitalWrite(IN6, HIGH);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, LOW);
 delay(yspeed); 
     digitalWrite(IN5, HIGH); 
     digitalWrite(IN6, HIGH);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, LOW);
delay(yspeed);
     digitalWrite(IN5, HIGH); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, LOW);
  delay(yspeed);
     digitalWrite(IN5, HIGH); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, HIGH);
 delay(yspeed);
     digitalWrite(IN5, LOW); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, LOW);
 delay(yspeed);
}


if (ydir == 3){

digitalWrite(IN5, LOW); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, LOW);
delay(yspeed);
    digitalWrite(IN5, HIGH); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, HIGH);
delay(yspeed);
      digitalWrite(IN5, HIGH); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, LOW);
delay(yspeed);
   digitalWrite(IN5, HIGH); 
     digitalWrite(IN6, HIGH);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, LOW);
delay(yspeed);
    digitalWrite(IN5, LOW); 
     digitalWrite(IN6, HIGH);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, LOW);
 delay(yspeed); 
      digitalWrite(IN5, LOW); 
     digitalWrite(IN6, HIGH);
     digitalWrite(IN7, HIGH);
     digitalWrite(IN8, LOW);
 delay(yspeed);
    digitalWrite(IN5, LOW); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, HIGH);
     digitalWrite(IN8, LOW);
delay(yspeed);
    digitalWrite(IN5, LOW); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, HIGH);
     digitalWrite(IN8, HIGH);
delay(yspeed);  
      digitalWrite(IN5, LOW); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, HIGH);
 delay(yspeed);

 
}
buttonval = analogRead(button);
//Serial.println(buttonval);

if (buttonval < 50){

laserstate != laserstate;
  
digitalWrite(laser, laserstate);

Serial.println(laserstate);

delay(200);

  
}


}

