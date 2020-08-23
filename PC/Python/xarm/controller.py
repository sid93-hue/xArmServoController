from .servo import Servo
from .util import Util
import time

class Controller:
    SIGNATURE = 0x55
    CMD_SERVO_MOVE = 0x03
    CMD_GET_BATTERY_VOLTAGE = 0x0f
    CMD_SERVO_STOP = 0x14
    CMD_GET_SERVO_POSITION  = 0x15

    debug = False

    def __init__(self, com_port, debug=False):
        if com_port.startswith('COM'):
            import serial
            self._device = serial.Serial(com_port, 9600, timeout = 1)
            self._is_serial = True
        elif com_port.startswith('USB'):
            import pywinusb.hid as hid, pywinusb.hid.core as core
            devices = hid.HidDeviceFilter(vendor_id=0x0483, product_id=0x5750).get_devices()
            print(len(devices))
            if len(devices) == 0:
                raise RuntimeError('No xArm device found.')
            serial_number = com_port.strip('USB')
            if serial_number:
                for device in devices:
                    if device.serial_number == serial_number:
                        self._device = device
                if not hasattr(self, '_device'):
                    raise ValueError('Device not found.')
            else:
                self._device = devices[0]
            if debug:
                print('Serial number:', self._device.serial_number)
            self._device.open()
            self._device.set_raw_data_handler(self.usb_data_handler)
            self._output_report = self._device.find_output_reports()[0]
            self._input_report = bytearray(65)
            self._is_serial = False
        else:
            raise ValueError('com_port parameter incorrect.')
        self.debug = debug

    def setPosition(self, servos, position=None, duration=1000, wait=False):
        data = bytearray([1, duration & 0xff, (duration & 0xff00) >> 8])

        if isinstance(servos, int):
            if position == None:
                raise ValueError('Parameter \'position\' missing.')
            if isinstance(position, float):
                position = Util._angle_to_position(position)
            data.extend([servos, position & 0xff, (position & 0xff00) >> 8])
        elif isinstance(servos, Servo):
            data.extend([servos.servo_id, servos.position & 0xff, (servos.position & 0xff00) >> 8])
        elif isinstance(servos, list):
            data[0] = len(servos)
            for servo in servos:            
                if isinstance(servo, Servo):
                    data.extend([servo.servo_id, servo.position & 0xff, (servo.position & 0xff00) >> 8])
                elif len(servo) == 2 and isinstance(servo[0], int):
                    if isinstance(servo[1], float):
                        servo[1] = Util._angle_to_position(servo[1])
                    data.extend([servo[0], servo[1] & 0xff, (servo[1] & 0xff00) >> 8])
                else:
                    raise ValueError('Parameter list \'servos\' is not valid.')
        else:
            raise ValueError('Parameter \'servos\' is not valid.')

        self._send(self.CMD_SERVO_MOVE, data)

        if wait:
            time.sleep(duration/1000)

    def getPosition(self, servos, degrees=False):
        if isinstance(servos, int):
            data = bytearray([1, servos])
        elif isinstance(servos, Servo):
            pass
        elif isinstance(servos, list) and all(isinstance(x, Servo) for x in servos):
            pass
        else:
            raise ValueError('Parameter \'servos\' is not valid.')

        self._send(self.CMD_GET_SERVO_POSITION, data)
        data = self._recv(self.CMD_GET_SERVO_POSITION)

        if data != None:
            position = data[3] * 256 + data[2]
            return Util._position_to_angle(position) if degrees else position
        else:
            raise Exception('Function \'getPosition\' recv error.')


    # @multimethod
    # def getPosition(self, servo: Servo):
    #     position = self.getPosition(servo.servo_id)
    #     servo.position = position
    #     return position

    # @multimethod
    # def getPosition(self, servos: list):
    #     count = len(servos)
    #     data = bytearray([count])
    #     for servo in servos:
    #         data.append(servo.servo_id)
    #     self.__send(self.CMD_GET_SERVO_POSITION, data)

    #     data = self.__recv(self.CMD_GET_SERVO_POSITION)
    #     if data != None:
    #         for i in range(count):
    #             j = i * 3 + 2
    #             servos[i].position = data[j + 1] * 256 + data[j]
    #         return True
    #     else:
    #         return False

    def servoOff(self, servos=None):
        data = bytearray([1])

        if isinstance(servos, int):
            data.append(servos)
        elif isinstance(servos, Servo):
            data.append(servos.servo_id)
        elif isinstance(servos, list) and all(isinstance(x, Servo) for x in servos):
            data[0] = len(servos)
            for servo in servos:
                data.append(servo.servo_id)
        elif servos == None:
            data = [6, 1,2,3,4,5,6]
        else:
            raise ValueError('servos parameter incorrect.')

        self._send(self.CMD_SERVO_STOP, data)

    # # GetBatteryVoltage

    def getBatteryVoltage(self):
        self._send(self.CMD_GET_BATTERY_VOLTAGE)
        
        data = self._recv(self.CMD_GET_BATTERY_VOLTAGE)
        if data != None:
            return data[1] * 256 + data[0]
        else:
            return -1

    def _send(self, cmd, data = []):
        if self.debug:
            print('Send Data (' + str(len(data)) + '): ' + ' '.join('{:02x}'.format(x) for x in data))

        if self._is_serial:
            self._device.flush()
            self._device.write([self.SIGNATURE, self.SIGNATURE, len(data) + 2, cmd])
            if len(data) > 0:
                self._device.write(data)
        else:
            if self._device.is_plugged():
                report_data = bytearray(65)
                report_data[0] = 0
                report_data[1] = self.SIGNATURE
                report_data[2] = self.SIGNATURE
                report_data[3] = len(data) + 2
                report_data[4] = cmd
                if len(data):
                    report_data[5:5 + len(data)] = data
                self._output_report.set_raw_data(report_data)
                self._output_report.send()
            else:
                raise RuntimeError('Lost device xArm connection.')
        time.sleep(0.01)    # Sleep for approximately 10 milliseconds to prevent communication overrun.

    def _recv(self, cmd):
        if self._is_serial:
            data = self._device.read(4)

            if self.debug:
                print('Recv Data: ' + ' '.join('{:02x}'.format(x) for x in data), end=" ")

            if data[0] == self.SIGNATURE and data[1] == self.SIGNATURE and data[3] == cmd:
                length = data[2]
                data = self._device.read(length)

                if self.debug:
                    print(' '.join('{:02x}'.format(x) for x in data))
            
                return data
            else:
                return None
        else:
            t_end = time.time() + 60
            while time.time() < t_end:
                if self._input_report[1] == self.SIGNATURE and self._input_report[2] == self.SIGNATURE and self._input_report[4] == cmd:
                    length = self._input_report[3]
                    data = self._input_report[5:5 + length]
                    if self.debug:
                        print('Recv Data: ' + ' '.join('{:02x}'.format(x) for x in data))
                    return data
            return None

    def usb_data_handler(self, data):
        self._input_report = data
        if self.debug:
            print('USB Raw Recv Data: ' + ' '.join('{:02x}'.format(x) for x in data))