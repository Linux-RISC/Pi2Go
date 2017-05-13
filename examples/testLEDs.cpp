#include <stdlib.h>
#include "Pi2GoFull.hpp"

//--------------------------------------------------------------------------------
int main(int argc, char **argv) {

	wiringPiSetup () ;

	Pi2GoFull pi2GoFull;
	pi2GoFull.init ();

	while (true) {

		digitalWrite (Pi2GoFull::DOWN_RIGHT_LED,Pi2GoFull::LED_TURN_OFF);
		digitalWrite (Pi2GoFull::UP_LEFT_LED,Pi2GoFull::LED_TURN_ON);
		delay(500);
		digitalWrite (Pi2GoFull::UP_LEFT_LED,Pi2GoFull::LED_TURN_OFF);
		digitalWrite (Pi2GoFull::UP_RIGHT_LED,Pi2GoFull::LED_TURN_ON);
		delay(500);
		digitalWrite (Pi2GoFull::UP_RIGHT_LED,Pi2GoFull::LED_TURN_OFF);
		digitalWrite (Pi2GoFull::DOWN_LEFT_LED,Pi2GoFull::LED_TURN_ON);
		delay(500);
		digitalWrite (Pi2GoFull::DOWN_LEFT_LED,Pi2GoFull::LED_TURN_OFF);
		digitalWrite (Pi2GoFull::DOWN_CENTER_LED,Pi2GoFull::LED_TURN_ON);
		delay(500);
		digitalWrite (Pi2GoFull::DOWN_CENTER_LED,Pi2GoFull::LED_TURN_OFF);
		digitalWrite (Pi2GoFull::DOWN_RIGHT_LED,Pi2GoFull::LED_TURN_ON);
		delay(500);
	}

	return EXIT_SUCCESS;
}
//--------------------------------------------------------------------------------

