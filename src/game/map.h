#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>

// Useful aliases
typedef std::vector<const char *>   TileLine;
typedef std::vector<TileLine>       TileMap;

class Map {
     TileMap tiles;

public:
    Map();
    int Width();
    int Height();
};

#endif
