from .util import Util

class Servo:
    def __init__(self, servo_id, position=None, degrees=None):
        if position and degrees:
            raise ValueError('Specify position or degrees but not both.')
        self.servo_id = servo_id

        if position:
            if position < 0 or position > 1000:
                raise ValueError('Position paramater must be between 0 and 1000')
            self.__set_position(position)
        else:
            if degrees < -125.0 or degrees > 125.0:
                raise ValueError('Degrees parameter must be between -125.0 and 125.0')
            self.__set_angle(degrees)
    
    def __get_position(self):
        return self.__position

    def __set_position(self, position):
        self.__position = int(position)
        self.__angle = Util._position_to_angle(self.__position)

    def __get_angle(self):
        return self.__angle

    def __set_angle(self, degrees):
        self.__angle = float(degrees)
        self.__position = Util._angle_to_position(self.__angle)

    position = property(__get_position, __set_position)
    angle = property(__get_angle, __set_angle)