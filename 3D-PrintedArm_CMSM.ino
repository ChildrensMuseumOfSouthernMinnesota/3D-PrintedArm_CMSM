#define ROTATE 5
#define OUT 4
#define UP 3
#define GRIP 2

#include "PololuMaestro.h"

#include <SoftwareSerial.h>
SoftwareSerial maestroSerial(4, 5);
MicroMaestro maestro(maestroSerial);
int rotatePos = 6000;
int outPos = 6000;
int upPos = 6000;
int gripPos = 6000;

int deadZone = 40;

int rotateStick, outStick, upStick;
int gripSwitch;

void setup()
{
  maestroSerial.begin(9600);
  Serial.begin(9600);
  pinMode(GRIP, INPUT_PULLUP);
}

void loop()
{
  rotateStick = analogRead(ROTATE)-512;
  if (abs(rotateStick)<deadZone) {
    rotateStick = 0;
  }
  rotatePos+=rotateStick/10;
  rotatePos = constrain(rotatePos, 4000, 8000);

  outStick = analogRead(OUT)-512;
  if (abs(outStick)<deadZone) {
    outStick = 0;
  }
  outPos+=outStick/10;
  outPos = constrain(outPos, 4000, 8000);

  upStick = analogRead(UP)-512;
  if (abs(upStick)<deadZone) {
    upStick = 0;
  }
  upPos+=upStick/10;
  upPos = constrain(upPos, 4000, 8000);

  gripSwitch = digitalRead(GRIP);
  if (gripSwitch) {
    gripPos = 8000;
  } else {
    gripPos = 4000;
  }
  delay(10);
  //Serial.println(upStick);
  maestro.setTarget(ROTATE, rotatePos);
  maestro.setTarget(OUT, outPos);
  maestro.setTarget(UP, upPos);
  maestro.setTarget(GRIP, gripPos);
  
}
