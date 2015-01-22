COMPILER= $(shell which clang)

ifeq ($(COMPILER),)
COMPILER=$(shell which cc)
ifeq ($(COMPILER),)
$(warning Neither clang nor cc is installed)
endif
endif

INCLUDES=-Isrc/config

CCFLAGS=-std=c99 -pedantic -Wall -Wextra -Werror $(INCLUDES)
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=texpack

cc: COMPILER=cc
cc: all

clang: COMPILER=clang
clang: all

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(COMPILER) -lcurl  $(OBJECTS) -o $@

.c.o:
	$(COMPILER) $(CCFLAGS) -c  $< -o $@

