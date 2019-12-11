#ifndef __BEHAVIORS_HPP__
#define __BEHAVIORS_HPP__

#include "Pi2GoFull.hpp"

class Robot {

	// distances to consider that there is an obstacle and it is clear
	unsigned lowDistance, highDistance;
	// speeds por low and high distances
	unsigned lowDistanceSpeed, highDistanceSpeed;
	// distance read using obstacleDetected()
	float distance;
	unsigned behavior;
	// last avoid moved to the right
	bool lastAvoidMovedRight;
	// movement when searching an obstacle, true if spiral
	bool spiral;
	// speed when moving along
	unsigned speed;
	// how an obstacle was detected
	bool bObstacleDetected;
	bool bObstacleDetectedByDistance;
	// if switch was pressed
	bool switchPressed;
	// formatted time as HH:MM:SS
	char sTime[8];

public:

	enum behaviors { SEARCH_OBSTACLE, AVOID_OBSTACLE, /*MOVE_ALONG,*/ ERROR };
	Pi2GoFull pi2GoFull;

	Robot ();
	void controller ();
	unsigned setBehavior (unsigned behavior);
	void _1_searchObstacle (bool firstCall);
	bool _2_avoidObstacle ();
	// alternate movement when searching an obstacle
	void alternateMovement ();
	// control speed when not moving in spiral
	void controlSpeed (float distance);
	bool obstacleDetected ();
	void notifyStartup ();
	void notifyObstacle ();
	void notifyError ();
	char* getStringTime();
	void obstacleDetectedMessage ();
	void buttonPressedEvent ();
};

#endif
