#include "game.h"
#include "IUTSDL.h"

#include <string.h>

Game::Game(SDL_Renderer *renderer) {
    this->renderer = renderer;

    // Loaders
    this->mapLoader = new MapLoader("./levels/");
    this->textureLoader = new TextureLoader("./images/", this->renderer);

    // Load map
    this->map = this->mapLoader->Load("sample.txt");
}

Game::~Game() {
    delete(this->mapLoader);
    delete(this->textureLoader);
}

void Game::Run() {
    // Are we running ?
    bool running = true;
    // Our target FPS
    int FRAMERATE = 20;
    // Counter of previous ticks
    int prevTicks = SDL_GetTicks();

    this->render();
    while(running) {
        SDL_Event(event);
        while( SDL_PollEvent( &event ) != 0 ) {
            switch(event.type) {
                case SDL_QUIT :
                    running = false;
                    break;
            }
        }

        // Update ticks to compute FPS
        int currentTicks = SDL_GetTicks();
        int deltaTicks = currentTicks - prevTicks;
        prevTicks = currentTicks;

        // Wait if necessary
        if(deltaTicks < 1000/FRAMERATE) {
            SDL_Delay((1000/FRAMERATE) - deltaTicks);
        }

        this->render();
    }
}

void Game::render() {
    SDL_RenderClear(this->renderer);
    this->renderMap(this->map);
    IUTSDL_RefreshScreen(this->renderer);
}

const char *bgTexture(const char *texture);
void Game::renderMap(Map *map) {
    auto cellW = 34;
    auto cellH = 34;

    // Offsets
    int y = 0;
    for(auto &tileLine : map->Tiles()) {
        int x = 0;
        for(const char *tile : tileLine) {
            // Build rect
            SDL_Rect rect;
            rect.x = x * cellW;
            rect.y = y * cellH;
            rect.w = cellW;
            rect.h = cellH;

            // Render BG
            auto bg = bgTexture(tile);
            if(bg != NULL) {
                auto bgT = this->textureLoader->Load(bg);
                SDL_RenderCopy(this->renderer, bgT, NULL, &rect);
            }

            // Load texture
            auto texture = this->textureLoader->Load(std::string(tile));

            // Render
            SDL_RenderCopy(this->renderer, texture, NULL, &rect);

            // Increment x
            x++;
        }
        // Increment y
        y++;
    }
}

const char *bgTexture(const char *texture) {
    if(strcmp(texture, "bridge") == 0) {
        return "water";
    } else if(strcmp(texture, "cannon") == 0) {
        return "background";
    } else if(strcmp(texture, "mario_start") == 0) {
        return "background";
    }

    return NULL;
}
