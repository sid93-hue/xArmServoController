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
  // define xArmServo object array
  xArmServo servos[] = {{1, 500},
                        {2, 500},
                        {3, 500},
                        {4, 500},
                        {5, 500},
                        {6, 500}};
                        
  // get servos' positions
  int i = xarm.getPosition(servos, 6);

  // print positions to console
  Serial.print("\ngetPosition returned: "); Serial.println(i == 1 ? "True" : "False");
  Serial.println("Servo\tPosition");
  for (int i = 0; i < 6; i++) {
    Serial.print(servos[i].servo_id, DEC);
    Serial.print("\t");
    Serial.println(servos[i].position, DEC);
  }
  
  // loop here indefinately
  while (true) {}
}