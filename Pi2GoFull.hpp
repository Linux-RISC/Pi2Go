#ifndef __PI2GO_HPP__
#define __PI2GO_HPP__

#include <wiringPi.h>
#include "PCF8591.hpp"
#include "PCA9685.hpp"

class Pi2GoFull {

	// IR sensors
	static const unsigned LEFT_LINE_SENSOR = 1;
	static const unsigned RIGHT_LINE_SENSOR = 3;
	static const unsigned LEFT_IR_OBSTACLE_SENSOR = 0;
	static const unsigned RIGHT_IR_OBSTACLE_SENSOR = 7;
	static const unsigned CENTER_IR_OBSTACLE_SENSOR = 2;

	// Motor pins
	static const unsigned LEFT_MOTOR_FORWARD = 11;
	static const unsigned LEFT_MOTOR_REVERSE = 10;
	static const unsigned RIGHT_MOTOR_FORWARD = 12;
	static const unsigned RIGHT_MOTOR_REVERSE = 13;

	// tact switch
	static const unsigned TACT_SWITCH = 4;

	// sonar
	static const unsigned SONAR = 15;

	// motor speeds
	static int leftSpeed, rightSpeed;

public:
	static const unsigned OFF = LOW;
	static const unsigned ON = HIGH;
	static const unsigned LED_TURN_OFF = HIGH;
	static const unsigned LED_TURN_ON = LOW;

	// front LEDs
	static const unsigned UP_LEFT_LED = 0;
	static const unsigned DOWN_LEFT_LED = 1;
	static const unsigned DOWN_CENTER_LED = 2;
	static const unsigned DOWN_RIGHT_LED = 3;
	static const unsigned UP_RIGHT_LED = 7;

	static PCF8591 pcf8591;
	static PCA9685 pca9685;

	Pi2GoFull ();
	~Pi2GoFull ();

	// to reset GPIO on exit
	static void signal_callback_handler (int signum);
	
	// General functions
	// Initialises GPIO pins, switches motors and LEDs Off, etc
	static void init (bool destructor = false);
	// Sets all motors and LEDs off and sets GPIO to standard values
	static void cleanup ();

	// LED functions
	static void resetAllLEDs ();
	static void setAllLEDsOff ();

	// RGB LED functions
	// Sets the LED specified to required RGB value. 0 >= LED <= 3; 0 <= R,G,B <= 4095
	// 0=left, 1=back, 2=right, 3=front
	static void setRGBLED (unsigned led,unsigned red,unsigned green,unsigned blue);
	// Sets all LEDs to required RGB. 0 <= R,G,B <= 4095
	static void setAllRGBLEDs (unsigned red,unsigned green,unsigned blue);
	static void setRGBLEDRed (unsigned led);
	static void setRGBLEDGreen (unsigned led);
	static void setRGBLEDBlue (unsigned led);
	static void setRGBLEDWhite (unsigned led);
	static void setRGBLEDOff (unsigned led);
	static void setAllRGBLEDsOff ();

	// Switch functions
	// Returns the value of the tact switch: true==pressed
	static bool getSwitch ();

	// IR Sensor Functions
	static bool getLeftIRLineSensor ();
	static bool getRightIRLineSensor ();
	static bool getLeftIRObstacleSensor ();
	static bool getRightIRObstacleSensor ();
	static bool getCentreIRObstacleSensor ();
	static bool getAnyIRObstacleSensor ();

	// UltraSonic functions
	// Returns the distance in cm to the nearest reflecting object. 0 == no object
	static float getDistance ();

	// Light sensor functions
	// 0 <= sensor <= 3
	static int getLight (unsigned sensor);
	static unsigned getLightFL ();
	static unsigned getLightFR ();
	static unsigned getLightBL ();
	static unsigned getLightBR ();

	// Motor functions
	// Stops both motors
	static void stop ();
	// Sets both motors to move forward at speed. 0 <= speed <= 100
	static void forward (unsigned speed);
	// Sets both motors to reverse at speed. 0 <= speed <= 100
	static void reverse (unsigned speed);
	// Sets motors to turn opposite directions at speed. 0 <= speed <= 100
	static void spinLeft (unsigned speed);
	static void spinRight (unsigned speed);
	// Moves forwards in an arc by setting different speeds. 0 <= leftSpeed,rightSpeed <= 100
	static void turnForward (unsigned leftSpeed,unsigned rightSpeed);
	static void turnReverse (unsigned leftSpeed,unsigned rightSpeed);
	// controls motors in both directions independently using different positive/negative speeds. -100<= leftSpeed,rightSpeed <= 100	
	static void go (int leftSpeed,int rightSpeed);
	// controls motors in both directions together with positive/negative speed parameter. -100<= speed <= 100
	static void go (int speed);
	static int getLeftSpeed ();
	static int getRightSpeed ();

	static float difftime_ms (const struct timeval& startTime,const struct timeval& endTime);
	static float difftime_ms_msg (const struct timeval& startTime,const struct timeval& endTime,char *msg);
	static clock_t difftime_ms (clock_t startTime,clock_t endTime);
	static clock_t difftime_ms_msg (clock_t startTime,clock_t endTime,char *msg);
};

#endif
