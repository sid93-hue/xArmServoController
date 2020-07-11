# Arduino xArmServoController

xArm servo controller library for Arduino.

## Table of Contents

*  [Installation](#installation)
*  [Setup](setup)
*  [Initialization](#initialization)
*   [Commands](#commands)
	* [SetPosition](#setposition)

## Installation

Download or clone the [xArmServoController project on GitHub](https://github.com/ccourson/xArmServoController). Open the `Arduino/xArmServoController.ino` file with [Arduino IDE](https://www.arduino.cc/).

## Setup

The examples in this documentation use the following connections.



## Initialization

```cpp
#define rxPin 10
#define txPin 11

// define servo controller
xArmServoController xarm = xArmServoController(rxPin, txPin);
```

### Structures

```cpp
struct xArmServo {
	uint8_t id;
	uint16_t position;
	uint16_t duration;
};
```

## Commands

### SetPosition

SetPosition has three [overloads](https://en.wikipedia.org/wiki/Function_overloading). The first takes parameters to specify the servo ID, position, duration and optionally a wait flag. The wait flag controls if the function is [blocking or non-blocking](https://en.wikipedia.org/wiki/Blocking_(computing)).

The second two forms of SetPosition use a structure (struct) object to hold the servo ID, position and duration parameters. The xArmServo object is used either alone or in an array. When passed alone, an optional wait flag controls if the function will block. When the xArmServo object is passed in an array, an optional step flag, when 'true', will cause the function to perform each servo movement in-turn and in the order specified and will block until each duration has completed. When the step flag is 'false', all of the servo movements are sent and the function returns immediately, before movement has completed.

Subsequent non-blocking SetPosition commands will override the command being performed by the xArm.

```cpp
void setPosition(uint8_t servo_id, uint16_t position, uint16_t duration[, bool wait = false]);
```

```cpp
void setPosition(xArmServo servo[, bool wait = false]);
```

```cpp
void setPosition(xArmServo servos[], uint8_t count[, bool step = false]);
```

| Parameter | Description |
|---|---|
|servo_id | 8-bit ID of servo. Valid range is 1 through 31. The xArm has 6 servos numbered from 1 to 6 starting from the gripper.
|servo | An [xArmServo struct](#structures) defining servo ID, position and duration.
|position | 16-bit position to move the servo to. Valid range is 0 to 1000.
|duration | 16-bit length of time in milliseconds to traverse the movement.
|wait | Optional boolean value when 'true' causes the function to wait until duration has elapsed before returning. When 'false', returns immediately. xArm will continue servo movement.
|count | When passing an array of xArmServo objects, specifies the number of objects. Arduino c++ cannot determine the number of objects in an array.
|step | Optional boolean value when 'true' causes the function to wait until duration has elapsed before sending the next action. When 'false', will send all actions to the xArm to perform simultaneously and returns immediately.

**Example 1**

```cpp
xArm.SetPosition{1, 200, 1000};
```
Moves servo ID 1 to position 200 and returns immediately. The servo will continue to move for the duration specified.

**Example 2**
```cpp
xArm.SetPosition{1, 200, 1000, true};
```
Moves servo ID 1 to position 200 and returns after duration (1000ms) has elapsed.

**Example 3**
```cpp
xArmServo servo1 {1, 200, 1000};
xArm.SetPosition(servo1);
```
Servo movement is defined by object servo1. Moves servo ID 1 to position 200 and returns immediately. The servo will continue to move for the duration specified.

**Example 4**
```cpp
xArmServo servo1 {1, 200, 1000};
xArm.SetPosition(servo1, true);
```
Servo movement is defined by object servo1. Moves servo ID 1 to position 200 and returns after duration (1000ms) has elapsed.

**Example 5**
```cpp
xArmServo servo1 {1, 200, 1000};
xArmServo servo2 {2, 400, 1000};
xArmServo servo3 {3, 600, 1000};

xArmServo servos[] = {servo1, servo2, servo3};

void  setPosition(xArmServo servos[], sizeof(servos) / sizeof(servos[0]) );
```
Servo movements are defined by an array of xArmServo objects. Sends all actions to the xArm to perform simultaneously and returns immediately.

**Example 6**
```cpp
xArmServo servo1 {1, 200, 1000};
xArmServo servo2 {2, 400, 1000};
xArmServo servo3 {3, 600, 1000};

xArmServo servos[] = {servo1, servo2, servo3};

void  setPosition(xArmServo servos[], sizeof(servos) / sizeof(servos[0]), true);
```
Servo movements are defined by an array of xArmServo objects. Sends each action in turn and waits for it to complete before sending the next action. Performs each action individually and returns when all actions have completed.
