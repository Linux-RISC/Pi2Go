#include <stdio.h>
#include <stdlib.h>
#include "Pi2GoFull.hpp"

//--------------------------------------------------------------------------------
int main(int argc, char **argv) {

	wiringPiSetup () ;

	Pi2GoFull pi2GoFull;
	pi2GoFull.init ();

	while (true) {

		printf("distance: %.2f cm\n",Pi2GoFull::getDistance());

		delay(250);
	}

	return EXIT_SUCCESS;
}
//--------------------------------------------------------------------------------

