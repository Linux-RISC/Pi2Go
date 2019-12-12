#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "Robot.hpp"

using namespace std;

char Robot::sTime[8];

//--------------------------------------------------------------------------------
unsigned Robot::get_lowDistance () {

	return lowDistance;
}
//--------------------------------------------------------------------------------
unsigned Robot::get_highDistance () {

	return highDistance;
}
//--------------------------------------------------------------------------------
unsigned Robot::get_lowDistanceSpeed () {

	return lowDistanceSpeed;
}
//--------------------------------------------------------------------------------
unsigned Robot::get_highDistanceSpeed () {

	return highDistanceSpeed;
}
//--------------------------------------------------------------------------------
bool Robot::set_lowDistance (unsigned distance) {

	lowDistance = distance;
	return true;
}
//--------------------------------------------------------------------------------
bool Robot::set_highDistance (unsigned distance) {

	highDistance = distance;
	return true;
}
//--------------------------------------------------------------------------------
bool Robot::set_lowDistanceSpeed (unsigned speed) {

	if (speed>100)
		speed=100;
	lowDistanceSpeed = speed;
	return true;
}
//--------------------------------------------------------------------------------
bool Robot::set_highDistanceSpeed (unsigned speed) {

	if (speed>100)
		speed=100;
	highDistanceSpeed = speed;
	return true;
}
//--------------------------------------------------------------------------------
Robot::Robot () {

	lowDistanceSpeed = 30;
	highDistanceSpeed = 50;
	lowDistance = 10;
	highDistance = 70;
	behavior = SEARCH_OBSTACLE;
	lastAvoidMovedRight = false;
	bObstacleDetected = false;
	bObstacleDetectedByDistance = false;
	wiringPiSetup ();
	pi2GoFull.init ();
}
//--------------------------------------------------------------------------------
void Robot::controller () {
	
	bool firstCall = true;
	setBehavior (SEARCH_OBSTACLE);
	while (true) {
		switch (behavior) {
			case SEARCH_OBSTACLE:
				_1_searchObstacle (firstCall);
				firstCall = false;
				setBehavior (switchPressed?ERROR:AVOID_OBSTACLE);
				//setBehavior (AVOID_OBSTACLE);
				break;
			case AVOID_OBSTACLE:	
				setBehavior (_2_avoidObstacle ()?SEARCH_OBSTACLE:ERROR);
				break;
			default:
				notifyError ();
				return;
				break;		
		}
	}
}
//--------------------------------------------------------------------------------
unsigned Robot::setBehavior (unsigned behavior) {

	this->behavior = behavior;
	return behavior;
}
//--------------------------------------------------------------------------------
void Robot::_1_searchObstacle (bool firstCall) {

	if (firstCall) {
		srand(time(NULL));
		spiral = ((float)rand()/RAND_MAX)<0.50 ? true : false;
		alternateMovement();
	}
	// move in spiral to the opposite direction of the obstacle found
	else {
		spiral = true;
		if (lastAvoidMovedRight)
			pi2GoFull.turnForward(lowDistanceSpeed,highDistanceSpeed);
		else
			pi2GoFull.turnForward(highDistanceSpeed,lowDistanceSpeed);
	}

	unsigned count = 0;
	while (true) {
		if (obstacleDetected ()) {
			pi2GoFull.stop();
			obstacleDetectedMessage();
			notifyObstacle();
			return;
		}
		printf ("%s %u SEARCH_OBSTACLE\n",string(getStringTime()).c_str(),++count);

		switchPressed = pi2GoFull.getSwitch();
		if (switchPressed) {
			buttonPressedEvent();
			return;
		}

		// alternate movement every some time
		if (count==50) {
			alternateMovement();
			count = 0;
		}

		if (!spiral)
			controlSpeed(distance);

		delay (100);
	}
}
//--------------------------------------------------------------------------------
bool Robot::_2_avoidObstacle () {

	unsigned count = 0;
	while (true) {
		bool obstacle = (bObstacleDetected || bObstacleDetectedByDistance);
		printf ("%s %u AVOID_OBSTACLE, obstacle=%s\n",string(getStringTime()).c_str(),++count,obstacle?"true":"false");

		if (!obstacle)
			return true;
		else {
			obstacleDetectedMessage();
			notifyObstacle();
		}
				
		// limit the maximum attempts
		if (count >= 5) {
			puts ((string(getStringTime())+" "+"ERROR: too much attempts to avoid an obstacle").c_str());
			break; 
		}

		if (pi2GoFull.getCentreIRObstacleSensor() || bObstacleDetectedByDistance) {
			// alternate movement using right and left direction
			if (lastAvoidMovedRight)
				pi2GoFull.turnReverse(lowDistanceSpeed,highDistanceSpeed);
			else
				pi2GoFull.turnReverse(highDistanceSpeed,lowDistanceSpeed);
			lastAvoidMovedRight = !lastAvoidMovedRight;
		}
		else
		if (pi2GoFull.getRightIRObstacleSensor()) {
			pi2GoFull.turnReverse(highDistanceSpeed,lowDistanceSpeed);
			lastAvoidMovedRight = true;
		}
		else
		if (pi2GoFull.getLeftIRObstacleSensor()) {
			pi2GoFull.turnReverse(lowDistanceSpeed,highDistanceSpeed);
			lastAvoidMovedRight = false;
		}
		else
			return true;

		puts ((string(getStringTime())+" "+"moving back and "+(lastAvoidMovedRight?"right":"left")).c_str());

		// add a random time to randomize movements
		srand(time(NULL));
		unsigned randomTime = ((float)rand()/RAND_MAX)*1000;
		unsigned totalTime = 1200+randomTime;

		const unsigned STEP = 10; 
		for (unsigned i=0; i<=totalTime; i+=STEP) {
			switchPressed = pi2GoFull.getSwitch();
			if (switchPressed) {
				buttonPressedEvent();
				return false;
			}
			delay(STEP);
		}

		pi2GoFull.stop();

		obstacle = obstacleDetected ();
	}

	return false;
}
//--------------------------------------------------------------------------------
void Robot::alternateMovement () {

	spiral = !spiral;
	printf ("%s moving %s\n",string(getStringTime()).c_str(),spiral?"in spiral":"along");

	if (spiral) {
		srand(time(NULL));
		bool right = ((float)rand()/RAND_MAX)<0.50 ? true : false;
		if (right)
			pi2GoFull.turnForward(highDistanceSpeed,lowDistanceSpeed);
		else
			pi2GoFull.turnForward(lowDistanceSpeed,highDistanceSpeed);
	}
	else {
		speed = lowDistanceSpeed;
		pi2GoFull.forward(speed);
	}
}
//--------------------------------------------------------------------------------
void Robot::controlSpeed (float distance) {

	if (spiral)
		return;

	// decrease speed when distance is low
	if ((distance<highDistance) && (speed!=lowDistanceSpeed)) {
		puts ((string(getStringTime())+" "+"decrease speed").c_str());
		speed = lowDistanceSpeed;
		pi2GoFull.forward(speed);
		return;
	}
	// increase speed when distance is high
	if ((distance>=highDistance) && (speed!=highDistanceSpeed)) {
		puts ((string(getStringTime())+" "+"increase speed").c_str());
		speed = highDistanceSpeed;
		pi2GoFull.forward(speed);
	}
}
//--------------------------------------------------------------------------------
bool Robot::obstacleDetected () {

	distance = pi2GoFull.getDistance();
	bObstacleDetectedByDistance = (distance<=lowDistance);
	bObstacleDetected = pi2GoFull.getAnyIRObstacleSensor();
	return (bObstacleDetected || bObstacleDetectedByDistance);
}
//--------------------------------------------------------------------------------
void Robot::notifyStartup () {

	for (int i=0; i<=4095; i+=100) {
		pi2GoFull.setRGBLED(2,i,0,0);
		pi2GoFull.setRGBLED(0,0,i,0);
		pi2GoFull.setRGBLED(3,0,0,i);
		pi2GoFull.setRGBLED(1,i,i,i);
	}
	for (int i=4095; i>0; i-=100) {
		pi2GoFull.setRGBLED(2,i,0,0);
		pi2GoFull.setRGBLED(0,0,i,0);
		pi2GoFull.setRGBLED(3,0,0,i);
		pi2GoFull.setRGBLED(1,i,i,i);
	}

	pi2GoFull.setAllRGBLEDsOff();	
}
//--------------------------------------------------------------------------------
void Robot::notifyObstacle () {

	if (!bObstacleDetected && !bObstacleDetectedByDistance)
		return;

	for (int i=0; i<=4095; i+=100) {
		if (pi2GoFull.getRightIRObstacleSensor())
			pi2GoFull.setRGBLED(2,i,0,0);
		if (pi2GoFull.getLeftIRObstacleSensor())
			pi2GoFull.setRGBLED(0,i,0,0);
		if (pi2GoFull.getCentreIRObstacleSensor())
			pi2GoFull.setRGBLED(3,i,0,0);
		if (bObstacleDetectedByDistance)
			pi2GoFull.setRGBLED(1,i,0,0);
	}
	for (int i=4095; i>0; i-=100) {
		if (pi2GoFull.getRightIRObstacleSensor())
			pi2GoFull.setRGBLED(2,i,0,0);
		if (pi2GoFull.getLeftIRObstacleSensor())
			pi2GoFull.setRGBLED(0,i,0,0);
		if (pi2GoFull.getCentreIRObstacleSensor())
			pi2GoFull.setRGBLED(3,i,0,0);
		if (bObstacleDetectedByDistance)
			pi2GoFull.setRGBLED(1,i,0,0);
	}

	pi2GoFull.setAllRGBLEDsOff();	
}
//--------------------------------------------------------------------------------
void Robot::notifyError () {

	for (int i=0; i<=4095; i+=100) {
		pi2GoFull.setRGBLED(2,i,0,0);
		pi2GoFull.setRGBLED(0,i,0,0);
		pi2GoFull.setRGBLED(3,i,0,0);
		pi2GoFull.setRGBLED(1,i,0,0);
	}
	for (int i=4095; i>0; i-=100) {
		pi2GoFull.setRGBLED(2,i,0,0);
		pi2GoFull.setRGBLED(0,i,0,0);
		pi2GoFull.setRGBLED(3,i,0,0);
		pi2GoFull.setRGBLED(1,i,0,0);
	}

	pi2GoFull.setAllRGBLEDsOff();	
}
//--------------------------------------------------------------------------------
char* Robot::getStringTime () {

	time_t currentTime;
	struct tm* _tm;

	time (&currentTime);
	_tm = localtime (&currentTime);
	sprintf (sTime,"%02d:%02d:%02d",_tm->tm_hour,_tm->tm_min,_tm->tm_sec);
	
	return sTime;
}
//--------------------------------------------------------------------------------
void Robot::buttonPressedEvent () {

	pi2GoFull.stop();
	puts ((string(getStringTime())+" "+"switch pressed, robot stopped").c_str());
}
//--------------------------------------------------------------------------------
void Robot::obstacleDetectedMessage () {

	puts ((string(getStringTime())+" "+"obstacle detected").c_str());
}
//--------------------------------------------------------------------------------

