# xArmServoController

xArm servo controller libraries for `Lewan-Soul`/`Lobot`/`Hiwonder` 6-DOF robotic arm.

![xArm 6-DOF Robotic Arm](https://i.imgur.com/ykl5PWF.png)

Available on Amazon.com at [this link](https://www.amazon.com/LewanSoul-Programmable-Feedback-Parameter-Programming/dp/B0793PFGCY).

## Table of Contents

*  [TTL Serial Control](#ttlserialcontrol)
*  [Arduino](Arduino/README.md)
*  [Credits](#credits)
*  [License](#license)  

## TTL Serial Control

The control board mounted on the base of the xArm has a 4-pin connector which provides a signal path and power to an external host controller.

![xArm 6-DOF Robotic Arm](https://i.imgur.com/tG3Fw9u.jpg)

| Pin | Description
|-----|------------
| GND | Power and signal ground.
| TX  | Serial TTL signal from xArm to host controller. Mark = 5VDC, Space = 0VDC.
| RX  | - Serial TTL signal from host controller to xArm. Mark = 5VDC, Space = 0VDC.
| 5V  | 5 Volts DC power for eternal host controller. Current rating is not yet known. In most circumstances this is left unconnected.<br>`Warning: Do not connect to an external power source. Doing so will cause the xArm to beep loudly and may damage the control board.`

## Credits

Ammon Dodson - *Command examples* - https://github.com/ammon0/Syringenator

## License

This project is licensed under the GNU GENERAL PUBLIC LICENSE v3 - see the [LICENSE](LICENSE) file for details
