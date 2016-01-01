CC=g++
CFLAGS=-std=c++11 -c -Wall
SDLFLAGS=`sdl2-config --cflags --libs` -framework Cocoa
SOURCES=src/main.cpp src/IUTSDL.cpp src/game.cpp src/loaders/texture.cpp src/loaders/map.cpp src/tools/dirs.cpp src/tools/strings.cpp src/tools/files.cpp src/game/map.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=mario

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(SDLFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
