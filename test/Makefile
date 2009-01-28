CFLAGS = -Wall -DGLIBCXX_FORCE_NEW -O0 -g -fpic -I..
CXXFLAGS = $(CFLAGS)
LDFLAGS =
CXX      = g++
FXX      = g77

.PHONY: test

test:
	$(CXX) $(CXXFLAGS) test.cpp -o $@
	./test

clean:
	rm -f ./test
