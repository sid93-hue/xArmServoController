import time
from msvcrt import kbhit 
import pywinusb.hid as hid

CMD_SERVO_STOP = 0x14
CMD_GET_BATTERY_VOLTAGE = 0x0f
CMD_GET_SERVO_POSITION  = 0x15

def event_handler(new_value, event_type):
    #time.sleep(0.1  )
    print('event', new_value[:23], event_type)

devices = hid.HidDeviceFilter(vendor_id=0x0483, product_id=0x5750).get_devices()

if len(devices) > 0:
    device = devices[0]
    
    device.open()
    print('serial_number:', device.serial_number)

    full_usage_id = hid.get_full_usage_id(0x8c, 0x03)
    device.add_event_handler(full_usage_id, event_handler)


    while not kbhit():
        cmd = CMD_GET_SERVO_POSITION
        data = [6,1,2,3,4,5,6]
        report_data = bytearray(65)
        report_data[0] = 0
        report_data[1] = 0x55
        report_data[2] = 0x55
        report_data[3] = len(data) + 2
        report_data[4] = cmd
        if len(data):
            report_data[5:5 + len(data)] = data
        device.send_output_report(report_data)

        #time.sleep(0.1)

print('end')

