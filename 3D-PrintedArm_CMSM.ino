
// Analog pins that each axis of the two joysticks are connected to
#define ROTATE 5 // duh
#define OUT 4 // left servo as the arm faces away
#define UP 3 // right servo as the arm faces away

// Digital pin for the gripper toggle switch
#define GRIP 2 // duh

// Digital pins that the servo signal wires are connected to
#define ROTATE_SERVO_PIN 6
#define OUT_SERVO_PIN 5
#define UP_SERVO_PIN 3
#define GRIP_SERVO_PIN 9

#include <Servo.h>

// Home positions
int rotatePos = 1500;
int outPos = 1500;
int upPos = 1500;
int gripPos = 1000;

int deadZone = 40; // Compensates for centering error
int speedMultiplier = 32; // Bigger is slower

int rotateStick, outStick, upStick, gripSwitch;

int servoMin = 700;
int servoMax = 2200;
int gripOpen = 2200;
int gripClosed = 1500;


Servo rotate;
Servo out;
Servo up;
Servo grip;

void setup()
{
  rotate.attach(ROTATE_SERVO_PIN);
  out.attach(OUT_SERVO_PIN);
  up.attach(UP_SERVO_PIN);
  grip.attach(GRIP_SERVO_PIN);
  pinMode(GRIP, INPUT_PULLUP);
}

void loop()
{
  // Each of the three axes are read, and the distance from center is calculated. 
  // If inside the deadzone, the value is zeroed/ignored. 
  // Then the position of the servo is incremented (with a constant to control speed), and constrained to the range of the servo (value is in microseconds)
  // The sticks control velocity, not position

  rotateStick = analogRead(ROTATE)-512;
  if (abs(rotateStick)<deadZone) {
    rotateStick = 0;
  }
  rotatePos+=rotateStick/speedMultiplier;
  rotatePos = constrain(rotatePos, servoMin, servoMax);

  outStick = analogRead(OUT)-512;
  if (abs(outStick)<deadZone) {
    outStick = 0;
  }
  outPos-=outStick/speedMultiplier;
  outPos = constrain(outPos, servoMin, servoMax);

  upStick = analogRead(UP)-512;
  if (abs(upStick)<deadZone) {
    upStick = 0;
  }
  upPos-=upStick/speedMultiplier;
  upPos = constrain(upPos, servoMin, servoMax);

  // The gripper is in one of two positions, opened or closed, controlled by a toggle switch
  gripSwitch = digitalRead(GRIP);
  if (gripSwitch) {
    gripPos = gripOpen;
  } else {
    gripPos = gripClosed;
  }
  
  // Finally, the positions are written to the servos, with a small delay at the end of the loop
  rotate.write(rotatePos);
  out.write(outPos);
  up.write(upPos);
  grip.write(gripPos);
  delay(10);
}
