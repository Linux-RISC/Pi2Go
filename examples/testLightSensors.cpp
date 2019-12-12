#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Pi2GoFull.hpp"

//--------------------------------------------------------------------------------
int main(int argc, char **argv) {

	wiringPiSetup () ;

	Pi2GoFull pi2GoFull;
	pi2GoFull.init ();

	while (true) {

		for (unsigned i=0; i<3; i++) {
			printf ("AD(0)=%d, %.2fV\n",pi2GoFull.pcf8591.readAnalogInput (0),pi2GoFull.pcf8591.rawToVolts(pi2GoFull.pcf8591.getLastAnalogValue(0)));
			printf ("AD(1)=%d, %.2fV\n",pi2GoFull.pcf8591.readAnalogInput (1),pi2GoFull.pcf8591.rawToVolts(pi2GoFull.pcf8591.getLastAnalogValue(1)));
			printf ("AD(2)=%d, %.2fV\n",pi2GoFull.pcf8591.readAnalogInput (2),pi2GoFull.pcf8591.rawToVolts(pi2GoFull.pcf8591.getLastAnalogValue(2)));
			printf ("AD(3)=%d, %.2fV\n",pi2GoFull.pcf8591.readAnalogInput (3),pi2GoFull.pcf8591.rawToVolts(pi2GoFull.pcf8591.getLastAnalogValue(3)));
			puts ("\n");
			sleep (1);
		}
		for (unsigned i=0; i<=3; i++)
			printf ("getLight(%u)=%d\n",i,pi2GoFull.getLight(i));
		puts ("\n");
		sleep (1);
	}

	return EXIT_SUCCESS;
}
//--------------------------------------------------------------------------------

