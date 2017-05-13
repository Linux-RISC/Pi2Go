# general definitions
CXX = g++
HDR = *.hpp
CPP = *.cpp
OBJ = *.o

# compiler options
# -Wfatal-errors -fmax-errors=N
CFLAGS = -I.. -Wall
LIBS = -lwiringPi
LOCAL_LIBS = ../libPi2Go.a

# executable files
EXE = wanderer

all : $(EXE)

clean :
	rm *~ $(OBJ) $(EXE)

$(OBJ) : $(CPP) $(HDR)
	$(CXX) -c $(CFLAGS) $(CPP)

$(EXE) : $(OBJ)
	$(CXX) $(LIBS) -o $@ $^ $(LOCAL_LIBS)

