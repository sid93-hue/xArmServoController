/*
  xArmServoController.cpp - Library for controlling xArm servos.
  Created by Chris Courson, July 9, 2020.
  Released into the public domain.
*/

#include "xArmServoController.h"

xArmServoController::xArmServoController(uint8_t receivePin, uint8_t transmitPin) : serial_port(receivePin, transmitPin)
{
  serial_port.begin(9600);
}

void xArmServoController::setPosition(uint8_t servo_id, uint16_t position, uint16_t duration, bool wait = false)
{
  serial_port.write(SIGNATURE);
  serial_port.write(SIGNATURE);
  serial_port.write(8); // length
  serial_port.write(CMD_SERVO_MOVE);
  serial_port.write(1); // servo count
  serial_port.write(lowByte(duration));
  serial_port.write(highByte(duration));
  serial_port.write(servo_id);
  serial_port.write(lowByte(position));
  serial_port.write(highByte(position));
  if (wait) {
    delay(duration);
  }
}

/*** SetPosition ***/

void xArmServoController::setPosition(xArmServo servo, bool wait = false)
{
  setPosition(servo.servo_id, servo.position, servo.duration, wait);
}

void xArmServoController::setPosition(xArmServo servos[], uint8_t count, bool step = false)
{
  for (int i = 0; i < count; i++) {
    setPosition(servos[i].servo_id, servos[i].position, servos[i].duration, step);
  }
}

/*** Off ***/

void xArmServoController::off(uint8_t servo_id)
{
  serial_port.write(SIGNATURE);
  serial_port.write(SIGNATURE);
  serial_port.write(4); // length
  serial_port.write(CMD_SERVO_STOP);
  serial_port.write(1); // servo count
  serial_port.write(servo_id);
}

void xArmServoController::off(uint8_t servo_id[], uint8_t count)
{
  serial_port.write(SIGNATURE);
  serial_port.write(SIGNATURE);
  serial_port.write(count + 3); // length
  serial_port.write(CMD_SERVO_STOP);
  serial_port.write(count); // servo count
  for (int i = 0; i < count; i++) {
    serial_port.write(servo_id[i]);
  }
}

void xArmServoController::off(xArmServo servo)
{
  off(servo.servo_id);
}

void xArmServoController::off(xArmServo servos[], uint8_t count)
{
  uint8_t* servo_id = new uint8_t[count];
  for (int i = 0; i < count; i++) {
    servo_id[i] = servos[i].servo_id;
  }
  off(servo_id, count);
  delete servo_id;
}

void xArmServoController::off()
{
  uint8_t servo_id[] = {1, 2, 3, 4, 5, 6};
  off(servo_id, 6);
  delete servo_id;
}
