/**
 * @brief methods to read analog values using PCF8591 chip
 * @author Alvaro Llamas alvarollamasg@gmail.com
 * @date 2016/08/04
 * @copyright Apache License
 *
 * 8-bit A/D and D/A converter
 * http://www.nxp.com/documents/data_sheet/PCF8591.pdf
 */

#ifndef __PCF8591_HPP__
#define __PCF8591_HPP__

class PCF8591 {

	static int fd;
	static unsigned rawValue[4];
	static const unsigned PINBASE = 100;

public:

	static bool init ();
	// 0 <= AD_channel <= 3
	static int readAnalogInput (unsigned AD_channel);
	static int getLastAnalogValue (unsigned AD_channel);
	static float rawToVolts (unsigned rawValue);
};

#endif
