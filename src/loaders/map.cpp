#include "map.h"

#include "../tools/dirs.h"

// Internal funcs
Map *ParseMap(const std::string &data);
const char *CharToTile(char ch);

MapLoader::MapLoader(const std::string &prefix) {
    this->prefix = prefix;
}

std::vector<std::string> MapLoader::List() {
    return DirList(this->prefix);
}

Map *MapLoader::Load(const std::string &name) {
    auto data = FileReadString(this->prefix+name);
    return ParseMap(data);
}

Map *ParseMap(const std::string &data) {
    auto lines = StringLines(data);

    TileMap tiles;
    for(auto &line : lines) {
        TileLine tileLine;
        for(auto &ch : StringChars(line)) {
            tileLine.push_back(CharToTile(ch));
        }
        tiles.push_back(tileLine);
    }

    return new Map(tiles);
}

// Converts a level map's char to it's corresponding texture/object
const char *CharToTile(char ch)
 {
    switch(ch)
    {
        case '.':
            return "background";
        case 'W':
            return "water";
        case 'M':
            return "mur";
        case 'O':
            return "bombe";
        case 'C':
            return "dollar";
        case 'B':
            return "bridge";
        case 'F':
            return "flagpole";
        case 'X':
            return "cannon";
        case 'T':
            return "tortuer";
        case 'G':
            return "tortuev";


    }
    return "background";
}
