#include <xArmServoController.h>

// define servo controller
xArmServoController xarm = xArmServoController(Serial1);

// define xArmServo object
xArmServo servo;

void setup() {
  // initialize serial port
  Serial1.begin(9600);

  // initialize xArmServo object
  servo = {1, 500};
}

void loop() {
  // set servo 1 to position 500
  xarm.setPosition(servo);

  // loop here indefinately
  while (true) {}
}
