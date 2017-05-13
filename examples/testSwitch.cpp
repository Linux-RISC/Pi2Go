#include <stdio.h>
#include <stdlib.h>
#include "Pi2GoFull.hpp"

//--------------------------------------------------------------------------------
int main(int argc, char **argv) {

	wiringPiSetup () ;

	Pi2GoFull pi2GoFull;
	pi2GoFull.init ();

	unsigned counter = 0;
	while (true) {

		if (pi2GoFull.getSwitch()) {
			printf("%u pressed\n",counter);
			counter++;
		}
		else
			puts("OFF");

		delay(250);
	}

	return EXIT_SUCCESS;
}
//--------------------------------------------------------------------------------

