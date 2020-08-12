#include <xArmServoController.h>

// define servo controller
xArmServoController xarm = xArmServoController(Serial1);

void setup() {  
  // initialize serial console
  Serial.begin(9600);

  // initialize serial port
  Serial1.begin(9600);

  // wait for serial ports to initialize
  while (!Serial && !Serial1) {}
}

void loop() {
  // define xArmServo object
  xArmServo servo = {1, 500};

  // get servo 1's position
  int i = xarm.getPosition(servo);

  // print position to console
  Serial.print("\nServo 1 position: "); Serial.println(i, DEC);
  Serial.print("servo.servo_id:   "); Serial.println(servo.servo_id, DEC);
  Serial.print("servo.position:   "); Serial.println(servo.position, DEC);
  
  // loop here indefinately
  while (true) {}
}