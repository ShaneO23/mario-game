#ifndef GAME_H
#define GAME_H

#include <vector>

#include "loaders/map.h"
#include "loaders/texture.h"
#include "objects/mario.h"
#include "objects/bomb.h"

class Game {
    SDL_Renderer            *renderer;
    TextureLoader           *textureLoader;
    MapLoader               *mapLoader;
    Map                     *map;
    std::vector<Object*>    *objects;
    Mario                   *mario;

    public:
    Game(SDL_Renderer *renderer);
    ~Game();
    void Run();

    private:
    void render();
    void renderMap();
    void renderObjects();
};


#endif
