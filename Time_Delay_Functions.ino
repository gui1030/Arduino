//Time Delay functions



void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
unsigned long previousMillis;
unsigned long currentMillis = millis();
unsigned long timeinterval = 10000;
    // Read the sensor when needed.
    if (currentMillis - previousMillis > timeinterval) {
        previousMillis = currentMillis;
        Serial.println("TimeLapse");
        
    }
}



  


