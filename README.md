# xArmServoController
XArm servo controller libraries

> This doc is in progress.

## Arduino

### Initialization

	#define  rxPin  10
	#define  txPin  11  

	// define servo controller
	xArmServoController xarm =  xArmServoController(rxPin, txPin);

### Structures

    struct xArmServo {
        uint8_t  id;
        uint16_t position;
        uint16_t duration;
    };

### SetPosition
> void setPosition(uint8_t servo_id, uint16_t position, uint16_t duration, bool wait = false);

**servo_id:** ID of servo

**Examples**
Moves servo ID 1 to position 200 and returns immediately.

	xArmServo servoStep1 {1, 200, 1000};

Moves servo ID 1 to position 200 and waits until duration has expired.

	xArmServo servoStep1 {1, 200, 1000, true};




void setPosition(xArmServo servo, bool wait = false);

	xarm.setPosition(servoStep1);

xarm.setPosition(servoStep1, true);

void setPosition(xArmServo servos[], uint8_t count, bool step = false);
