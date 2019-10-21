SHELL=/bin/sh

CXX=g++
CXXFLAGS=-std=c++11 -g -O0 -pthread
INCLUDES=-I$(PWD)/include
LDLIBS=-lcpprest -lboost_system -lssl -lcrypto

TARGET=taxiid

SOURCES=\
	src/taxii/listener.cpp \
	src/taxii/service.cpp \
	src/taxii/taxii2.cpp \
	src/main.cpp
OBJECTS=$(SOURCES:%.cpp=%.o)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) -o $(@) $(<)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(@) $(^) $(LDLIBS)

clean:
	rm -f $(TARGET) $(OBJECTS)
