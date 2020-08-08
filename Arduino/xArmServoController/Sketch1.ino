#include "src/xArmServoController.h"

#define rxPin 10
#define txPin 11

// define servo controller
xArmServoController xarm = xArmServoController(rxPin, txPin);

xArmServo servoStep1 {1, 200, 1000};
xArmServo servoStep2 {1, 800, 1000};
xArmServo servoStep3 {1, 500, 1000};

xArmServo servos[] = {servoStep1, servoStep2, servoStep3};

xArmServo servo_id[] = {1, 2, 3};

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  xarm.setPosition(1, 200, 1000, true);
  xarm.setPosition(1, 800, 5000);

  delay (2500);
  
  xarm.off(servos, 3);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(100);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
  delay(500);                      // wait for a second
}
