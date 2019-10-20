SHELL=/bin/sh

CXX=g++
CXXFLAGS=-std=c++11 -g -O0 -pthread
LDLIBS=-lcpprest -lboost_system -lssl -lcrypto

TARGET=taxiid

SOURCES=src/main.cpp
OBJECTS=$(SOURCES:%.cpp=%.o)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $(@) $(<)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(@) $(^) $(LDLIBS)

clean:
	rm -f $(TARGET) $(OBJECTS)
