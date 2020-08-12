#include <xArmServoController.h>

// define servo controller
xArmServoController xarm = xArmServoController(Serial1);

void setup() {
  // initialize serial port
  Serial1.begin(9600);
}

void loop() {
  // set servo 1 to position 500
  xarm.setPosition(1, 200);

  // loop here indefinately
  while (true) {}
}
