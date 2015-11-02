#include "game.h"
#include "IUTSDL.h"

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
    bool running = true;

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

        this->render();
    }
}

void Game::render() {
    this->renderMap(this->map);
    IUTSDL_RefreshScreen(this->renderer);
}

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
