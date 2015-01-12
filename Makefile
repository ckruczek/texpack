CC=cc
CCFLAGS=-lcurl -std=c99 -pedantic -Wall -Wextra -Werror 
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=texpack

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CCFLAGS) $< -o $@

