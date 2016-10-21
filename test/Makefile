CXXFLAGS = -Weffc++ -Wall -std=c++14 -O0 -g -fpic
INC = -I. -I.. -I/usr/include/catch
LIBS = -lstdc++ -lboost_date_time
CXX  = clang++
##CXX  = g++

bin/% : %.cpp
	$(CXX) $(CXXFLAGS) $(INC) $< -o $@ $(LIBS)

all: $(patsubst %.cpp, bin/%, $(wildcard *.cpp))

clean:
	rm -f bin/*
