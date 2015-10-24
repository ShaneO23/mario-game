CC=g++
CFLAGS=-std=c++11 -c -Wall
SDLFLAGS=`sdl2-config --cflags --libs` -framework Cocoa
SOURCES=src/main.cpp src/IUTSDL.cpp src/object.cpp src/bomb.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=mario

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(SDLFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
