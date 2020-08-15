# xarm module requires serial and multimethod


import xarm


print('Begin.')

arm = xarm.Controller('COM6')
arm.debug = True
#xarm.servoOff()
#print(arm.getBatteryVoltage())

servo1 = xarm.Servo(1, 700)
servo2 = xarm.Servo(2, 400)
servo3 = xarm.Servo(3, 600)

# arm.setPosition([servo1, servo2, servo3])

# print(arm.getPosition(1))

# position = arm.getPosition(servo1)
# print('Position:', position)
# print('servo1.position:', servo1.position)

# arm.getPosition([servo1, servo2, servo3])
# print('servo1.position:', servo1.position)
# print('servo2.position:', servo2.position)
# print('servo3.position:', servo3.position)

# arm.servoOff(1, 2, 3)

# arm.servoOff(servo2)

arm.servoOff([servo1, servo2, servo3])

print('End.')