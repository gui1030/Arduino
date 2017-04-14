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
unsigned long randNumber;
unsigned long timedelay = 10 * sec;
unsigned long previousmillis;
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
digitalWrite(relaypin, LOW);

delay(500);

}

/*
 * --LOOP----LOOP----LOOP----LOOP----LOOP----LOOP----LOOP----LOOP----LOOP----LOOP----LOOP----LOOP----LOOP----LOOP----LOOP--
 */

void loop() {

if (millis() - previousmillis > timedelay){

  oledinittest();
  oledprintdelay(timedelay);
  bool success = runtest();

    if (success == true){
       display.setCursor(40,20);
       display.print("  PASS");
       display.display();
       delay(2000);
      }

     while (success == false){
        display.setCursor(40,20);
        display.print("  FAILED");
        display.display();
        delay(2000);
       }

loopcounter ++;
oledinitloop();
oledprintdelay(timedelay);
previousmillis = millis();
}

}

//-------------------------------------------------------------------------------------------------------
//Functions Under here
//-------------------------------------------------------------------------------------------------------


void oledinit(){
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.println("VeriSolutions");
display.print("Starting...");
display.display();
}

void oledinittest(){
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.print("VeriSolutions");
display.setCursor(0,20);
display.print("Testing: ");
displayloopnumber();
display.display();
}

void oledinitloop(){
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.print("VeriSolutions");
oledprintdelay(timedelay);
displayloopnumber();
display.display();
}

void oledprintdelay(int printdelay){
  display.setCursor(0,10);
  display.print("Delay Value: ");
  display.print(printdelay/1000);
  display.print(" Sec");
  display.display();
}

void displayloopnumber(){
  display.setCursor(100,0);
  display.print(loopcounter);
  display.display();
}

// This function returns 1 if the test passes and 0 if it fails
int runtest(){
  digitalWrite(relaypin, HIGH); //Turn relay on
  delay(8000);
    bool voltagepinstate = digitalRead(voltagepin);
      if (voltagepinstate == HIGH){
        delay(1000);
        digitalWrite(relaypin, LOW); //Should turn relay off
        return 1;
      }
      else {
        delay(1000);
        digitalWrite(relaypin, LOW); //Should turn relay off
        return 0;
      }
}
