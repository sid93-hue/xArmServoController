#include <xArmServoController.h>

// define servo controller
xArmServoController xarm = xArmServoController(Serial1);

void setup() {  
  // initialize serial port
  Serial1.begin(9600);
}

void loop() {
  // define xArmServo object array
  xArmServo servos[] = {{1, 500},
                        {2, 500},
                        {3, 500}};
                        
  // turn off servos 1, 2 and 3
  xarm.servoOff(servos, 3);

  // loop here indefinately
  while (true) {}
}