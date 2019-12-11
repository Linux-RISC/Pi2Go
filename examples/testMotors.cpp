#include <stdio.h>
#include <stdlib.h>
#include "Pi2GoFull.hpp"

//--------------------------------------------------------------------------------
int main(int argc, char **argv) {

	wiringPiSetup () ;

	Pi2GoFull pi2GoFull;
	pi2GoFull.init ();

	puts ("The motors will move in 10 seconds. Please flip the robot up to avoid any damage");
	delay(10000);
	
	puts ("forward");
	pi2GoFull.forward(30);
	delay(500);

	pi2GoFull.stop();
	delay(500);

	puts ("reverse");
	pi2GoFull.reverse(30);
	delay(500);

	pi2GoFull.stop();
	delay(500);

	puts ("spin left");
	pi2GoFull.spinLeft(30);
	delay(1000);

	pi2GoFull.stop();
	delay(500);

	puts ("spin right");
	pi2GoFull.spinRight(30);
	delay(1000);

	pi2GoFull.stop();
	delay(500);

	puts ("turnForward(20,50)");
	pi2GoFull.turnForward(20,50);
	delay(1000);

	pi2GoFull.stop();
	delay(500);

	puts ("turnReverse(20,50)");
	pi2GoFull.turnReverse(20,50);
	delay(1000);

	return EXIT_SUCCESS;
}
//--------------------------------------------------------------------------------

