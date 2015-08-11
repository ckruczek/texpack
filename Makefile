COMPILER= $(shell which clang)

ifeq ($(COMPILER),)
  COMPILER=$(shell which cc)
  ifeq ($(COMPILER),)
    $(warning Neither clang nor cc is installed)
  endif
endif

INCLUDES=-Isrc/config

CCFLAGS=-g -std=c99 -D_GNU_SOURCE -pedantic -Wall -Wextra $(INCLUDES)
SOURCES=$(shell find src -name '*.c')
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=texpack

debug: CCFLAGS += -DDEBUG
debug: all

cc: COMPILER=cc
cc: all

clang: COMPILER=clang
clang: all

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(COMPILER) -lcurl  $(OBJECTS) -o $@

.c.o:
	$(COMPILER) $(CCFLAGS) -c  $< -o $@

