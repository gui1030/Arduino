/*
 * This program is to test the power adapters we are currently using
 * It will consist of one relay that will randomly switch on and off stressing the power adapter
 * It will also check the output of the power adapter to ensure it is working
 * The system will (Hopefully) tell us how long it took until it failed
 */

//Included libraries
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <gfxfont.h>

//Defined Variables
#define relaypin 7
#define voltagepin 6
#define OLED_RESET 4
#define min 60000
#define sec 1000
long randNumber;
long timedelay;
long previousmillis;
int loopcounter;


//Initializers
Adafruit_SSD1306 display(OLED_RESET);

/*
 *--SETUP----SETUP----SETUP----SETUP----SETUP----SETUP----SETUP----SETUP----SETUP----SETUP----SETUP----SETUP----SETUP--
 */

void setup() {
Serial.begin(9600);
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
oledinit();

//Setup Pin Configuration
pinMode(voltagepin, INPUT);
pinMode(relaypin, OUTPUT);
digitalWrite(relaypin, HIGH);

delay(2000);

}

/*
 * --LOOP----LOOP----LOOP----LOOP----LOOP----LOOP----LOOP----LOOP----LOOP----LOOP----LOOP----LOOP----LOOP----LOOP----LOOP--
 */

void loop() {

//Set the initial time delay, which will then become random between 10-30 Min

if (loopcounter == 0){
 long timedelay = 10000;
}

if (millis() - previousmillis > timedelay){
  previousmillis = millis();
  oledinittest();
  randNumber = random(10, 30);
  timedelay = randNumber * min;
  oledprintdelay(timedelay);
  bool success = runtest();

    if (success == true){
       display.setCursor(20,20);
       display.print("PASS");
       display.display();
      }

     while (success == false){
        display.setCursor(20,20);
        display.print("FAILED");
        display.display();
       }
}

loopcounter ++;
displayloopnumber();
}

//-------------------------------------------------------------------------------------------------------
//Functions Under here
//-------------------------------------------------------------------------------------------------------

void oledinit(){
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.print("VeriSolutions");
display.display();
}

void oledinittest(){
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.print("VeriSolutions");
display.setCursor(20,0);
display.print("TIP: ");
display.display();
}


void oledprintdelay(int printdelay){
  display.setCursor(10,0);
  display.print("Delay Value: ");
  display.print(printdelay);
  display.display();
}

void displayloopnumber(){
  display.setCursor(20,80);
  display.print(loopcounter);
  display.display();
}

// This function returns 1 if the test passes and 0 if it fails
int runtest(){
  digitalWrite(relaypin, LOW); //Turn relay on
  delay(1000);
    bool voltagepinstate = digitalRead(voltagepin);
      if (voltagepinstate == HIGH){
        delay(1000);
        digitalWrite(relaypin, HIGH); //Should turn relay off
        return 1;
      }
      else {
        delay(1000);
        digitalWrite(relaypin, HIGH); //Should turn relay off
        return 0;
      }
}
