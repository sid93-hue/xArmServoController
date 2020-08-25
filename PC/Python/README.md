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
> Battery voltage of arm1 in volts: 7.677\
  Battery voltage of arm2 in volts: 7.662

In the same way, the Controller can connect to one or more serailly connected xArms.

### Methods

*class* **Controller**(*com_port*_[_, *debug=False*_]_)
<dd>The Controller class connects Python to the xArm.
| com_port | Can be a serial port (COM5) or USB port (USB). If more than one xArm is attached by USB, each can be specified by appending the serial number to USB (USB497223563535). |
| debug | When `True` will cause diganostic information to be printed to the terminal. |</dd>


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