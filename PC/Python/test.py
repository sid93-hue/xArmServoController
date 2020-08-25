import xarm

arm = xarm.Controller('USB')

servo2 = xarm.Servo(2)
servo5 = xarm.Servo(5)
servo6 = xarm.Servo(6)

# Turns off servo motor 1
arm.servoOff(1)

# Turns off servo motor 1
arm.servoOff(servo2)

# Turns off servo motors 3 and 4
arm.servoOff([3, 4])

# Turns off servo motors 5 and 6
arm.servoOff([servo5, servo6])
