CC = g++
CXXFLAGS = -pg
SOURCES = ./functions.cpp ./unit.cpp
LIBS = -lpthread

OBJECTS = functions.o unit.o


all: functions run

functions: $(OBJECTS)
	$(CXX) -o $@ $^ $(LIBS)

bin/%.o : %.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

run: functions
	./functions

clean:
	@rm -rf functions $(OBJECTS)

.PHONY: all run clean
