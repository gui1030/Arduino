void setup() {
  // put your setup code here, to run once:
int button = 2;
int ledpin = 13;
  
pinMode(button, INPUT);
pinMode(ledpin, OUTPUT);
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

int val = 0;
int button = 4;
int ledpin = 13;

val = digitalRead(button);

if (val == HIGH){
digitalWrite(ledpin, HIGH);
}
else  {
  digitalWrite(ledpin, LOW);
}

Serial.println(val);

}
