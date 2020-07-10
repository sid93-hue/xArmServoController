#include "xArmServoController.h"

#define rxPin 10
#define txPin 11

// define servo controller
xArmServoController xarm = xArmServoController(rxPin, txPin);

xArmServo servoStep1 {1, 200, 1000};
xArmServo servoStep2 {1, 800, 1000};
xArmServo servoStep3 {1, 500, 1000};

xArmServo servos[] = {servoStep1, servoStep2, servoStep3};

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  xarm.setPosition(1, 200, 1000, true);
  xarm.setPosition(1, 800, 1000, true);
  xarm.setPosition(1, 500, 1000, true);
  delay (500);
  
  xarm.setPosition(servoStep1);
  delay(1000);
  xarm.setPosition(servoStep2);
  delay(1000);
  xarm.setPosition(servoStep3);
  delay(1500);
  
  xarm.setPosition(servos, sizeof(servos) / sizeof(servos[0]), true);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(250);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
  delay(800);                      // wait for a second
}
