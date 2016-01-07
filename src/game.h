#ifndef GAME_H
#define GAME_H

#include <vector>

#include "loaders/map.h"
#include "loaders/texture.h"

#include "objects/mario.h"
#include "objects/bomb.h"
#include "objects/dollar.h"
#include "objects/plant.h"
#include "objects/turtle.h"
#include "objects/flagpole.h"

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
    int  ticks();
    void render();
    void renderMap();
    void renderObjects();
    void renderObject(Object *obj);
};


#endif
