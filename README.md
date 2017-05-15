# Pi2Go
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

6. enter wanderer directory and compile robot example:
- cd wanderer
- optional: make

7. run wanderer as root and follow the on screen instructions:
- sudo ./wanderer

8. use wanderer robot to build your own robot program, the robot works according to these rules:
- the robot remains stopped until the switch is pressed
- when moving, the robot will stop if the switch is pressed
- when searching an obstacle:
	- the robot searchs an obstacle moving along or in spiral, randomly left or right
	- the movement alternates between spiral and along every some seconds
	- when moving along, the speed increases if no obstacle is detected near, and is decreased otherwise
- when avoiding an obstacle:
	- if an obstacle is found, the robot tries to avoid it and moves in spiral to the opposite direction of the obstacle found
	- if an obstacle can't be avoided, the robot stops and notifies the problem using PWM LEDs
	- PWM LEDs will show the position of the obstacles found

