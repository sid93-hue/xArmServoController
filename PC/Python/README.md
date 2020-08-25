# /PC/Python/xArmController

## Table of Content
1. [Setting up a Python development environment](#setting-up-a-windows-python-development-environment)
1. [Installing the xArmController module](#installing-the-xArmController-module)
1. [Methods and examples](#methods-and-examples)
1. [Things left To-Do](#to-do)

___
## Setting up a Windows Python development environment

There are many options for setting up Python development environment in Windows. To get xArmController running you install the following:

1. Python 3
1. An editor or IDE
1. xArmController module

### How to install Python 3

If you already have Python installed, ensure you are running version 3 or higher.

1. Open a  web browser to https://www.python.org/
1. Click on the "Download Python {version here}" button on the home page.
1. After downloaded, run the installer and follow the prompts.
1. When prompted, choose to "Add python.exe to Path".

### Installing an editor

Python includes a very simple GUI editor called IDLE. This editor is adequate for the examples and demos in this library.

A more robust editor is VSCode (Visual Studio Code). It can be installed from https://code.visualstudio.com/. There are a couple plugins that will be required to get the best experience from VSCode. VSCode will *automagically* prompt you for these plugins when it detects you are working with Python.

___
## Installing the xArmController module

From the Windows Command Prompt or Terminal in VSCode, run the following command to unstall xArmController and its module dependency pywinusb. Just copy from here and paste to the terminal command line.

`pip install "git+https://github.com/ccourson/xArmServoController.git#egg=master&subdirectory=PC/Python"`

___
## Methods and examples

### Connecting to the xArm

This example is the bare minimum to connect to the xArm via USB and read the battery voltage.

```py
import xarm

# arm is the first xArm detected which is connected to USB
arm = xarm.Controller('USB')
print('Battery voltage in volts:', arm.getBatteryVoltage())
```
Output:
> Battery voltage: 7.677

The Controller can connect to a specific xArm by appending the serial number to "USB". To find the serial number of your xArm, turn on debug, then after connecting one xArm, run this code.

```py
import xarm

arm = xarm.Controller('USB', debug=True)
```
Output:
>Serial number: 497223563535

Now knowing the serial number you can connect to a specific xArm like this example using two.

```py
import xarm

arm1 = xarm.Controller('USB497223563535')
arm2 = xarm.Controller('USB497253743535')

print('Battery voltage of arm1 in volts:', arm1.getBatteryVoltage())

print('Battery voltage of arm2 in volts:', arm2.getBatteryVoltage())
```
Output:

>Battery voltage of arm1 in volts: 7.677\
>Battery voltage of arm2 in volts: 7.662

In the same way, the Controller can connect to one or more serailly connected xArms.

### Classes and Methods

*class* **Servo**(*servo_id*__[__, *position=500*__]__)
<dl><dd>
Returns a <i>Servo</i> object. The Servo class is used to hold the position of a given servo in units and angle.

Properties include:
<ul>
<li>servo_id - ID of servo.</li>
<li>position - Position of servo in units (0 to 1000).</li>
<li>angle - Angle of servo in degrees (-125.0 to 125.0 in 0.25 degree integral).</li>
</ul>

The <em>position</em> paramter may be specified with an <em>int</em> value between 0 and 1000. When set to a <em>float</em> value between -125.0 to 125.0, the <em>angle</em> value is set in degrees and rounded to a 0.25 degree integral. There are 4 servo units per degree of angle.

>Note: In Python, an <em>int</em> value does not have a decimal point (500). A <em>float</em> value has a decimal point (0.0).

Setting position will also set the corresponding angle and visa-versa. If <em>position</em> is not specified, it will default to '500' and <em>angle</em> will be set to '0.0'.

```py
import xarm

arm = xarm.Controller('USB')

# define servo as servo ID 1 with position 300
servo = xarm.Servo(1, 300)

print('servo ID:', servo.servo_id)
print('servo position:', servo.position)
print('servo angle:', servo.angle)
```
Output:
>servo ID: 1\
>servo position: 300\
>servo angle: -50.0
</dd></dl>

*class* **Controller**(*com_port*__[__, *debug=False*__]__)
<dl><dd>
Returns a <i>Controller</i> object. The Controller class connects Python to the xArm. The port to connect to the xArm through is determined by <i>com_port</i> which can be a serial port (<code>COM5</code>) or USB port (<code>USB</code>). Multiple xArms may be connected. If more than one xArm is attached by USB, each can be identified by appending the serial number to 'USB' (<code>USB497223563535</code>). 

Optionally, when <i>debug</i> is <code>True</code>, communication diganostic information will be printed to the terminal.

```py
# attach to xArm connected to USB
arm1 = xarm.Controller('USB')
# attach to USB connected xArm with serial number '497223563535'
arm2 = xarm.Controller('USB497223563535')
# attach to xArm connected to serial port 'COM5'
arm3 = xarm.Controller('COM5')
# enable debug
arm4 = xarm.Controller('COM6', True)        # positional argument
arm5 = xarm.Controller('COM7', debug=True)  # named argument
```
</dd></dl>

**setPosition**(*servos*__[__, *position=None*, *duration=1000*, *wait=False*__]__)
<dl><dd>
Moves one or more servos.

When <em>servos</em> is an <em>int</em> value, it represents a servo ID and the <em>position</em> parameter is required.

The <em>position</em> paramter may be an <em>int</em> to indicate a unit position (0 to 1000) or a <em>float</em> to indicate an angle in degrees (-125.0 to 125.0).

```py
# Set servo ID 1 to position 500.
setPosition(1, 500)
```

When <em>servos</em> is a <em>Servo</em> object, the <em>position</em> parameter is ignored.

When <em>servos</em> is a <em>list</em>, it may contain <em>Servo</em> objects or servo ID and position pairs and the <em>position</em> parameter is ignored.
</dd></dl>

**getPosition**(*servos*__[__, *degrees=False*__]__)
<dl><dd>
Moves one or more servos.


</dd></dl>

**servoOff**(__[__ *servos=None*__]__)
<dl><dd>
Moves one or more servos.


</dd></dl>


**getBatteryVoltage**()
<dl><dd>
Moves one or more servos.


</dd></dl>

___
## To-Do

* gripCalibrate - Gripper will slowly close and detect when it has reached the fully closed condition.
* gripClose - Gripper will slowly close and stop when it has detected gripper is no longer closing.
* gripOpen - Gripper will open to a specified with in centimeters.
* gripMove - Gripper will move to a Euclidean coordinate while maintining its angle.

### Built-in functions

* groupRun
* groupStop
* groupErase
* groupDownload
* groupSpeed
* offsetRead
* offsetWrite
* offsetAdjust