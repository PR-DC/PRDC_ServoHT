# STM32 Servo Library using HardwareTimer from Arduino_Core_STM32

PWM signal for Servo motor control is generated using HardwareTimer 
library from Arduino_Core_STM32, for every i/o pin, that has PWM 
capability. Timer and channel are configured within the attach() method.

## Requirements
[Arduino](https://www.arduino.cc/)<br>
[Arduino_Core_STM32](https://github.com/stm32duino/Arduino_Core_STM32)<br>

This library is tested with
**Arduino IDE 1.8.13** and **Arduino_Core_STM32 1.9.0**.

## Installation
Clone the repository to the Arduino libraries folder.

For example, on the Windows OS path is:
```
C:\Users\{User}\Documents\Arduino\libraries
```

For more information please visit: https://www.arduino.cc/en/guide/libraries#toc5

## Usage

This library is compatible with the **Arduino Servo library**, 
the only difference is that the class name is **ServoHT** instead of Servo.

For more information about the Arduino Servo library 
please visit: http://www.arduino.cc/en/Reference/Servo

## License
Copyright (C) 2021 PR-DC <info@pr-dc.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as 
published by the Free Software Foundation, either version 3 of the 
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
