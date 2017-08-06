CXXFLAGS += -O2 -Wall -g -pthread

all: test getTemp

test: RCSwitch.o RcOok.o Sensor.o test.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi

getTemp: RCSwitch.o RcOok.o Sensor.o getTemp.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi

clean:
	$(RM) *.o test getTemp
