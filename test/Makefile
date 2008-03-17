CFLAGS = -Wall -O0 -g -fpic
CXXFLAGS = $(CFLAGS)
LDFLAGS =
CXX      = g++
FXX      = g77

.PHONY: test

test:
	$(CXX) -I.. test.cpp -o $@
	./test

clean:
	rm -f ./test
