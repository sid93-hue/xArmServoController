/*
  xArmServoController.h - Library for controlling xArm servos.
  Created by Chris Courson, July 9, 2020.
  Released into the public domain.
*/
#pragma once
#ifndef XARMSERVOCONTROLLER_H
#define XARMSERVOCONTROLLER_H

#include <Arduino.h>
#include <stdarg.h>

#define SIGNATURE               0x55

#define CMD_SERVO_MOVE          0x03
#define CMD_GET_BATTERY_VOLTAGE 0x0f
#define CMD_SERVO_STOP          0x14
#define CMD_GET_SERVO_POSITION  0x15
//#define CMD_ACTION_GROUP_RUN    0x06
//#define CMD_ACTION_GROUP_STOP   0x07
//#define CMD_ACTION_GROUP_SPEED  0x0B

struct xArmServo {
    uint8_t  servo_id;
    uint16_t position;
};

class xArmServoController {
  public:
    bool debug = false;
  
    xArmServoController(Stream &serial_port);

    void setPosition(uint8_t servo_id, uint16_t position, uint16_t duration = 1000, bool wait = false);
    void setPosition(xArmServo servo, uint16_t duration = 1000, bool wait = false);
    void setPosition(xArmServo servos[], size_t count, uint16_t duration = 1000, bool wait = false);

    uint16_t getPosition(uint8_t servo_id);
    uint16_t getPosition(xArmServo &servo);
    bool getPosition(xArmServo servos[], size_t count);
    
    void servoOff(uint8_t servo_id);
    void servoOff(int num, int servo_id, ...);
    void servoOff(xArmServo servo);
    void servoOff(xArmServo servos[], size_t count);
    void servoOff();

    uint16_t getBatteryVoltage();
    
  protected:
    Stream &serial_port;
  
  private:
    byte _buffer[32];
    
    void send(uint8_t cmd, size_t len);
    size_t recv(uint8_t cmd);
};

#endif
