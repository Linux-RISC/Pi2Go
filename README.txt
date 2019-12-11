git@github.com:allamasg/Pi2Go.git
git config --global user.name "allammeasg"
git config --global user.email "alvarollamasg@gmail.com"
/home/usuario/.gitconfig

https://help.github.com/articles/fork-a-repo/
git clone https://github.com/allamasg/Pi2Go
git clone https://github.com/allamasg/Pi2Go

1. install basic development system if it is not installed, for Debian/Ubuntu:
sudo apt-get install build-essential 

2. run make:
make

3. enter examples directory:
cd examples

4. run examples as root:
sudo ./testRGBLEDs

5. enter wanderer directory and compile robot example:
cd wanderer
make

6. run wanderer as root and follow the on screen instructions:
sudo ./wanderer

7. use wanderer robot to build your own robot program, the robot works according to these rules:
- the robot remains stopped until the switch is pressed
- when moving, the robot will stop if the switch is pressed
- when searching an obstacle:
	- the robot searchs an obstacle moving along or in spiral, randomly left or right
	- the movement alternates between spiral and along every some seconds
	- if moving along, the speed increases if no obstacle is detected near, and is decreased otherwise
- when avoiding an obstacle:
	- if an obstacle is found, the robot tries to avoid it and moves in spiral to the opposite direction of the obstacle found
	- if an obstacle can't be avoided, the robot stops and notifies the problem using PWM LEDs
	- PWM LEDs will show the position of the obstacles found

	

