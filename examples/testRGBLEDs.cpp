#include <stdio.h>
#include <stdlib.h>
#include "Pi2GoFull.hpp"

//--------------------------------------------------------------------------------
int main(int argc, char **argv) {

	wiringPiSetup () ;

	Pi2GoFull pi2GoFull;
	pi2GoFull.init ();

	while (true) {

		pi2GoFull.setAllRGBLEDs(0,0,0);

		for (unsigned i=0; i<4; i++) {
			pi2GoFull.setRGBLED(i,4095,0,0);
			delay (250);
		}
		pi2GoFull.setAllRGBLEDs(0,0,0);

		for (unsigned i=0; i<4; i++) {
			pi2GoFull.setRGBLED(i,0,4095,0);
			delay (250);
		}
		pi2GoFull.setAllRGBLEDs(0,0,0);

		for (unsigned i=0; i<4; i++) {
			pi2GoFull.setRGBLED(i,0,0,4095);
			delay (250);
		}
		pi2GoFull.setAllRGBLEDs(0,0,0);

		for (unsigned i=0; i<4; i++) {
			pi2GoFull.setRGBLED(i,4095,4095,4095);
			delay (250);
		}
		pi2GoFull.setAllRGBLEDs(0,0,0);

		for (int i=0; i<=4095; i+=100) {
			pi2GoFull.setRGBLED(0,i,0,0);
			pi2GoFull.setRGBLED(1,i,0,0);
			pi2GoFull.setRGBLED(2,i,0,0);
			pi2GoFull.setRGBLED(3,i,0,0);
		}
		for (int i=4095; i>0; i-=100) {
			pi2GoFull.setRGBLED(0,i,0,0);
			pi2GoFull.setRGBLED(1,i,0,0);
			pi2GoFull.setRGBLED(2,i,0,0);
			pi2GoFull.setRGBLED(3,i,0,0);
		}
		for (int i=0; i<=4095; i+=100) {
			pi2GoFull.setRGBLED(0,0,i,0);
			pi2GoFull.setRGBLED(1,0,i,0);
			pi2GoFull.setRGBLED(2,0,i,0);
			pi2GoFull.setRGBLED(3,0,i,0);
		}
		for (int i=4095; i>0; i-=100) {
			pi2GoFull.setRGBLED(0,0,i,0);
			pi2GoFull.setRGBLED(1,0,i,0);
			pi2GoFull.setRGBLED(2,0,i,0);
			pi2GoFull.setRGBLED(3,0,i,0);
		}
		for (int i=0; i<=4095; i+=100) {
			pi2GoFull.setRGBLED(0,0,0,i);
			pi2GoFull.setRGBLED(1,0,0,i);
			pi2GoFull.setRGBLED(2,0,0,i);
			pi2GoFull.setRGBLED(3,0,0,i);
		}
		for (int i=4095; i>0; i-=100) {
			pi2GoFull.setRGBLED(0,0,0,i);
			pi2GoFull.setRGBLED(1,0,0,i);
			pi2GoFull.setRGBLED(2,0,0,i);
			pi2GoFull.setRGBLED(3,0,0,i);
		}
		for (int i=0; i<=4095; i+=100) {
			pi2GoFull.setRGBLED(0,i,i,i);
			pi2GoFull.setRGBLED(1,i,i,i);
			pi2GoFull.setRGBLED(2,i,i,i);
			pi2GoFull.setRGBLED(3,i,i,i);
		}
		for (int i=4095; i>0; i-=100) {
			pi2GoFull.setRGBLED(0,i,i,i);
			pi2GoFull.setRGBLED(1,i,i,i);
			pi2GoFull.setRGBLED(2,i,i,i);
			pi2GoFull.setRGBLED(3,i,i,i);
		}
		pi2GoFull.setAllRGBLEDs(0,0,0);
	}

	return EXIT_SUCCESS;
}
//--------------------------------------------------------------------------------

