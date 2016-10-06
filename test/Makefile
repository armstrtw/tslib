##CFLAGS = -Wall --std=c++11 -DGLIBCXX_FORCE_NEW -O0 -g -fpic -I. -I..  -I/usr/include/catch
CXXFLAGS = -Weffc++ -Wall --std=c++11 -O0 -g -fpic
INC = -I. -I.. -I/usr/include/catch
LIBS = -lstdc++ -lboost_date_time
##CXX  = clang++
CXX  = g++

bin/% : %.cpp
	$(CXX) $(CXXFLAGS) $(INC) $< -o $@ $(LIBS)

all: $(patsubst %.cpp, bin/%, $(wildcard *.cpp))

clean:
	rm -f bin/*
