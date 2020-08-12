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
  // get the battery voltage
  int i = xarm.getBatteryVoltage();

  // print positions to console
  Serial.print("\nBattery voltage(mv): "); Serial.println(i, DEC);

  // loop here indefinately
  while (true) {}
}