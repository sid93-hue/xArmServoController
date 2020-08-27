#!/usr/bin/python3
import time
import serial
#from serial import Serial

# ser = serial.Serial('/dev/tty0', 9600, timeout = 1)

ser = serial.Serial(
        port='/dev/ttyS0', #Replace ttyS0 with ttyAM0 for Pi1,Pi2,Pi0
        baudrate = 9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
      )

counter = 0
while counter < 1000:
    ser.write('Hello '.encode())
    counter += 1

