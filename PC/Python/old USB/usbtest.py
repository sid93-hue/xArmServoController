import pywinusb.hid as hid # https://www.reddit.com/r/learnpython/comments/3z346p/reading_a_usb_data_stream_on_windows/
from time import sleep

vendor_id = 0x0483
product_id = 0x5750

def sample_handler(data):
    print('Raw data: ' + ' '.join('{:02x}'.format(x) for x in data))

print('Begin.')

devices = hid.HidDeviceFilter(vendor_id=vendor_id, product_id=product_id).get_devices()

if devices:
    device = devices[0]
    print(device)
    print('success')

    device.open()
    device.set_raw_data_handler(sample_handler)

    if device.is_plugged():
        report = device.find_output_reports()[0]

    while device.is_plugged():
        
        buffer = bytearray(65)
        buffer[0] = 0x00
        buffer[1] = 0x55
        buffer[2] = 0x55
        buffer[3] = 0x02
        buffer[4] = 0x0f
        report.set_raw_data(buffer)
        report.send()
        #device.send_output_report(buffer)
        sleep(1) 
else:
    print('Device not found')

print('End.')
