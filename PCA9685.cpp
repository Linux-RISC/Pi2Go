/**
 * @brief methods to control LEDs using PCA9685 chip
 * @author Alvaro Llamas alvarollamasg@gmail.com
 * @date 2016/08/04
 * @copyright Apache License
 *
 * Adafruit 16-Channel 12-bit PWM/Servo Driver - I2C interface - PCA9685
 * https://www.adafruit.com/product/815
 * 16-channel, 12-bit PWM Fm+ IC-bus LED controller
 * https://cdn-shop.adafruit.com/datasheets/PCA9685.pdf
 */

#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "PCA9685.hpp"

int PCA9685::fd;

//--------------------------------------------------------------------------------
/**
	@brief initializes PCA9685 using wiringPiI2CSetup
	@returns the result of the operation: true if ok, false if error
*/
bool PCA9685::init () {

	if ((fd = wiringPiI2CSetup(0x40)) < 0) {
		puts ("wiringPiI2CSetup failed");
		return false;
	}
    /*
	*** adapted from pca9685.py ***
	bus.write_byte_data(PCA, 1, 0x04)  # set Mode2 outputs to push-pull
    mode1 = bus.read_byte_data(PCA, 0) # get current Mode1 register
    mode1 &= 0x7f # ignore the reset bit
    mode1 |= 0x10 # set Sleep bit
    bus.write_byte_data(PCA, 0, mode1) # sleep
    bus.write_byte_data(PCA, 254, 101)    # set prescaler
    mode1 &= 0xef # clear Sleep bit
    bus.write_byte_data(PCA, 0, mode1 | 0x80) # wake up
    time.sleep(0.005)*/

	// set Mode2 outputs to push-pull
	wiringPiI2CWriteReg8(fd,1,0x04);
	// get current Mode1 register
	int mode1 = wiringPiI2CReadReg8(fd,0);
	// ignore the reset bit
    mode1 &= 0x7f;
	// set Sleep bit
    mode1 |= 0x10;
	// sleep
	wiringPiI2CWriteReg8(fd,0,mode1);
	// set prescaler
	wiringPiI2CWriteReg8(fd,254,101);
	// clear Sleep bit
    mode1 &= 0xef;
	// wake up
	wiringPiI2CWriteReg8(fd,0,mode1 | 0x80);
	delay (5);

	return true;
}
//--------------------------------------------------------------------------------
void PCA9685::setRGBLED (unsigned led,unsigned red,unsigned green,unsigned blue) {

	if (led>3)
		return;

        /*
		*** adapted from pca9685.py ***
		bus.write_byte_data(PCA, RED + led*12 + 0, 0)
        bus.write_byte_data(PCA, RED + led*12 + 1, 0)
        bus.write_byte_data(PCA, RED + led*12 + 2, red & 0xff)
        bus.write_byte_data(PCA, RED + led*12 + 3, red >> 8)
        bus.write_byte_data(PCA, GREEN + led*12 + 0, 0)
        bus.write_byte_data(PCA, GREEN + led*12 + 1, 0)
        bus.write_byte_data(PCA, GREEN + led*12 + 2, green & 0xff)
        bus.write_byte_data(PCA, GREEN + led*12 + 3, green >> 8)
        bus.write_byte_data(PCA, BLUE + led*12 + 0, 0)
        bus.write_byte_data(PCA, BLUE + led*12 + 1, 0)
        bus.write_byte_data(PCA, BLUE + led*12 + 2, blue & 0xff)
        bus.write_byte_data(PCA, BLUE + led*12 + 3, blue >> 8)*/

	// Sets the LED specified to required RGB value. 0 >= LED <= 3; 0 <= R,G,B <= 4095
	// 0=front, 1=left, 2=right, 3=back
	wiringPiI2CWriteReg8(fd,RED + led*12 + 0,0);
	wiringPiI2CWriteReg8(fd,RED + led*12 + 1,0);
	wiringPiI2CWriteReg8(fd,RED + led*12 + 2,red & 0xff);
	wiringPiI2CWriteReg8(fd,RED + led*12 + 3,red >> 8);
	wiringPiI2CWriteReg8(fd,GREEN + led*12 + 0,0);
	wiringPiI2CWriteReg8(fd,GREEN + led*12 + 1,0);
	wiringPiI2CWriteReg8(fd,GREEN + led*12 + 2,green & 0xff);
	wiringPiI2CWriteReg8(fd,GREEN + led*12 + 3,green >> 8);
	wiringPiI2CWriteReg8(fd,BLUE + led*12 + 0,0);
	wiringPiI2CWriteReg8(fd,BLUE + led*12 + 1,0);
	wiringPiI2CWriteReg8(fd,BLUE + led*12 + 2,blue & 0xff);
	wiringPiI2CWriteReg8(fd,BLUE + led*12 + 3,blue >> 8);
}
//--------------------------------------------------------------------------------

