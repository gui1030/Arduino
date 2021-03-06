#include <Stepper.h>

//Input Pins for (Up/Down) Motor
#define IN1  8
#define IN2  9
#define IN3  10
#define IN4  11

//Input Pins for (Left/Right) Motor
#define IN5  4
#define IN6  5
#define IN7  6
#define IN8  7

//Input pin for laser
#define laser 3
int laserstate;
int previous;
long time = 0;
long debounce = 200;

int button = A2;
int buttonval;
int Steps = 0;
int stepsPerRevolution = 4095;
boolean xdir = true;
unsigned long last_time;
unsigned long currentMillis ;
int steps_left=4095;


Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
Stepper myStepper2(stepsPerRevolution, 8, 9, 10, 11);


void setup(){

//Serial.begin(9600);
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

//Set delay between coil activations, which controls the angular velocity
const int totalspeed = 1;

//Read input from joystick x-axis and y-axis
xval = analogRead(0);
yval = analogRead(1);

//Map analog values to 0-100 and then -49 to get both negative and positive numbers
//which changes the direction of the stepper
xval = map(xval, 0, 1024, 0, 100);
xval = xval - 49;
yval = map(yval, 0, 1024, 0, 100);
yval = yval - 49;

//Sets both the x and y direction of rotation with a dead zone in the middle
//to account for any voltage variance coming from the joystick pots
if (xval < -2){xdir=1;}
if (xval > 5){xdir=3;}
if (yval < -2){ydir=1;}
if (yval > 5){ydir=3;}

//Setting the speed of rotation to a constant
int xspeed = totalspeed; //Delay time

//Spin " " Direction at speed xspeed
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

//Spin " " Direction at speed xspeed
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
int yspeed = totalspeed; //Delay time
if (ydir ==3){
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

if (ydir == 1){
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

if (buttonval < 2 && previous > 2 && yval > -15){

  if(laserstate == HIGH){
    laserstate = LOW;
  }

  else {laserstate = HIGH;}
  time = millis();
  }

digitalWrite(laser, laserstate);

previous = buttonval;

}
