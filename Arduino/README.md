# Arduino xArmServoController

xArm servo controller library for Arduino.

This work is in progress is frequently changes.

## Table of Contents

* [Installation](#installation)
* [Setup](#setup)
* [xArmServo Structure](<#xarmservo-structure>)
* [xArmServo Object Initialization](<#xarmServo-object-initialization>)
* [Commands](#commands)
	* [SetPosition](#setposition)
	* [GetPosition](#getposition)
	* [ServoOff](#servooff)
	* [GetBatteryVoltage](#getbatteryvoltage)

## Installation

1. Download or clone the [xArmServoController project on GitHub](https://github.com/ccourson/xArmServoController).
1. Copy the _xArmServoController libraries_ folder from this project into the _Arduino libraries_ folder. This is usually located at C:\ProgramFiles(86\Arduino\libraries.
1. Open an Arduino example sketch with [Arduino IDE](https://www.arduino.cc/).

## Setup

### Initialization

The _xArmServoController object_ requires one parameter, the hardware or software serial port to which the xArm is connected. The baud rate must be set to 9600.

For hardware serial definitions, refer to [Arduino Serial Communication](https://www.arduino.cc/reference/en/language/functions/communication/serial/).

For software serial configuration, refer to [Arduino SoftwareSerial Library](https://www.arduino.cc/en/Reference/SoftwareSerial).

Example HardwareSerial initialization code:
```arduino
#include <xArmServoController.h>

// define servo controller
xArmServoController xarm = xArmServoController(Serial1);

void setup() {
  // initialize serial port
  Serial1.begin(9600);
  // Your setup here.
}

void loop() {
  // Your code here.
}
```

Example SoftwareSerial initialization code:
```arduino
#include <SoftwareSerial.h>
#include <xArmServoController.h>

// define servo controller
#define rxPin 10
#define txPin 11
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);
xArmServoController xarm = xArmServoController(mySerial);

void setup() {
  // initialize serial port
  mySerial.begin(9600);
  // Your setup here.
}

void loop() {
  // Your code here.
}
```

### xArmServo Structure

The xArmServoController library exposes global structure **xArmServo** that is used by some functions.

xArmServo Object:
```cpp
struct xArmServo {
	uint8_t id;
	uint16_t position;
};
```

### xArmServo Object Initialization

Example 1:
```arduino
#include <xArmServoController.h>

// define servo controller
xArmServoController xarm = xArmServoController(Serial1);
// define xArmServo object
xArmServo servo;

void setup() {
  // initialize serial port
  Serial1.begin(9600);

  // initialize xArmServo object
  servo.servo_id = 1;
  servo.position = 500;
}

void loop() {
  // set servo 1 to position 500
  xarm.setPosition(servo);

  // loop here indefinately
  while (true) {}
}
```
Example 2:
```arduino
#include "xArmServoController.h"

// define servo controller
xArmServoController xarm = xArmServoController(Serial1);
// define xArmServo object
xArmServo servo;

void setup() {
  // initialize serial port
  Serial1.begin(9600);

  // initialize xArmServo object
  servo = {1, 500};
}

void loop() {
  // set servo 1 to position 500
  xarm.setPosition(servo);

  // loop here indefinately
  while (true) {}
}
```

## Commands

### SetPosition

Sets the position(s) of the specified servo(s). Optionally returns after duration has elapsed.

```cpp
void setPosition(uint8_t servo_id, uint16_t position, uint16_t duration = 1000, bool wait = false);
```

Set one servo's position by servo ID. Optionally specify duration and wait.

Parameters:

* **servo_id**: The ID number (1 - 6) of the servo.
* **position**: The position (0 - 1000) to set the servo to.
* **duration**: (optional) The length of time in milliseconds (0 - 3000) to traverse the servo movement. By default, the duration is 1000 milliseconds.
* **wait**: (optional) When true, the function will return after duration has elapsed. By default, the function will return immediately and servo movement will continue for the duration.

Returns:

* Nothing.

Examples:

* [Example1.ino](Example1/Example1.ino)

```cpp
void setPosition(xArmServo servo, uint16_t duration = 1000, bool wait = false);
```

Set one servo's position by xArmServo object. Optionally specify duration and wait.

Parameters:

* **servo**: The xArmServo object defining servo ID and position of the servo.
* **duration**: (optional) The length of time in milliseconds (0 - 3000) to traverse the servo movement. By default, the duration is 1000 milliseconds.
* **wait**: (optional) When true, the function will return after duration has elapsed. By default, the function will return immediately and servo movement will continue for the duration.

Returns:

* Nothing.

Examples:

* [Example2.ino](Example2/Example2.ino)

```cpp
void setPosition(xArmServo servos[], size_t count, uint16_t duration = 1000, bool wait = false);
```

Set one or more servos' positions by and array of xArmServo object. Optionally specify duration and wait.

Parameters:

* **servos[]**: An array of one or more xArmServo objects defining servo ID and position of each servo.
* **count**: The number of servos in the servos array.
* **duration**: (optional) The length of time in milliseconds (0 - 3000) to traverse the servo movement. By default, the duration is 1000 milliseconds.
* **wait**: (optional) When true, the function will return after duration has elapsed. By default, the function will return immediately and servo movement will continue for the duration.

Returns:

* Nothing.

Examples:

* [Example3.ino](Example3/Example3.ino)

### GetPosition

Gets the position(s) of the specified servo(s).

```cpp
uint16_t getPosition(uint8_t servo_id);
```

Gets the position of one servo specified by servo_id.

Parameters:

* **servo_id**: The ID number (1 - 6) of the servo.

Returns:

* The current position of the servo (0 - 1000).
* If the position cannot be read, it will return -1;

Examples:

* [Example4.ino](Example4/Example4.ino)

```cpp
uint16_t getPosition(xArmServo &servo);
```

Gets the position of one servo specified by xArmServo servo object. The position is returned by the funtion and also stored in the servo object.

Parameters:

* **servo**: The xArmServo object specifying the servo.

Returns:

* The current position of the servo (0 - 1000).
* The position is also stored in the xArmServo object.
* If the position cannot be read, it will return and store -1;

Examples:

* [Example5.ino](Example5/Example5.ino)

```cpp
bool getPosition(xArmServo servos[], size_t count);
```

Gets the position of one or more servos specified by an array of xArmServo servo object. Success is returned by returned the funtion. Positions of each servo is stored in each servo object in the array.

Parameters:

* **servos[]**: An array of one or more xArmServo objects specifying the servos.
* **count**: The number of xArmServo objects in the array.

Returns:

* False if the position cannot be read.
* The position of each servo is stored in the respective xArmServo object in the array.

Examples:

* [Example6.ino](Example6/Example6.ino)

### ServoOff

Turns off motor of the specified servo(s).

```cpp
void servoOff(uint8_t servo_id);
```

Turns off motor of one servo specified by servo ID.

Parameters:

* **servo_id**: The ID number (1 - 6) of the servo.

Returns:

* Nothing.

Examples:

* [Example7.ino](Example7/Example7.ino)

```cpp
void servoOff(int num, int servo_id, ...);
```

Turns off motor of one or more servos specified by servo_ids.

Parameters:

* **num**: Number of servo IDs in list.
* **servo_ids[]**: An a list of one or more servo_ids.

Returns:

* Nothing.

Examples:

* [Example8.ino](Example8/Example8.ino)

```cpp
void servoOff(xArmServo servo);
```

Turns off motor of one servo specified by xArmServo object.

Parameters:

* **servo**: An xArmServo object specifying the servo.

Returns:

* Nothing.

Examples:

* [Example9.ino](Example9/Example9.ino)

```cpp
void servoOff(xArmServo servos[], size_t count);
```

Turns off motor of one or more servos specified by an array of xArmServo object.

Parameters:

* **servos[]**: An array of one or more xArmServo objects defining servo ID and position of each servo.
* **count**: The number of servos in the servos array.

Returns:

* Nothing.

Examples:

* [Example10.ino](Example10/Example10.ino)

```cpp
void servoOff();
```

Turns off all servo motors (1 - 6).

Parameters:

* Nothing.

Returns:

* Nothing.

Examples:

* [Example11.ino](Example11/Example11.ino)

### GetBatteryVoltage

Gets the battery or power supply voltage.

```cpp
uint16_t getBatteryVoltage();
```
If the xArm is powered by the supplied power brick, it will return the voltage which is around 7.6 VDC (7600 mv).

Parameters:

* Nothing.

Returns:

* Battery voltage in millivolts. Range is 4500 to 12000 mv.

Examples:

* [Example12.ino](Example12/Example12.ino)