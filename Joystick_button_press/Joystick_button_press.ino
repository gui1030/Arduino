#include <Esplora.h>


void setup(){
  // nothing in setup
} 

void loop()
{
  int button = Esplora.readJoystickButton();

  if(button == LOW)
  {
    Esplora.writeRed(255);
  }
  else {
    Esplora.writeRed(0);
  }
}
