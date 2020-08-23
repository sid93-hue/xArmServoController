import xarm

# serial_number': '497223563535' and '497253743535'
arm = xarm.Controller('USB', True)

servo1 = xarm.Servo(1, 500)
servo2 = xarm.Servo(2, 500)
servo3 = xarm.Servo(3, 500)
servo4 = xarm.Servo(4, 500)
servo5 = xarm.Servo(5, 500)
servo6 = xarm.Servo(6, 500)

#arm.setPosition([servo1, servo2, servo3, servo4, servo5, servo6], None, wait=True)
#arm.setPosition(2, 500, wait=True)

# arm.setAngle(2, 90, wait=True)
# arm.setAngle(2, 0, wait=True)

# arm.servoOff()

#voltage = arm.getBatteryVoltage()
#print('Battery Voltage:', voltage)

# servo = xarm.Servo(1, 140)
# print('servo_id', servo.servo_id, 'servo.position', servo.position, 'servo.angle', servo.angle)
# arm.setPosition(servo, wait=True)
# servo.angle = 0
# arm.setAngle(1, 0, wait=True)

# servo = xarm.Servo(2, 140)
# arm.setPosition([[1,90.0], servo], wait=True)

# arm.setPosition([servo1, [2,0.0]], wait=True)

# arm.servoOff()

postion = arm.getPosition(2, True)
print('position', postion)