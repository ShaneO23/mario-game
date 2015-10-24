CC=g++
CFLAGS=-c -Wall
SDLFLAGS=`sdl2-config --cflags --libs` -framework Cocoa
SOURCES=main.cpp IUTSDL.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=mario

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(SDLFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
