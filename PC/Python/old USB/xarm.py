import serial, time, sys, usb.core
from multimethod import multimethod # (pip install multimethod)
import usb.core           # https://github.com/pyusb/pyusb (pip install pyusb, pip install libusb)


class Servo:
    def __init__(self, servo_id, position):
        self.servo_id = servo_id
        self.position = position


class Controller:
    SIGNATURE = 0x55
    CMD_SERVO_MOVE = 0x03
    CMD_GET_BATTERY_VOLTAGE = 0x0f
    CMD_SERVO_STOP = 0x14
    CMD_GET_SERVO_POSITION  = 0x15

    debug = False

    def __init__(self):
        # self.__device = usb.core.find(idVendor=0x0483, idProduct=0x5750)
        # if self.__device is None:
        #    raise ValueError('Device not found')
        dev = usb.core.find(find_all=True)
        for cfg in dev:
            print('Decimal VendorID=' + str(cfg.idVendor) + ' & ProductID=' + str(cfg.idProduct) + '\n')
            print('Hexadecimal VendorID=' + hex(cfg.idVendor) + ' & ProductID=' + hex(cfg.idProduct) + '\n\n')

    # SetPosition

    @multimethod
    def setPosition(self, servo_id: int, position: int, duration = 1000, wait = False):
        data = bytearray([1])
        data.append(duration & 0xff)
        data.append((duration & 0xff00) >> 8)
        data.append(servo_id)
        data.append(position & 0xff)
        data.append((position & 0xff00) >> 8)
        self.__send(self.CMD_SERVO_MOVE, data)

        if wait:
            time.sleep(duration/1000)

    @multimethod
    def setPosition(self, servo: Servo, duration = 1000, wait = False):
        self.setPosition(servo.servo_id, servo.position, duration, wait)

    @multimethod
    def setPosition(self, servos: list, duration = 1000, wait = False):
        count = len(servos) * 3 + 3
        data = bytearray([count])
        data.append(duration & 0xff)
        data.append((duration & 0xff00) >> 8)
        for servo in servos:
            data.append(servo.servo_id)
            data.append(servo.position & 0xff)
            data.append((servo.position & 0xff00) >> 8)
        self.__send(self.CMD_SERVO_MOVE, data)

        if wait:
            time.sleep(duration/1000)


    # GetPosition

    @multimethod
    def getPosition(self, servo_id: int):
        data = bytearray([1, servo_id])
        self.__send(self.CMD_GET_SERVO_POSITION, data)

        data = self.__recv(self.CMD_GET_SERVO_POSITION)
        if data != None:
            return data[3] * 256 + data[2]
        else:
            return -1


    @multimethod
    def getPosition(self, servo: Servo):
        position = self.getPosition(servo.servo_id)
        servo.position = position
        return position

    @multimethod
    def getPosition(self, servos: list):
        count = len(servos)
        data = bytearray([count])
        for servo in servos:
            data.append(servo.servo_id)
        self.__send(self.CMD_GET_SERVO_POSITION, data)

        data = self.__recv(self.CMD_GET_SERVO_POSITION)
        if data != None:
            for i in range(count):
                j = i * 3 + 2
                servos[i].position = data[j + 1] * 256 + data[j]
            return True
        else:
            return False


    # ServoOff

    @multimethod
    def servoOff(self, servo_id: int):
        data = bytearray([1, servo_id])
        self.__send(self.CMD_SERVO_STOP, data)

    @multimethod
    def servoOff(self, *servo_ids: int):
        data = bytearray([len(servo_ids)])
        for servo_id in servo_ids:
            data.append(servo_id)
        self.__send(self.CMD_SERVO_STOP, data)

    @multimethod
    def servoOff(self, servo: Servo):
        self.servoOff(servo.servo_id)

    @multimethod
    def servoOff(self, servos: list):
        data = bytearray([len(servos)])
        for servo in servos:
            data.append(servo.servo_id)
        self.__send(self.CMD_SERVO_STOP, data)

    @multimethod
    def servoOff(self):
        self.__send(self.CMD_SERVO_STOP, bytearray([6,1,2,3,4,5,6]))
    

    # GetBatteryVoltage

    def getBatteryVoltage(self):
        self.__send(self.CMD_GET_BATTERY_VOLTAGE)
        
        data = self.__recv(self.CMD_GET_BATTERY_VOLTAGE)
        if data != None:
            return data[1] * 256 + data[0]
        else:
            return -1


    # Private

    def __send(self, cmd, data = []):
        self.__serial_port.flush()
        self.__serial_port.write([self.SIGNATURE, self.SIGNATURE, len(data) + 2, cmd])
        if len(data) > 0:
            self.__serial_port.write(data)
            if self.debug:
                print('Send Data (' + str(len(data)) + '): ' + ' '.join('{:02x}'.format(x) for x in data))

    def __recv(self, cmd):
        data = self.__serial_port.read(4)

        if self.debug:
            print('Recv Data: ' + ' '.join('{:02x}'.format(x) for x in data), end=" ")

        if data[0] == self.SIGNATURE and data[1] == self.SIGNATURE and data[3] == cmd:
            length = data[2]
            data = self.__serial_port.read(length)

            if self.debug:
                print(' '.join('{:02x}'.format(x) for x in data))
        
            return data

        else:
            return None
