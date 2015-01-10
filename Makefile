CC=cc
CCFLAGS=-lcurl -Wall
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=texpack

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CCFLAGS) $< -o $@

