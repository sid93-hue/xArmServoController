#include <xArmServoController.h>

// define servo controller
xArmServoController xarm = xArmServoController(Serial1);

void setup() {
  // initialize serial port
  Serial1.begin(9600);
}

void loop() {
  // define and initialize xArmServo object array
  xArmServo servos[] = {{1, 500}, 
                        {2, 500}};
  
  // set servo 1 and 2 to position 500
  xarm.setPosition(servos, 2);

  // loop here indefinately
  while (true) {}
}