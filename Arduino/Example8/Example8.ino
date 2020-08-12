#include <xArmServoController.h>

// define servo controller
xArmServoController xarm = xArmServoController(Serial1);

void setup() {
  // initialize serial port
  Serial1.begin(9600);
}

void loop() {  
  // turn off servos 1, 2 and 3
  xarm.servoOff(3, 1, 2, 3);

  // loop here indefinately
  while (true) {}
}