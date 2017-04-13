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

void oledresult(int testresult){

}
