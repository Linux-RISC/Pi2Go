# general definitions
CXX = g++
#HDR = *.hpp
#CPP = *.cpp
#OBJ = *.o

# compiler options
# -Wfatal-errors -fmax-errors=N
FLAGS = -I. -Wall
CFLAGS = -c -Wall
LIBS = -lwiringPi
LOCAL_LIBS = libPi2Go.a

# library members
OBJ_lib = PCF8591.o PCA9685.o Pi2GoFull.o

# sample programs
SAMPLES_DIR = examples
SAMPLES = $(SAMPLES_DIR)/testLEDs $(SAMPLES_DIR)/testRGBLEDs $(SAMPLES_DIR)/testLightSensors $(SAMPLES_DIR)/testSwitch $(SAMPLES_DIR)/testSonar $(SAMPLES_DIR)/testIRSensors $(SAMPLES_DIR)/testMotors

all : libPi2Go.a $(SAMPLES)

clean :
	rm *~ $(OBJ_lib) libPi2Go.a $(SAMPLES)

# build library
libPi2Go.a : $(OBJ_lib)  
	ar rcs $@ $^

PCF8591.o : PCF8591.cpp PCF8591.hpp
	$(CXX) $(CFLAGS) PCF8591.cpp

PCA9685.o : PCA9685.cpp PCA9685.hpp
	$(CXX) $(CFLAGS) PCA9685.cpp

Pi2GoFull.o : Pi2GoFull.cpp Pi2GoFull.hpp PCF8591.cpp PCA9685.cpp
	$(CXX) $(CFLAGS) Pi2GoFull.cpp

# build sample programs
$(SAMPLES_DIR)/testLEDs : $(SAMPLES_DIR)/testLEDs.cpp
	$(CXX) $(FLAGS) $(LIBS) -o $@ $^ $(LOCAL_LIBS)
$(SAMPLES_DIR)/testRGBLEDs : $(SAMPLES_DIR)/testRGBLEDs.cpp
	$(CXX) $(FLAGS) $(LIBS) -o $@ $^ $(LOCAL_LIBS)
$(SAMPLES_DIR)/testLightSensors : $(SAMPLES_DIR)/testLightSensors.cpp
	$(CXX) $(FLAGS) $(LIBS) -o $@ $^ $(LOCAL_LIBS)
$(SAMPLES_DIR)/testSwitch : $(SAMPLES_DIR)/testSwitch.cpp
	$(CXX) $(FLAGS) $(LIBS) -o $@ $^ $(LOCAL_LIBS)
$(SAMPLES_DIR)/testSonar : $(SAMPLES_DIR)/testSonar.cpp
	$(CXX) $(FLAGS) $(LIBS) -o $@ $^ $(LOCAL_LIBS)
$(SAMPLES_DIR)/testIRSensors : $(SAMPLES_DIR)/testIRSensors.cpp
	$(CXX) $(FLAGS) $(LIBS) -o $@ $^ $(LOCAL_LIBS)
$(SAMPLES_DIR)/testMotors : $(SAMPLES_DIR)/testMotors.cpp
	$(CXX) $(FLAGS) $(LIBS) -o $@ $^ $(LOCAL_LIBS)



