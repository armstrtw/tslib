CFLAGS = -Wall -O0 -g -fpic
CXXFLAGS = $(CFLAGS)
LDFLAGS =
CXX      = g++
FXX      = g77


test: ../tseries.hpp ../tseries.data.hpp
	$(CXX) test.cpp -o $@ -I..
	./test