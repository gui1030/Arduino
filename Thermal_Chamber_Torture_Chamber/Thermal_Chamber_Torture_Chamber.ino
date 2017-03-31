/*This code is for creating a thermal chamber/torture chamber for humidity/temp 
 * Using DHT22 sensors (DHT11 for testing)
 * 3.5 TFT touchscreen as user interface
 * 4 sensors
 * 2 relay switches (One for fan/One for Humidifier)

*/
//Included Libraries
#include "DHT.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <SPI.h>
#include "Adafruit_HX8357.h"
#include "TouchScreen.h"


//Static Variables
int fanmode;
int lowhumiditythreshold = 80;
int thresholdoffset = 10;
#define debugmode "DISABLED"

//Define Humidity Sensor Pins
#define humiditypin1 3
#define humiditypin2 4
#define humiditypin3 5
#define humiditypin4 6

//Define sensor type
#define DHTTYPE DHT22

DHT dht1(humiditypin1, DHTTYPE);
DHT dht2(humiditypin2, DHTTYPE);
DHT dht3(humiditypin3, DHTTYPE);
DHT dht4(humiditypin4, DHTTYPE);

//Define Relay pins
#define fanrelaypin A0
#define humidifierrelaypin A1

//Define Touchscreen analog pins
#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 8   // can be a digital pin

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 110
#define TS_MINY 80
#define TS_MAXX 900
#define TS_MAXY 940

#define MINPRESSURE 200
#define MAXPRESSURE 1000

// The display uses hardware SPI, plus #9 & #10
#define TFT_RST -1  // dont use a reset pin, tie to arduino RST if you like
#define TFT_DC 9
#define TFT_CS 10

Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
int xplateresistance = 264;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, xplateresistance);

// Size of the color selection boxes and the paintbrush size
#define BOXWIDTH 115
#define BOXHEIGHT 80

//Timekeeping variables
unsigned long previousMillis;
unsigned long previousdebugMillis;
unsigned long previoushumidifierMillis;
#define readinterval 10000
#define humidifierinterval 20000
int startupdelay = 500;
#define debuginterval 2000


void setup() {

//Initialize COMs
Serial.begin(9600);
dht1.begin();
dht2.begin();
dht3.begin();
dht4.begin();

Serial.println("Starting...");
Serial.print("Debugging: ");
Serial.println(debugmode);
delay(startupdelay);

displayinitialize(startupdelay);

//Initialize Relays
pinMode(fanrelaypin, OUTPUT);
pinMode(humidifierrelaypin, OUTPUT);
digitalWrite(fanrelaypin, HIGH);
digitalWrite(humidifierrelaypin, HIGH);


}

void loop() {
  
int calculatedaveragehumidity = 235; //To know when a read is initial and not turn on humid/fan
// Read the sensor when needed.
  if (millis() - previousMillis > readinterval) {
    tft.setTextSize(3);
    tft.fillRect(88, 0, 145, 25, HX8357_BLACK);
    tft.setCursor(90,0);
    tft.setTextColor(HX8357_GREEN);
    tft.print("AQUIRING");
    tft.setTextSize(2);
    refreshtft();
    calculatedaveragehumidity = updatesensorreadings();
    Serial.print("Calculated:  ");
    Serial.println(calculatedaveragehumidity);
    previousMillis = millis(); 
      
   }

int highhumiditythreshold = lowhumiditythreshold + thresholdoffset;
   
if (fanmode == 2 && calculatedaveragehumidity > highhumiditythreshold){
digitalWrite(fanrelaypin, LOW);
}

if (fanmode == 2 && calculatedaveragehumidity < highhumiditythreshold){
digitalWrite(fanrelaypin, HIGH);
}

if (calculatedaveragehumidity != 235){

  if (calculatedaveragehumidity > lowhumiditythreshold){
  digitalWrite(humidifierrelaypin, HIGH); 
  }

  if (calculatedaveragehumidity < lowhumiditythreshold){
  digitalWrite(humidifierrelaypin, LOW);
  
  }
}

// Retrieve a point  
  TSPoint p = ts.getPoint();   
  if (p.z < MINPRESSURE || p.z > MAXPRESSURE) {
     return;
  } 
  // Scale from ~0->1000 to tft.width using the calibration #'s
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());


//Adding in Up button
if (p.x < 170 && p.y < 380){
  Serial.print("UP!");
  delay(500);
  }

//Adding in Down button
if (p.x < 170 && p.y > 390){
  Serial.print("DOWN!");
  delay(500);
  }

// Fan button pushed (3 Different States)
if (p.x > 200 && p.y > 400)
{ 

fanmode++;

if (fanmode == 1){
tft.fillRect(180, 420, 115, BOXHEIGHT/2, HX8357_RED);
tft.setCursor(195, 428);
tft.print("Fan OFF");
digitalWrite(fanrelaypin, HIGH);
}

else if (fanmode == 2){
tft.fillRect(180, 420, 115, BOXHEIGHT/2, HX8357_GREEN);
tft.setCursor(195, 428);
tft.print("Fan ON");
digitalWrite(fanrelaypin, LOW);

}

else if (fanmode == 0){
tft.fillRect(180, 420, 115, BOXHEIGHT/2, HX8357_BLUE);
tft.setCursor(195, 428);
tft.print("Fan AUTO");

}
else if (fanmode == 3){
  fanmode = -1;
}

delay(500); //debounce delay 

if (debugmode == "ENABLED"){debug(fanmode);}
}
}

//----------------------------------------------------------------------
//All functions listed under here

//This function sets up the Display
void displayinitialize(int startupdelay){
  
tft.begin(HX8357D);
tft.fillScreen(HX8357_WHITE);
tft.setCursor(30,40);
tft.setTextSize(3);
tft.setTextColor(HX8357_BLACK);
tft.println("Thermal Chamber");
tft.setTextSize(2);
tft.setCursor(30,80);
tft.print("Starting");
  
  //Create Boxes
tft.fillRect(20, 120, BOXWIDTH, BOXHEIGHT, HX8357_BLACK);
tft.print(".");
delay(startupdelay);
tft.fillRect(180, 120, BOXWIDTH, BOXHEIGHT, HX8357_BLACK);
tft.print(".");
delay(startupdelay);
tft.fillRect(20, 220, BOXWIDTH, BOXHEIGHT, HX8357_BLACK);
tft.print(".");
delay(startupdelay);
tft.fillRect(180, 220, BOXWIDTH, BOXHEIGHT, HX8357_BLACK);
tft.print(".");
delay(startupdelay);
tft.fillRect(180, 320, BOXWIDTH, BOXHEIGHT, HX8357_BLACK);
tft.print(".");
delay(startupdelay);
tft.fillRect(180, 420, BOXWIDTH, BOXHEIGHT/2, HX8357_BLUE);
tft.print(".");
delay(startupdelay);


tft.fillRect(115, 320, 50, 60, HX8357_BLUE);
tft.print(".");
delay(startupdelay);
tft.fillRect(115, 400, 50, 60, HX8357_BLUE);
tft.print(".");
delay(startupdelay);



//Fill in Text
tft.setCursor(21, 121);
tft.setTextColor(HX8357_CYAN);
tft.print("Sensor 1");
tft.setTextColor(HX8357_WHITE);
tft.setCursor(21, 141);
tft.print("Temp: ");
tft.setCursor(21, 161);
tft.print("Hum: ");

tft.setCursor(181, 121);
tft.setTextColor(HX8357_CYAN);
tft.print("Sensor 2");
tft.setTextColor(HX8357_WHITE);
tft.setCursor(181, 141);
tft.print("Temp: ");
tft.setCursor(181, 161);
tft.print("Hum: ");

tft.setCursor(21, 221);
tft.setTextColor(HX8357_CYAN);
tft.print("Sensor 3");
tft.setTextColor(HX8357_WHITE);
tft.setCursor(21, 241);
tft.print("Temp: ");
tft.setCursor(21, 261);
tft.print("Hum: ");

tft.setCursor(181, 221);
tft.setTextColor(HX8357_CYAN);
tft.print("Sensor 4");
tft.setTextColor(HX8357_WHITE);
tft.setCursor(181, 241);
tft.print("Temp: ");
tft.setCursor(181, 261);
tft.print("Hum: ");

tft.setCursor(181, 321);
tft.setTextColor(HX8357_CYAN);
tft.print("Average");
tft.setTextColor(HX8357_WHITE);
tft.setCursor(181, 341);
tft.print("Temp: ");
tft.setCursor(181, 361);
tft.print("Hum: ");

tft.setCursor(200, 428);
tft.print("Fan AUTO");

tft.setCursor(127, 335);
tft.print("UP");
tft.setCursor(117, 415);
tft.print("DOWN");

tft.setTextSize(2);
tft.setTextColor(HX8357_BLACK);
tft.setCursor(2, 320);
tft.print("Humidity");
tft.setCursor(1, 340);
tft.print("Thresh:");

tft.setCursor(40, 380);
tft.print(" %RH");

tft.setCursor(20, 380);
tft.print(lowhumiditythreshold);


tft.fillRect(10, 80, 300, 40, HX8357_WHITE); //To erase the "starting" text
}






//This refresh does not affect the Fan on/off indicator 
void refreshtft(){
  //Create Boxes
tft.fillRect(40, 120, BOXWIDTH, BOXHEIGHT, HX8357_BLACK);
tft.fillRect(200, 120, BOXWIDTH, BOXHEIGHT, HX8357_BLACK);
tft.fillRect(40, 220, BOXWIDTH, BOXHEIGHT, HX8357_BLACK);
tft.fillRect(200, 220, BOXWIDTH, BOXHEIGHT, HX8357_BLACK);
tft.fillRect(200, 320, BOXWIDTH, BOXHEIGHT, HX8357_BLACK);

//Fill in Text
tft.setCursor(21, 121);
tft.setTextColor(HX8357_CYAN);
tft.print("Sensor 1");
tft.setTextColor(HX8357_WHITE);
tft.setCursor(21, 141);
tft.print("Temp: ");
tft.setCursor(21, 161);
tft.print("Hum: ");

tft.setCursor(181, 121);
tft.setTextColor(HX8357_CYAN);
tft.print("Sensor 2");
tft.setTextColor(HX8357_WHITE);
tft.setCursor(181, 141);
tft.print("Temp: ");
tft.setCursor(181, 161);
tft.print("Hum: ");

tft.setCursor(21, 221);
tft.setTextColor(HX8357_CYAN);
tft.print("Sensor 3");
tft.setTextColor(HX8357_WHITE);
tft.setCursor(21, 241);
tft.print("Temp: ");
tft.setCursor(21, 261);
tft.print("Hum: ");

tft.setCursor(181, 221);
tft.setTextColor(HX8357_CYAN);
tft.print("Sensor 4");
tft.setTextColor(HX8357_WHITE);
tft.setCursor(181, 241);
tft.print("Temp: ");
tft.setCursor(181, 261);
tft.print("Hum: ");

tft.setCursor(181, 321);
tft.setTextColor(HX8357_CYAN);
tft.print("Average");
tft.setTextColor(HX8357_WHITE);
tft.setCursor(181, 341);
tft.print("Temp: ");
tft.setCursor(181, 361);
tft.print("Hum: ");

tft.setCursor(127, 335);
tft.print("UP");
tft.setCursor(117, 415);
tft.print("DOWN");

}

float updatesensorreadings(){
        
        float h1 = dht1.readHumidity(4);
        float h2 = dht2.readHumidity(4);
        float h3 = dht3.readHumidity(4);
        float h4 = dht4.readHumidity(4);
        
        float t1 = dht1.readTemperature(4);
        float t2 = dht2.readTemperature(4);
        float t3 = dht3.readTemperature(4);
        float t4 = dht4.readTemperature(4);
        
        float averagehumidity = (h1 + h2 + h3 + h4) / 4;
        float averagetemp = (t1 + t2 + t3 + t4) / 4;

          // Print Values to TFT screen 
          tft.setTextSize(2);
          tft.setTextColor(HX8357_WHITE);
          tft.setCursor(91, 141);
          tft.print(t1);
          tft.setCursor(91, 161);
          tft.print(h1);

          tft.setCursor(251, 141);
          tft.print(t2);
          tft.setCursor(251, 161);
          tft.print(h2);

          tft.setCursor(91, 241);
          tft.print(t3);
          tft.setCursor(91, 261);
          tft.print(h3);

          tft.setCursor(251, 241);
          tft.print(t4);
          tft.setCursor(251, 261);
          tft.print(h4);

          tft.setCursor(251, 341);
          tft.print(averagetemp);
          tft.setCursor(251, 361);
          tft.print(averagehumidity); 

 
          
          tft.fillRect(88, 0, 145, 25, HX8357_WHITE);

return averagehumidity;
}

void debug(int fanmode){
// Serial printing for debugging
  if (millis() - previousdebugMillis > debuginterval) {  
    previousdebugMillis = millis();
    
        int h1 = dht1.readHumidity();
        int h2 = dht2.readHumidity();
        int h3 = dht3.readHumidity();
        int h4 = dht4.readHumidity();
        
        int t1 = dht1.readTemperature();
        int t2 = dht2.readTemperature();
        int t3 = dht3.readTemperature();
        int t4 = dht4.readTemperature();
        
        int averagehumidity = (h1 + h2 + h3 + h4) / 4;
        int averagetemp = (t1 + t2 + t3 + t4) / 4;
        
   Serial.println("\n");
        Serial.println("\n");
        Serial.println("Humidity (RH%)            Temperature (C)            Average Temp          Average Humidity");
        Serial.println("1    2    3    4          1    2    3    4    ");
        Serial.print(h1);   
        Serial.print("%  "); 
        Serial.print(h2);   
        Serial.print("%  "); 
        Serial.print(h3);   
        Serial.print("%  "); 
        Serial.print(h4);   
        Serial.print("%        "); 
        Serial.print(t1);   
        Serial.print("   "); 
        Serial.print(t2);   
        Serial.print("   "); 
        Serial.print(t3);   
        Serial.print("   "); 
        Serial.print(t4);   
        Serial.print("              "); 
        Serial.print(averagetemp);
        Serial.print("                       "); 
        Serial.print(averagehumidity);
        Serial.print("%");
        Serial.println("\n");  
        Serial.println("\n");  
  }
TSPoint p = ts.getPoint();
 
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z < MINPRESSURE || p.z > MAXPRESSURE) {
     return;
  } 
   
  // Scale from ~0->1000 to tft.width using the calibration #'s
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

  Serial.print("X = "); Serial.print(p.x);
  Serial.print("\tY = "); Serial.print(p.y);
  Serial.print("\tPressure = "); Serial.println(p.z);
  Serial.println("  ");     
  Serial.println("  ");
  Serial.print("Fanstate:  ");
  Serial.println(fanmode);
  Serial.println("  "); 
        
}
