#include <TinyGPS++.h>




TinyGPSPlus gps;


void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:


while (Serial.available() > 0){
    gps.encode(Serial.read());

}


Serial.print("LAT="); 

Serial.println(gps.location.lat(), 6);

Serial.print("LONG=");

Serial.println(gps.location.lng(), 6);

Serial.print("ALT="); 

Serial.println(gps.altitude.meters());

delay(1000);

}
