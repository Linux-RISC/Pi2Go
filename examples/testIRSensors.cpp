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

		printf("Count: %u\n",counter);
		printf("Left: %s\n",pi2GoFull.getLeftIRObstacleSensor()?"ON":"OFF");
		printf("Center: %s\n",pi2GoFull.getCentreIRObstacleSensor()?"ON":"OFF");
		printf("Right: %s\n",pi2GoFull.getRightIRObstacleSensor()?"ON":"OFF");
		printf("Line left: %s\n",pi2GoFull.getLeftIRLineSensor()?"ON":"OFF");
		printf("Line right: %s\n",pi2GoFull.getRightIRLineSensor()?"ON":"OFF");
		puts("\n");
		counter++;

		delay(500);
	}

	return EXIT_SUCCESS;
}
//--------------------------------------------------------------------------------

