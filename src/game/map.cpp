#include "map.h"

Map::Map(TileMap tiles) {
    this->tiles = tiles;
}

int Map::Height() {
    return this->tiles.size();
}
    
int Map::Width() {
    return this->tiles[0].size();
}

const TileMap &Map::Tiles() {
    return this->tiles;
}
