#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "Robot.hpp"

using namespace std;

//--------------------------------------------------------------------------------
int main(int argc, char **argv) {

	Robot robot;
	string s = "press switch to begin wandering and while moving to stop the robot";

	robot.notifyStartup ();
	puts ((string(robot.getStringTime())+" "+s).c_str());
	while (true) {
		// wait until switch is pressed
		if (robot.pi2GoFull.getSwitch()) {
			// wait until switch is released
			while (robot.pi2GoFull.getSwitch())
				delay (100);
			robot.controller();
			puts ((string(robot.getStringTime())+" "+s).c_str());
			/*robot.pi2GoFull.forward (30);
			delay(2000);
			robot.pi2GoFull.stop();
			robot.pi2GoFull.reverse (30);
			delay(2000);
			break;*/			
		}
		if (robot.obstacleDetected())
			robot.notifyObstacle();

		delay (100);
	}

	return EXIT_SUCCESS;
}
//--------------------------------------------------------------------------------

