# Pi2Go
Pi2Go Home Page
https://4tronix.co.uk/blog/?p=452

4tronix Pi2Go Full robot C++ library and sample programs

You can compile the sources or go to step 4 to run the examples.

1. install basic development system and Wiring Pi if it is not installed, for Raspbian:
- sudo apt-get install build-essential wiringpi

2. delete the current executable files:
- make clean

3. run make to build the current .o and executable files:
- make

4. enter into examples directory:
- cd examples

5. run examples as root:
- sudo ./testRGBLEDs

- testIRSensors: tests the IR sensors, useful to avoid near obstacles
- testLightSensors: tests the front and rear light sensors, use the lantern of your cell phone for this test
- testMotors: flip the robot and run this test and watch how wheels move
- testRGBLEDs: nice RGB test, modifing color and intensity, useful to report states
- testSonar: measures long distances in cm
- testSwitch: tests built-in switch, useful to modify your robot behavior in runtime
- testLEDs: old code, forget it

6. run wanderer as root and follow the on screen instructions:
- sudo ./wanderer

Use wanderer robot to build your own robot program, the robot works according to these rules:
- the robot remains stopped until the switch is pressed
- when moving, the robot will stop if the switch is pressed
- when searching an obstacle:
	- the robot searchs an obstacle moving along or in spiral, randomly left or right
	- the movement alternates between spiral and along every some seconds
	- when moving along, the speed increases if no obstacle is detected near, and is decreased otherwise
- when avoiding an obstacle:
	- if an obstacle is found, the robot tries to avoid it and moves in spiral to the opposite direction of the obstacle found
	- if an obstacle can't be avoided, the robot stops and notifies the problem using PWM LEDs
	- PWM LEDs will show the position of the obstacle found
- watch how it works: https://www.youtube.com/watch?v=p9FWoLJQIz0

7. run PID_distance as root and follow the on screen instructions:
- sudo ./PID_distance 10 0.00001 0.01 20 5 100 1 (avoid parameters to read the help)
- the objective of this robot is to find a front obstacle and keep a fixed distance to the obstacle. Use a folder to make the robot move forward and backward

This robot works according to these rules:
- the programs shows Kp, Ki and Kp parameters sent
- the robot remains stopped until the switch is pressed
- when moving, the robot will stop if the switch is pressed
- the robot remains stopped until the switch is pressed
- the objective of this robot is to find a front obstacle and keep a fixed distance to the obstacle. Use a folder to make the robot move forward and backward
- if a non-front or too near front obstacle is found, the robot stops
- PWM LEDs will show the position of the obstacle found
- watch how it works: https://www.youtube.com/watch?v=07AbvlxQjJk
