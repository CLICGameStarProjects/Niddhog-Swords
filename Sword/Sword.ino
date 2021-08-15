/* Copyright 2021 SimonTagne

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <Wire.h>
#include <Keyboard.h>

//#define KEY 'f'
#define KEY 'm'

#define I2C_ADDR 0x68

void setup() {
    // put your setup code here, to run once:

    // LED to debug
    pinMode(13, OUTPUT);

    Wire.begin();
    Keyboard.begin();

    // Wait for the IMU to initialize completely before attempting to communicate
    delay(100);

    // Disable sleep mode of the IMU
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(0x6B);
    Wire.write(0x00);
    Wire.endTransmission(true);

    delay(10);

    // Decrease sensitivity
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(0x1B);
    Wire.write(0x10);
    Wire.endTransmission(true);
}

void loop() {
    // put your main code here, to run repeatedly:

    // Request registers 0x38 and following (sensor data)
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(I2C_ADDR, 14, true);

    // Sensor data are 16 bits values
    int16_t accX = Wire.read() << 8;
    accX |= (Wire.read() & 0xFF);

    int16_t accY = Wire.read() << 8;
    accY |= (Wire.read() & 0xFF);

    int16_t accZ = Wire.read() << 8;
    accZ |= (Wire.read() & 0xFF);

    int16_t temp = Wire.read() << 8;
    temp |= (Wire.read() & 0xFF);

    int16_t gyrX = Wire.read() << 8;
    gyrX |= (Wire.read() & 0xFF);

    int16_t gyrY = Wire.read() << 8;
    gyrY |= (Wire.read() & 0xFF);

    int16_t gyrZ = Wire.read() << 8;
    gyrZ |= (Wire.read() & 0xFF);

//    Serial.print("Acc: ");
//    Serial.print(accX);
//    Serial.print(" ");
//    Serial.print(accY);
//    Serial.print(" ");
//    Serial.println(accZ);
//    Serial.print("Gyr: ");
//    Serial.print(gyrX);
//    Serial.print(" ");
//    Serial.print(gyrY);
//    Serial.print(" ");
//    Serial.println(gyrZ);

    // TODO find an appropriate threshold
    if(gyrX > 15000)
    {
        // Press key and turn on the LED
        Keyboard.press(KEY);
        digitalWrite(13, HIGH);
    }
    else
    {
        // Release key and turn off the LED
        Keyboard.releaseAll();
        digitalWrite(13, LOW);
    }

    delay(50);
}
