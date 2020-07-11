
# xArmServoController
XArm servo controller libraries

> This doc is in progress.

## Arduino

### Initialization

```cpp
	#define  rxPin  10
	#define  txPin  11  

	// define servo controller
	xArmServoController xarm =  xArmServoController(rxPin, txPin);
```
### Structures
```cpp
    struct xArmServo {
        uint8_t  id;
        uint16_t position;
        uint16_t duration;
    };
```
## Commands
### SetPosition
```cpp
void setPosition(uint8_t servo_id, uint16_t position, uint16_t duration, bool wait = false);
```
* **servo_id:** 8-bit ID of servo. Valid number are 1 through 31. The xArm has 6 servos numbered from 1 to 6 starting from the gripper.
* **position:** 16-bit position to move the servo to. Valid range is 0 to 1000.
* **duration:** 16-bit length of time in milliseconds to traverse the movement.
* **wait:** Optional boolean value when 'true' causes the function to wait until duration has elapsed before returning. When false, function returns immediately before xArm completes servo movement.

**Example 1**
```cpp
xArmServo servoStep1 {1, 200, 1000};
```
Moves servo ID 1 to position 200 and returns immediately. The servo will continue to move for the duration.

**Example 2**
```cpp
xArmServo servoStep1 {1, 200, 1000, true};
```
Moves servo ID 1 to position 200 and waits until duration has elapsed.

---
```cpp
void setPosition(xArmServo servo, bool wait = false);
```

* **servo:** A servo structure defining ID, position and duration.
* **wait:** Optional boolean value when 'true' causes the function to wait until duration has elapsed before returning. When false, function returns immediately before xArm completes servo movement.

**Examples**
```cpp
xArmServo servo1 {1, 200, 1000};
xarm.setPosition(servo1);
```
Moves servo ID 1 to position 200 and returns immediately. The servo will continue to move for the duration.
```cpp
xArmServo servo1 {1, 200, 1000};
xarm.setPosition(servo1, true);
```
Moves servo ID 1 to position 200 and waits until duration has elapsed.
```cpp
void setPosition(xArmServo servos[], uint8_t count, bool step = false);
```
