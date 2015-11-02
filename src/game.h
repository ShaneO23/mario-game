#ifndef GAME_H
#define GAME_H

#include "loaders/map.h"
#include "loaders/texture.h"

class Game {
    SDL_Renderer    *renderer;
    TextureLoader   *textureLoader;
    MapLoader       *mapLoader;
    Map             *map;

    public:
    Game(SDL_Renderer *renderer);
    ~Game();
    void Run();

    private:
    void render();
    void renderMap(Map *map);
};

#endif
