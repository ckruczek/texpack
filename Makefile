COMPILER= $(shell which clang)

ifeq ($(COMPILER),)
COMPILER=$(shell which cc)
ifeq ($(COMPILER),)
$(warning Neither clang nor cc is installed)
endif
endif


CCFLAGS=-lcurl -std=c99 -pedantic -Wall -Wextra -Werror 
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=texpack

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(COMPILER) $(OBJECTS) -o $@

.c.o:
	$(COMPILER) $(CCFLAGS) $< -o $@

