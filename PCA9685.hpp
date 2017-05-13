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

#ifndef __PCA9685_HPP__
#define __PCA9685_HPP__

class PCA9685 {

	static int fd;
	static const unsigned RED = 14, GREEN = 10, BLUE = 6;

public:

	static bool init ();
	static void setRGBLED (unsigned led,unsigned red,unsigned green,unsigned blue);
};

#endif
