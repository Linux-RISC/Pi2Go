#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>
#include <wiringPi.h>
#include <softPwm.h>
#include "Pi2GoFull.hpp"

int Pi2GoFull::leftSpeed, Pi2GoFull::rightSpeed;
//--------------------------------------------------------------------------------
Pi2GoFull::Pi2GoFull () {

	leftSpeed = 0;
	rightSpeed = 0;
}
//--------------------------------------------------------------------------------
Pi2GoFull::~Pi2GoFull () {

	cleanup ();
}
//--------------------------------------------------------------------------------
void Pi2GoFull::signal_callback_handler (int signum) {

	cleanup ();
	exit(EXIT_SUCCESS);
}
//--------------------------------------------------------------------------------
void Pi2GoFull::resetAllLEDs () {

	pinMode (UP_LEFT_LED,INPUT);
	pinMode (DOWN_LEFT_LED,INPUT);
	pinMode (DOWN_CENTER_LED,INPUT);
	pinMode (DOWN_RIGHT_LED,INPUT);
	pinMode (UP_RIGHT_LED,INPUT);
}
//--------------------------------------------------------------------------------
void Pi2GoFull::setAllLEDsOff () {

	pinMode (UP_LEFT_LED,OUTPUT);
	digitalWrite (UP_LEFT_LED,LED_TURN_OFF);

	pinMode (DOWN_LEFT_LED,OUTPUT);
	digitalWrite (DOWN_LEFT_LED,LED_TURN_OFF);

	pinMode (DOWN_CENTER_LED,OUTPUT);
	digitalWrite (DOWN_CENTER_LED,LED_TURN_OFF);

	pinMode (DOWN_RIGHT_LED,OUTPUT);
	digitalWrite (DOWN_RIGHT_LED,LED_TURN_OFF);

	pinMode (UP_RIGHT_LED,OUTPUT);
	digitalWrite (UP_RIGHT_LED,LED_TURN_OFF);
}
//--------------------------------------------------------------------------------
void Pi2GoFull::init (bool destructor) {

	// initialize PCF8591 Analog IO expander IC
	if (!destructor) {
		pcf8591.init ();
		pca9685.init ();
		softPwmCreate (LEFT_MOTOR_FORWARD,0,100);
		softPwmCreate (LEFT_MOTOR_REVERSE,0,100);
		softPwmCreate (RIGHT_MOTOR_FORWARD,0,100);
		softPwmCreate (RIGHT_MOTOR_REVERSE,0,100);
	}

	signal (SIGINT,Pi2GoFull::signal_callback_handler);
	signal (SIGTERM,Pi2GoFull::signal_callback_handler);
	signal (SIGFPE,Pi2GoFull::signal_callback_handler);

	// reset LEDs status
	resetAllLEDs();

	// turn all RGS LEDs off
	setAllRGBLEDsOff();

	// configure tact switch
	pinMode (TACT_SWITCH,INPUT);
	pullUpDnControl (TACT_SWITCH,PUD_UP);

	// stop motors
	stop ();

	return;
}
//--------------------------------------------------------------------------------
void Pi2GoFull::cleanup () {

	// stop motors
	stop ();
	pinMode (LEFT_MOTOR_FORWARD,OUTPUT);
	pinMode (LEFT_MOTOR_REVERSE,OUTPUT);
	pinMode (RIGHT_MOTOR_FORWARD,OUTPUT);
	pinMode (RIGHT_MOTOR_REVERSE,OUTPUT);

	init (true);
}
//--------------------------------------------------------------------------------
bool Pi2GoFull::getLeftIRLineSensor () {

	return digitalRead (LEFT_LINE_SENSOR)==OFF;
}
//--------------------------------------------------------------------------------
bool Pi2GoFull::getRightIRLineSensor () {

	return digitalRead (RIGHT_LINE_SENSOR)==OFF;
}
//--------------------------------------------------------------------------------
bool Pi2GoFull::getLeftIRObstacleSensor () {

	return digitalRead (LEFT_IR_OBSTACLE_SENSOR)==OFF;
}
//--------------------------------------------------------------------------------
bool Pi2GoFull::getRightIRObstacleSensor () {

	return digitalRead (RIGHT_IR_OBSTACLE_SENSOR)==OFF;
}
//--------------------------------------------------------------------------------
bool Pi2GoFull::getCentreIRObstacleSensor () {

	return digitalRead (CENTER_IR_OBSTACLE_SENSOR)==OFF;
}
//--------------------------------------------------------------------------------
bool Pi2GoFull::getAnyIRObstacleSensor () {

	return (getLeftIRObstacleSensor() || getRightIRObstacleSensor() || getCentreIRObstacleSensor());
}
//--------------------------------------------------------------------------------
void Pi2GoFull::setRGBLED (unsigned led,unsigned red,unsigned green,unsigned blue) {
	
	// Sets the LED specified to required RGB value. 0 >= LED <= 3; 0 <= R,G,B <= 4095
	// 0=front, 1=left, 2=right, 3=back
	pca9685.setRGBLED(led,red,green,blue);
}
//--------------------------------------------------------------------------------
void Pi2GoFull::setAllRGBLEDs (unsigned red,unsigned green,unsigned blue) {

	for (unsigned i=0; i<4; i++)
		pca9685.setRGBLED(i,red,green,blue);
}
//--------------------------------------------------------------------------------
void Pi2GoFull::setRGBLEDRed (unsigned led) {
	
	pca9685.setRGBLED(led,4095,0,0);
}
//--------------------------------------------------------------------------------
void Pi2GoFull::setRGBLEDGreen (unsigned led) {
	
	pca9685.setRGBLED(led,0,4095,0);
}
//--------------------------------------------------------------------------------
void Pi2GoFull::setRGBLEDBlue (unsigned led) {
	
	pca9685.setRGBLED(led,0,0,4095);
}
//--------------------------------------------------------------------------------
void Pi2GoFull::setRGBLEDWhite (unsigned led) {
	
	pca9685.setRGBLED(led,4095,4095,4095);
}
//--------------------------------------------------------------------------------
void Pi2GoFull::setRGBLEDOff (unsigned led) {
	
	pca9685.setRGBLED(led,0,0,0);
}
//--------------------------------------------------------------------------------
void Pi2GoFull::setAllRGBLEDsOff () {

	for (unsigned i=0; i<4; i++)
		pca9685.setRGBLED(i,0,0,0);
}
//--------------------------------------------------------------------------------
bool Pi2GoFull::getSwitch () {

	return digitalRead (TACT_SWITCH)==OFF;
}
//--------------------------------------------------------------------------------
int Pi2GoFull::getLight (unsigned sensor) {
	return pcf8591.readAnalogInput (sensor);
}
//--------------------------------------------------------------------------------
unsigned Pi2GoFull::getLightFL () {
	return pcf8591.readAnalogInput (2);
}
//--------------------------------------------------------------------------------
unsigned Pi2GoFull::getLightFR () {
	return pcf8591.readAnalogInput (1);
}
//--------------------------------------------------------------------------------
unsigned Pi2GoFull::getLightBL () {
	return pcf8591.readAnalogInput (3);
}
//--------------------------------------------------------------------------------
unsigned Pi2GoFull::getLightBR () {
	return pcf8591.readAnalogInput (4);
}
//--------------------------------------------------------------------------------
float timedifference_msec (struct timeval t0, struct timeval t1)
{
    return fabs(t1.tv_sec - t0.tv_sec) * 1000.0f + fabs(t1.tv_usec - t0.tv_usec) / 1000.0f;
}
//--------------------------------------------------------------------------------
float Pi2GoFull::getDistance () {

	struct timeval start, stop, count;
	float elapsed;

	pinMode (SONAR,OUTPUT);
	// Send 10us pulse to trigger
	digitalWrite (SONAR,ON);
	usleep (10);
	digitalWrite (SONAR,OFF);
	pinMode (SONAR,INPUT);

    gettimeofday(&start,NULL);
    count = start;
    while ((digitalRead(SONAR)==OFF) && (timedifference_msec(start,count)<100))
		gettimeofday(&start,NULL);

    gettimeofday(&stop,NULL);
    count = stop;
    while ((digitalRead(SONAR)==ON) && (timedifference_msec(stop,count)<100))
		gettimeofday(&stop,NULL);

    // Calculate pulse length
	elapsed = timedifference_msec(stop,start);

    // Distance pulse travelled in that time is time
    // multiplied by the speed of sound 34000(cm/s) divided by 2
    return elapsed*17;	// 17000/1000
}
//--------------------------------------------------------------------------------
void Pi2GoFull::go (int leftSpeed,int rightSpeed) {

	if ((abs(leftSpeed)>100) || (abs(rightSpeed)>100))
		return;

	Pi2GoFull::leftSpeed = leftSpeed;
	Pi2GoFull::rightSpeed = rightSpeed;

	if (leftSpeed>0) {
		softPwmWrite (LEFT_MOTOR_REVERSE,0);
		softPwmWrite (LEFT_MOTOR_FORWARD,leftSpeed);
	}
	else {
		softPwmWrite (LEFT_MOTOR_FORWARD,0);
		softPwmWrite (LEFT_MOTOR_REVERSE,-1*leftSpeed);
	}

	if (rightSpeed>0) {
		softPwmWrite (RIGHT_MOTOR_REVERSE,0);
		softPwmWrite (RIGHT_MOTOR_FORWARD,rightSpeed);
	}
	else {
		softPwmWrite (RIGHT_MOTOR_FORWARD,0);
		softPwmWrite (RIGHT_MOTOR_REVERSE,-1*rightSpeed);
	}
}
//--------------------------------------------------------------------------------
void Pi2GoFull::go (int speed) {

	leftSpeed = speed;
	rightSpeed = speed;
	go (leftSpeed,rightSpeed);
}
//--------------------------------------------------------------------------------
void Pi2GoFull::stop () {

	leftSpeed = 0;
	rightSpeed = 0;
	go (leftSpeed,rightSpeed);
}
//--------------------------------------------------------------------------------
void Pi2GoFull::turnForward (unsigned leftSpeed,unsigned rightSpeed) {

	Pi2GoFull::leftSpeed = leftSpeed;
	Pi2GoFull::rightSpeed = rightSpeed;
	go (Pi2GoFull::leftSpeed,Pi2GoFull::rightSpeed);
}
//--------------------------------------------------------------------------------
void Pi2GoFull::turnReverse (unsigned leftSpeed,unsigned rightSpeed) {

	Pi2GoFull::leftSpeed = -1*leftSpeed;
	Pi2GoFull::rightSpeed = -1*rightSpeed;
	go (Pi2GoFull::leftSpeed,Pi2GoFull::rightSpeed);
}
//--------------------------------------------------------------------------------
void Pi2GoFull::spinLeft (unsigned speed) {

	leftSpeed = -1*speed;
	rightSpeed = speed;
	go (Pi2GoFull::leftSpeed,Pi2GoFull::rightSpeed);
}
//--------------------------------------------------------------------------------
void Pi2GoFull::spinRight (unsigned speed) {

	leftSpeed = speed;
	rightSpeed = -1*speed;
	go (Pi2GoFull::leftSpeed,Pi2GoFull::rightSpeed);
}
//--------------------------------------------------------------------------------
void Pi2GoFull::forward (unsigned speed) {

	leftSpeed = speed;
	rightSpeed = speed;
	go (speed);
}
//--------------------------------------------------------------------------------
void Pi2GoFull::reverse (unsigned speed) {

	leftSpeed = -1*speed;
	rightSpeed = -1*speed;
	go (-1*speed);
}
//--------------------------------------------------------------------------------
int Pi2GoFull::getLeftSpeed () {

	return leftSpeed;
}
//--------------------------------------------------------------------------------
int Pi2GoFull::getRightSpeed () {

	return rightSpeed;
}
//--------------------------------------------------------------------------------

