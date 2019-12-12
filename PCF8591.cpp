/**
 * @brief methods to read analog values using PCF8591 chip
 * @author Alvaro Llamas alvarollamasg@gmail.com
 * @date 2016/08/04
 * @copyright Apache License
 * @verbatim 
 * 8-bit A/D and D/A converter
 * http://www.nxp.com/documents/data_sheet/PCF8591.pdf
 * @endverbatim
 */

#include <stdio.h>
#include <wiringPi.h>
//#include <wiringPiI2C.h>
#include <pcf8591.h>
#include "PCF8591.hpp"

int PCF8591::fd;
unsigned PCF8591::rawValue[4];

//--------------------------------------------------------------------------------
bool PCF8591::init () {

	// http://stackoverflow.com/questions/28750703/raspberry-pi-and-i2c-in-c-with-wiringpi-for-pcf8591
	/*if ((fd = wiringPiI2CSetup(0x48)) < 0) {
		puts ("wiringPiI2CSetup failed");
		return false;
	}*/
	if (pcf8591Setup(PINBASE,0x48) < 0) {
		puts ("pcf8591Setup failed");
		return false;
	}

	for (unsigned i=0; i<4; i++)
		rawValue[i] = 0;
		
	return true;
}
//--------------------------------------------------------------------------------
int PCF8591::readAnalogInput (unsigned AD_channel) {

	if (AD_channel>3)
		return -1;

	// http://stackoverflow.com/questions/28750703/raspberry-pi-and-i2c-in-c-with-wiringpi-for-pcf8591
    // Previous value
	//rawValue[AD_channel] = wiringPiI2CReadReg8(fd,0x40|AD_channel);
	// force new A/D conversion
	//rawValue[AD_channel] = wiringPiI2CReadReg8(fd,0x40|AD_channel);

	rawValue[AD_channel] = analogRead(PINBASE + AD_channel);

	return rawValue[AD_channel];
}
//--------------------------------------------------------------------------------
int PCF8591::getLastAnalogValue (unsigned AD_channel) {

	if (AD_channel>3)
		return -1;

	return rawValue[AD_channel];
}
//--------------------------------------------------------------------------------
float PCF8591::rawToVolts (unsigned rawValue) {

	return rawValue*3.3/255;
}
//--------------------------------------------------------------------------------

