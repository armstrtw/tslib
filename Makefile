CFLAGS = -Wall -O0 -g -fpic
CXXFLAGS = $(CFLAGS)
LDFLAGS =
CXX      = g++

SUBDIRS = test

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@



