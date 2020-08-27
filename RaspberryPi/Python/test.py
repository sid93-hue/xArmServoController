#!/usr/bin/python3
import xarm, time

arm = xarm.Controller('/dev/ttyS0', True)

battery_voltage = arm.getBatteryVoltage()
print('Battery voltage (volts):', battery_voltage)

arm.setPosition(2, 90.0, wait=True)
time.sleep(1)
arm.setPosition(2, 0.0, wait=True)
time.sleep(1)
arm.servoOff()
