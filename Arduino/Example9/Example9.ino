#include <xArmServoController.h>

// define servo controller
xArmServoController xarm = xArmServoController(Serial1);

void setup() {
  // initialize serial port
  Serial1.begin(9600);
}

void loop() {
  // define xArmServo object
  xArmServo servo = {1, 500};
  
  // turn off servo 1
  xarm.servoOff(servo);

  // loop here indefinately
  while (true) {}
}