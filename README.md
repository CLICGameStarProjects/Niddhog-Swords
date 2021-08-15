# NidhoggSword

This is meant to play Nidhogg with a sword for hitting and a Nunchuck for movement and jump
There are two parts for the two players: Sword and Nunchuck.

## Sword
This program is used to read an MPU-6050 IMU data over I2C and send corresponding keypresses to Nidhogg

### Hardware
The hardware used is an Arduino Leonardo with an MPU-6050 IMU mounted on a sword.
The MPU-6050 sensor is mounted on a GY-521 PCB.
The SCL pin of the sensor is connected to pin 3 of the Arduino Leonardo and SDA is connected to pin 5
The VCC and GND pins of the sensor are connected to the 5V and GND pins of the Arduino

The Arduino expect the I2C bus to be at 5V and the MPU-6050 expects it to be at 3.3V. However, we just connect the
bus directly, the MPU-6050 pulls the lines to 3.3V and the Arduino to 5V, resulting in an idle voltage of approximately 3.6V,
which should be acceptable for both the Arduino and the sensor.

The sensitive axis is the gyroscope X axis (appropriate for the current placement of the sensor on the sword)

### Installation
You'll need the Arduino IDE with the Keyboard library (available from the library store in the IDE, by the Arduino team)

### Configuration
The keyboard key has to be specified by defining the `KEY` macro with a lowercase ASCII value on a US keyboard.
For non-alphabetic keys, see `https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/`
The macro needs to be changed for the two players. The default bindings for Nidhogg are `'f'` and `'m'`.


## Nunchuck
This program is used to interface a Nintendo Wii Nunchuck and generate keypresses for displacement in Nidhogg

### Hardware
The hardware is an Arduino Micro with a Nunchuck connected.

Pinout:
┌─┐   ┌─┐
│ └───┘ │
│ · · · │ SCL  NC  GND
│ · · · │ VCC  NC  SDA
└───────┘

SCL: Arduino pin 3
SDA: Arduino pin 2
VCC: 3.3V
GND: Ground
NC:  No connection

### Installation
You'll need the Arduino IDE with the Keyboard library (available from the library store in the IDE, by the Arduino team)

### Library
The `nunchuck_functions.h` file is a slightly modified version of `https://github.com/todbot/wiichuck_adapter/blob/master/firmware/WiichuckDemo/nunchuck_funcs.h`
### Mapping
Z: jump
Joystick left/right: move left/right

### Configuration
The keyboards keys are defined by the macros `KEY_JUMP`, `KEY_LEFT` and `KEY_RIGHT`, with a lowercase ASCII value on a US keyboard.
For non-alphabetic keys, see `https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/`
The default bindings for Nidhogg can be used by defining the macro `LEFT_PLAYER` or `RIGHT_PLAYER`
