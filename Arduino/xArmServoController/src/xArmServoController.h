/*
  xArmServoController.h - Library for controlling xArm servos.
  Created by Chris Courson, July 9, 2020.
  Released into the public domain.
*/
#pragma once
#ifndef XARMSERVOCONTROLLER_H
#define XARMSERVOCONTROLLER_H

#include <stdarg.h>
#include <Arduino.h>

#define SIGNATURE               0x55
#define CMD_SERVO_MOVE          0x03
#define CMD_ACTION_GROUP_RUN    0x06
#define CMD_ACTION_GROUP_STOP   0x07
#define CMD_ACTION_GROUP_SPEED  0x0B
#define CMD_GET_BATTERY_VOLTAGE 0x0f
#define CMD_SERVO_STOP          0x14
#define CMD_GET_SERVO_POSITION  0x15

enum xArmMode : uint8_t {xArm, LeArm};

struct xArmServo {
    uint8_t  servo_id;
    uint16_t position;
};

class xArmServoController {
  public:
    // boolean debug = false;
  
    xArmServoController(xArmMode mode, Stream &serial_port);

    void setPosition(uint8_t servo_id, uint16_t position, uint16_t duration = 1000, boolean wait = false);
    void setPosition(xArmServo servo, uint16_t duration = 1000, boolean wait = false);
    void setPosition(xArmServo servos[], uint8_t count, uint16_t duration = 1000, boolean wait = false);

    uint16_t getPosition(uint8_t servo_id);
    uint16_t getPosition(xArmServo &servo);
    boolean getPosition(xArmServo servos[], uint8_t count);
    
    void servoOff(uint8_t servo_id);
    void servoOff(uint8_t num, uint8_t servo_id, ...);
    void servoOff(xArmServo servo);
    void servoOff(xArmServo servos[], uint8_t count);
    void servoOff();

    void actionRun(uint8_t group, uint16_t times);
    void actionStop();
    void actionSpeed(uint8_t group, uint16_t percentage);

    uint16_t getBatteryVoltage();
    
  protected:
    Stream &serial_port;
  
  private:
    uint8_t _buffer[32];
    xArmMode xMode;
    
    uint16_t clamp(uint16_t v, uint16_t lo, uint16_t hi);
    uint16_t clampServoLimits(uint8_t servo, uint16_t value);
    void send(uint8_t cmd, uint8_t len);
    uint8_t recv(uint8_t cmd);
};

#endif
