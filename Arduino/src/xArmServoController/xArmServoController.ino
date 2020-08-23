#include "xArmServoController.h"

// define servo controller
xArmServoController xarm1 = xArmServoController(Serial1);
xArmServoController xarm2 = xArmServoController(Serial2);

void setup() {  
  // initialize serial console
  Serial.begin(9600);

  // initialize serial port
  Serial1.begin(9600);
  Serial2.begin(9600);

  // wait for serial ports to initialize
  while (!Serial && !Serial1 && !Serial2) {}
}

void loop() {
  xArmServo home[] = {{1, 620}, 
                      {2, 500}, 
                      {3, 130}, 
                      {4, 500}, 
                      {5, 500}, 
                      {6, 500}};

  xArmServo bow1[] = {{1, 620}, 
                      {2, 0}, 
                      {3, 150}, 
                      {4, 500}, 
                      {5, 500}, 
                      {6, 500}};

  xArmServo bow2[] = {{1, 620}, 
                      {2, 1000}, 
                      {3, 150}, 
                      {4, 500}, 
                      {5, 500}, 
                      {6, 500}};

  while(true) {  
    xarm1.setPosition(bow1, 6, 10000);
    xarm2.setPosition(bow1, 6, 10000);
    
    delay(12000);
  
    xarm1.setPosition(bow2, 6, 10000);
    xarm2.setPosition(bow2, 6, 10000);
  
    delay(12000);
  }
}
