#include <xArmServoController.h>

// define servo controller
xArmServoController xarm = xArmServoController(Serial1);

void setup() {
  // initialize serial port
  Serial1.begin(9600);
}

void loop() {
  // turn off servo 1
  xarm.servoOff(1);

  // loop here indefinately
  while (true) {}
}