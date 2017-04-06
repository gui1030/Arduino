void setup() {
  // put your setup code here, to run once:

 const int x = 0;
 const int y = 1;
  
  Serial.begin(9600);
  

}

void loop() {
  // put your main code here, to run repeatedly:
int xval = 0;
int yval = 0;
int xdir = 0;
int ydir = 0;   //default 

xval = analogRead(0);
yval = analogRead(1);

xval = map(xval, 0, 1024, 0, 100);
  
xval = xval - 49;

if (xval < 0)
{

//set the motor direction to reverse (right/left)
xdir = 1;

  
}

else {
//set the motor direction to forward (right/left)
xdir = 0;
  
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

delay(400);   //For stability


}
