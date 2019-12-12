# general definitions
CXX = g++
#HDR = *.hpp
#CPP = *.cpp
#OBJ = *.o

# compiler options
# -Wfatal-errors -fmax-errors=N
FLAGS = -I. -Wall # Makefile's directory
CFLAGS = -I. -c -Wall # Makefile's directory
LIBS = -lwiringPi
LOCAL_LIBS = libPi2Go.a

# library members
OBJ_lib = PCF8591.o PCA9685.o Pi2GoFull.o Robot/Robot.o PID/PID.o

# sample programs
SAMPLES_DIR = examples
SAMPLES = $(SAMPLES_DIR)/testLEDs $(SAMPLES_DIR)/testRGBLEDs $(SAMPLES_DIR)/testLightSensors $(SAMPLES_DIR)/testSwitch $(SAMPLES_DIR)/testSonar $(SAMPLES_DIR)/testIRSensors $(SAMPLES_DIR)/testMotors $(SAMPLES_DIR)/wanderer $(SAMPLES_DIR)/PID_distance

all : libPi2Go.a $(SAMPLES)

clean :
	rm *~ $(OBJ_lib) libPi2Go.a $(SAMPLES)

PCF8591.o : PCF8591.cpp PCF8591.hpp
	$(CXX) $(CFLAGS) PCF8591.cpp

PCA9685.o : PCA9685.cpp PCA9685.hpp
	$(CXX) $(CFLAGS) PCA9685.cpp

Pi2GoFull.o : Pi2GoFull.cpp Pi2GoFull.hpp PCF8591.cpp PCA9685.cpp
	$(CXX) $(CFLAGS) Pi2GoFull.cpp

Robot/Robot.o : Robot/Robot.cpp Robot/Robot.hpp Pi2GoFull.cpp Pi2GoFull.hpp #or Pi2GoFull.o being the Pi2GoFull.o before
	$(CXX) $(CFLAGS) -o Robot/Robot.o Robot/Robot.cpp

PID/PID.o : PID/PID.cpp PID/PID.hpp
	$(CXX) $(CFLAGS) -o PID/PID.o PID/PID.cpp

# build library
libPi2Go.a : $(OBJ_lib)  
	ar rcs $@ $^

# build sample programs
$(SAMPLES_DIR)/testLEDs : $(SAMPLES_DIR)/testLEDs.cpp $(LOCAL_LIBS)
	$(CXX) $(FLAGS) $(LIBS) -o $@ $^ $(LOCAL_LIBS)
$(SAMPLES_DIR)/testRGBLEDs : $(SAMPLES_DIR)/testRGBLEDs.cpp $(LOCAL_LIBS)
	$(CXX) $(FLAGS) $(LIBS) -o $@ $^ $(LOCAL_LIBS)
$(SAMPLES_DIR)/testLightSensors : $(SAMPLES_DIR)/testLightSensors.cpp $(LOCAL_LIBS)
	$(CXX) $(FLAGS) $(LIBS) -o $@ $^ $(LOCAL_LIBS)
$(SAMPLES_DIR)/testSwitch : $(SAMPLES_DIR)/testSwitch.cpp $(LOCAL_LIBS)
	$(CXX) $(FLAGS) $(LIBS) -o $@ $^ $(LOCAL_LIBS)
$(SAMPLES_DIR)/testSonar : $(SAMPLES_DIR)/testSonar.cpp $(LOCAL_LIBS)
	$(CXX) $(FLAGS) $(LIBS) -o $@ $^ $(LOCAL_LIBS)
$(SAMPLES_DIR)/testIRSensors : $(SAMPLES_DIR)/testIRSensors.cpp $(LOCAL_LIBS)
	$(CXX) $(FLAGS) $(LIBS) -o $@ $^ $(LOCAL_LIBS)
$(SAMPLES_DIR)/testMotors : $(SAMPLES_DIR)/testMotors.cpp $(LOCAL_LIBS)
	$(CXX) $(FLAGS) $(LIBS) -o $@ $^ $(LOCAL_LIBS)
$(SAMPLES_DIR)/wanderer : $(SAMPLES_DIR)/wanderer.cpp $(LOCAL_LIBS)
	$(CXX) $(FLAGS) $(LIBS) -I./Robot -o $@ $^ $(LOCAL_LIBS)
$(SAMPLES_DIR)/PID_distance : $(SAMPLES_DIR)/PID_distance.cpp $(LOCAL_LIBS)
	$(CXX) $(FLAGS) $(LIBS) -I./Robot -I./PID -o $@ $^ $(LOCAL_LIBS)
