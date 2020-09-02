/*
  xArmServoController.cpp - Library for controlling xArm servos.
  Created by Chris Courson, July 9, 2020.
  Released into the public domain.
*/

#include "xArmServoController.h"

xArmServoController::xArmServoController(xArmMode mode, Stream &serial_port) : serial_port(serial_port) {
  xMode = mode;
}

/*** Send, Recv and checkServoLimits ***/

void xArmServoController::send(uint8_t cmd, uint8_t len = 0)
{
  serial_port.flush();
  serial_port.write(SIGNATURE);
  serial_port.write(SIGNATURE);
  serial_port.write(len + 2);
  serial_port.write(cmd);
  if (len > 0) {
    serial_port.write(_buffer, len);
/*     if (debug) {
      Serial.print("\nSend Data: "); 
      for (int i = 0; i < len; i++) {
        Serial.print(_buffer[i], DEC); Serial.print(' ');
      }
    }
 */  }
}

uint8_t xArmServoController::recv(uint8_t cmd)
{
  serial_port.readBytes(_buffer, 4);

/*   if (debug) {
    Serial.print("\nRecv Data: "); 
    for (int i = 0; i < 4; i++) {
      Serial.print(_buffer[i], DEC); Serial.print(' ');
    }
  }
 */  
  if (_buffer[0] == SIGNATURE && _buffer[1] == SIGNATURE && _buffer[3] == cmd) {
    uint8_t len = _buffer[2] - 2;
    serial_port.readBytes(_buffer, len);
/*     if (debug) {
      for (int i = 0; i < len; i++) {
        Serial.print(_buffer[i], DEC); Serial.print(' ');
      }
    }
 */    return len;
  }
  return -1;
}

uint16_t xArmServoController::clamp(uint16_t v, uint16_t lo, uint16_t hi) {
    return (v < lo) ? lo : (hi < v) ? hi : v;
}

uint16_t xArmServoController::clampServoLimits(uint8_t servo, uint16_t value) {
  switch (xMode)
  {
    case xArm:
      return clamp(value, 0, 1000);

    case LeArm:
      if(servo == 1) {
        return clamp(value, 1500, 2500);
      } else {
        return clamp(value, 500, 2500);
      }

    default:
      return value;
  }
}

/*** SetPosition ***/

void xArmServoController::setPosition(uint8_t servo_id, uint16_t position, uint16_t duration = 1000, boolean wait = false)
{
  position = clampServoLimits(servo_id, position);
  _buffer[0] = 1;
  _buffer[1] = lowByte(duration);
  _buffer[2] = highByte(duration);
  _buffer[3] = servo_id;
  _buffer[4] = lowByte(position);
  _buffer[5] = highByte(position);
  send(CMD_SERVO_MOVE, 6);
  if (wait) {
    delay(duration);
  }
}

void xArmServoController::setPosition(xArmServo servo, uint16_t duration = 1000, boolean wait = false)
{
  setPosition(servo.servo_id, servo.position, duration, wait);
}

void xArmServoController::setPosition(xArmServo servos[], uint8_t count, uint16_t duration = 1000, boolean wait = false)
{
  uint8_t len = count * 3 + 3;
  _buffer[0] = count;
  _buffer[1] = lowByte(duration);
  _buffer[2] = highByte(duration);
  for (int i = 3, j = 0; j < count; i += 3, j++) {
    _buffer[i] = servos[j].servo_id;
    _buffer[i + 1] = lowByte(servos[j].position);
    _buffer[i + 2] = highByte(servos[j].position);
  }
  send(CMD_SERVO_MOVE, len);
  if (wait) {
    delay(duration);
  }
}

/*** GetPosition ***/

uint16_t xArmServoController::getPosition(uint8_t servo_id)
{
  _buffer[0] = 1;
  _buffer[1] = servo_id;
  send(CMD_GET_SERVO_POSITION, 2);
  
  if (recv(CMD_GET_SERVO_POSITION) > 0) {
    return _buffer[3] * 256 + _buffer[2];
  }
  return -1;
}

uint16_t xArmServoController::getPosition(xArmServo &servo)
{
  uint16_t pos = getPosition(servo.servo_id);
  servo.position = pos;
  return pos;
}

boolean xArmServoController::getPosition(xArmServo servos[], uint8_t count)
{
  _buffer[0] = count;
  for (int i = 1, j = 0; j < count; i++, j++) {
    _buffer[i] = servos[j].servo_id;
  }
  send(CMD_GET_SERVO_POSITION, count + 1);

  // servo positions returned are in the same order sent.
  if (recv(CMD_GET_SERVO_POSITION) > 0) {
    for (int i = 2, j = 0; j < count; i += 3, j++) {
      servos[j].position = _buffer[i + 1] * 256 + _buffer[i];
    }
    return true;
  }
  return false;
}

/*** Off ***/

void xArmServoController::servoOff(uint8_t servo_id)
{
  _buffer[0] = 1;
  _buffer[1] = servo_id;
  send(CMD_SERVO_STOP, 2);
}

void xArmServoController::servoOff(uint8_t num, uint8_t servo_id, ...)
{
  _buffer[0] = num;
  _buffer[1] = servo_id;
  
  if (num > 1) {
    va_list args;
    va_start(args, servo_id);
    for (int i = 2; i <= num; i++) {
      _buffer[i] = (byte)va_arg(args, int);
    }
    va_end(args);    
  }
  send(CMD_SERVO_STOP, num + 1);
}

void xArmServoController::servoOff(xArmServo servo)
{
  servoOff(servo.servo_id);
}

void xArmServoController::servoOff(xArmServo servos[], uint8_t count)
{
  _buffer[0] = count;
  for (int i = 1, j = 0; j < count; i++, j++) {
    _buffer[i] = servos[j].servo_id;
  }
  send(CMD_SERVO_STOP, count + 1);
}

void xArmServoController::servoOff()
{
  _buffer[0] = 6;
  _buffer[1] = 1;
  _buffer[2] = 2;
  _buffer[3] = 3;
  _buffer[4] = 4;
  _buffer[5] = 5;
  _buffer[6] = 6;
  send(CMD_SERVO_STOP, 7);
}

/*** Action Group ***/

  void xArmServoController::actionRun(uint8_t group, uint16_t times) {
    _buffer[0] = group;
    _buffer[1] = lowByte(times);
    _buffer[2] = highByte(times);
    send(CMD_ACTION_GROUP_RUN, 3);
  }

  void xArmServoController::actionStop() {
    send(CMD_ACTION_GROUP_STOP, 0);
  }

  void xArmServoController::actionSpeed(uint8_t group, uint16_t percentage) {
    _buffer[0] = group;
    _buffer[1] = lowByte(percentage);
    _buffer[2] = highByte(percentage);
    send(CMD_ACTION_GROUP_SPEED, 3);
  }

/*** GetBatteryVoltage ***/

uint16_t xArmServoController::getBatteryVoltage()
{
  send(CMD_GET_BATTERY_VOLTAGE);
  if (recv(CMD_GET_BATTERY_VOLTAGE) > 0) {
    return _buffer[1] * 256 + _buffer[0];
  }
  return -1;
}
