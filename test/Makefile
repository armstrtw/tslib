CFLAGS = -Wall -DGLIBCXX_FORCE_NEW -O0 -g -fpic -I.. -I/usr/include/catch
CXXFLAGS = $(CFLAGS)
LDFLAGS =
CXX      = clang++

.PHONY: test

test:
	$(CXX) $(CXXFLAGS) test.cpp -o $@
	./test

clean:
	rm -f ./test
