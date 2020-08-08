/*
  xArmServoController.h - Library for controlling xArm servos.
  Created by Chris Courson, July 9, 2020.
  Released into the public domain.
*/
#pragma once
#ifndef XARMSERVOCONTROLLER_H
#define XARMSERVOCONTROLLER_H

#include <Arduino.h>
#include <SoftwareSerial.h>

#define SIGNATURE               0x55

#define CMD_SERVO_MOVE          0x03
#define CMD_SERVO_STOP          0x14
//#define CMD_ACTION_GROUP_RUN    0x06
//#define CMD_ACTION_GROUP_STOP   0x07
//#define CMD_ACTION_GROUP_SPEED  0x0B
//#define CMD_GET_BATTERY_VOLTAGE 0x0F 

//#define BATTERY_VOLTAGE         0x0F  
//#define ACTION_GROUP_RUNNING    0x06
//#define ACTION_GROUP_STOPPED    0x07
//#define ACTION_GROUP_COMPLETE   0x08

struct xArmServo {
    uint8_t  servo_id;
    uint16_t position;
    uint16_t duration;
};

class xArmServoController {
  public:
    xArmServoController(uint8_t receivePin, uint8_t transmitPin);
    void setPosition(uint8_t servo_id, uint16_t position, uint16_t duration, bool wait = false);
    void setPosition(xArmServo servo, bool wait = false);
    void setPosition(xArmServo servos[], uint8_t count, bool step = false);
    
    void off(uint8_t servo_id);
    void off(uint8_t servo_id[], uint8_t count);
    void off(xArmServo servo);
    void off(xArmServo servos[], uint8_t count);
    void off();
  
  private:
    SoftwareSerial serial_port;
};
#endif
