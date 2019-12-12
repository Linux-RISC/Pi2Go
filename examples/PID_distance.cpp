#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <libgen.h>
#include <string.h>
#include <string>
#include "Robot.hpp"
#include "PID.hpp"

using namespace std;

//--------------------------------------------------------------------------------
static void help(char* execName) {
	
	printf ("Usage: %s [Kp] [Ki] [Kd] [target distance cm] [maximum accepted percentage of error] [sample time 1-60000 ms] [external sample time check 0-1]\n",basename(execName));
	puts ("* internal sample time check: the time between calculations is checked by PID, for every loop it's necessary measuring and sending the distance to compute().");
	puts ("* external sample time check: the time between calculations is checked by the user, just measure the distance when calling to compute() after the sample time elapsed. This may save battery.");
	printf ("example that works: %s 10 0.00001 0.01 20 5 100 1\n",basename(execName));
	exit (EXIT_FAILURE);
}
//--------------------------------------------------------------------------------
int main(int argc, char **argv) {

	if (argc!=8)
		help(argv[0]);
		
	float Kp, Ki, Kd, target_distance, maxError;
	Kp = atof(argv[1]);
	Ki = atof(argv[2]);
	Kd = atof(argv[3]);
	target_distance = atof(argv[4]);
	maxError = atof(argv[5]);
	unsigned sampleTime_ms = atoi(argv[6]);
	bool externalTimeCheck = atoi(argv[7])?true:false;
	if (Kp<0 || Ki<0 || Kd<0 || target_distance<0 || maxError<0 || maxError>100 || 
		sampleTime_ms<1 || sampleTime_ms>60000 ||
		strlen(argv[7])!=1 || (argv[7][0]!='0' && argv[7][0]!='1'))
		help(argv[0]);
	printf("%s Kp=%.6f, Ki=%.6f, Kd=%.6f, distance=%.2f cm, max. error=%.2f%%, sample time=%u, external time check=%s\n",Robot::getStringTime(),Kp,Ki,Kd,target_distance,maxError,sampleTime_ms,externalTimeCheck?"true":"false");
	
	// Kp, Ki, Kd, setPoint (20 cm), minOutput (0%), maxOutput (100%);
	PID myPID(Kp,Ki,Kd,0,-100,100);
	myPID.set_sampleTime_ms(sampleTime_ms);
	
	string s = "press switch to begin movement and while moving to stop the robot";
	const unsigned SLEEP_TIME_MS = 10;
	bool moving = false;
	bool b_get_previous_time = true;
	struct timeval previous_time, current_time;
	float dt;
	Robot robot;

	robot.notifyStartup ();
	puts ((string(robot.getStringTime())+" "+s).c_str());
	while (true) {
		// wait until switch is pressed
		if (robot.pi2GoFull.getSwitch()) {
			if (!moving) {
				puts ((string(robot.getStringTime())+" robot is moving").c_str());
				moving = true;
				b_get_previous_time = true;
			}
			else {
				robot.buttonPressedEvent();
				moving = false;
				puts ((string(robot.getStringTime())+" "+s).c_str());
			}
			// wait until switch is released
			while (robot.pi2GoFull.getSwitch())
				delay (100);
		}

		delay (SLEEP_TIME_MS);

		if (!moving)
			continue;
		
		if (robot.pi2GoFull.getAnyIRObstacleSensor()) {
			robot.pi2GoFull.stop();
			robot.obstacleDetectedMessage();
			moving = false;
			puts ((string(robot.getStringTime())+" "+s).c_str());
			robot.notifyObstacle();
			continue;
		}

		if (externalTimeCheck) {
			if (b_get_previous_time) {
				gettimeofday(&previous_time,NULL);
				b_get_previous_time = false;
				continue;
			}
			else {
				gettimeofday(&current_time,NULL);
				
				if ((dt=PID::difftime_ms(previous_time,current_time))<myPID.get_sampleTime_ms()) {
					//printf ("dt=%.2f\n",dt);
					continue;
				}
			}
		}

		//struct timeval time_begin, time_end;
		//gettimeofday(&time_begin,NULL);
		float measured_distance = robot.pi2GoFull.getDistance();
		//gettimeofday(&time_end,NULL);
		//PID::difftime_ms_msg(time_begin,time_end,(char*)"time for distance measuring:");

		printf ("%s distance=%.2f\n",robot.getStringTime(),measured_distance);

		if (myPID.compute (fabs(target_distance-measured_distance),externalTimeCheck,dt)) {
			b_get_previous_time = true;
			printf("%s Kp=%.2f, Ki=%.2f, Kd=%.2f\n",robot.getStringTime(),myPID.get_Kp(),myPID.get_Ki(),myPID.get_Kd());
			printf("%s setPoint=%.2f, input=%.2f, error=%.2f, output=%.2f, previous_error=%.2f\n",robot.getStringTime(),myPID.get_setPoint(),myPID.get_input(),myPID.get_error(),myPID.get_output(),myPID.get_previous_error());
			printf("%s dt=%.2f, sampletime_ms=%u, proportional=%.2f, integral=%.2f, derivative=%.2f\n",robot.getStringTime(),myPID.get_dt(),myPID.get_sampleTime_ms(),myPID.get_proportional(),myPID.get_integral(),myPID.get_derivative());
			printf("%s Kp*proportional=%.2f, Ki*integral=%.2f, Kd*derivative=%.2f\n",robot.getStringTime(),Kp*myPID.get_proportional(),Ki*myPID.get_integral(),Kd*myPID.get_derivative());
			float percentage = fabs((target_distance-measured_distance)/target_distance*100);
			printf("%s target distance=%.2f, measured_distance=%.2f, %% of error=%.2f%%\n",robot.getStringTime(),target_distance,measured_distance,percentage);
			puts("");
			if (percentage<=maxError)
				robot.pi2GoFull.stop();
			else
				robot.pi2GoFull.go(measured_distance>target_distance?-1*myPID.get_output():myPID.get_output());
		}		
	}

	return EXIT_SUCCESS;
}
//--------------------------------------------------------------------------------

