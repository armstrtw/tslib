CFLAGS = -Wall -O0 -g -fpic
CXXFLAGS = $(CFLAGS)
LDFLAGS =
CXX      = g++
FXX      = g77


test:
	cd ./test; make


