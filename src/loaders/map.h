#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <string>
#include <vector>

#include "../game/map.h"
#include "../tools/files.h"
#include "../tools/strings.h"

class MapLoader
 {
    std::string prefix;

public:
    MapLoader(const std::string &prefix);
    // Load a specific map
    Map *Load(const std::string &name);
    // List available maps
    std::vector<std::string> List();
};

#endif
