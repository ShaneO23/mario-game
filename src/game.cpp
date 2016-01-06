#include <iostream>

#include "game.h"
#include "IUTSDL.h"

#include <math.h>
#include <string.h>

// Local functions
bool isBackgroundTile(const char *tile);
Object *tileToObject(const char *tile);
std::vector<Object *> *loadObjects(Map *map);
const char *bgTexture(const char *texture);
SDL_Rect toSDLRect(Rect r);

typedef enum Direction {
    MOVE_NONE,
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_UP,
    MOVE_DOWN,
} Direction;

Game::Game(SDL_Renderer *renderer) {
    this->renderer = renderer;

    // Loaders
    this->mapLoader = new MapLoader("./levels/");
    this->textureLoader = new TextureLoader("./images/", this->renderer);

    // Load map
    this->map = this->mapLoader->Load("map.txt");

    // Setup mario
    this->mario = new Mario();

    // Setup objects
    this->objects = loadObjects(this->map);
    //this->objects->push_back(mario);
    //this->objects->push_back(new Bombe());
}

Game::~Game() {
    delete(this->mapLoader);
    delete(this->textureLoader);
    delete(this->objects);
}

void Game::Run()
{
    // Are we running ?
    bool running = true;
    // Our target FPS
    int FRAMERATE = 20;
    // Counter of previous ticks
    int prevTicks = this->ticks();

    this->render();
    while(running) {
        // Default direction
        Direction direction = MOVE_NONE;

        // Get events
        SDL_Event(event);
        while( SDL_PollEvent( &event ) != 0 ) {
            switch(event.type)
             {
                case SDL_QUIT :
                    running = false;
                    break;
                case SDL_KEYDOWN :
                    switch(event.key.keysym.sym) {
                    case SDLK_LEFT:
                        direction = MOVE_LEFT;
                        break;
                    case SDLK_RIGHT:
                        direction = MOVE_RIGHT;
                        break;
                    case SDLK_UP:
                        direction = MOVE_UP;
                        break;
                    case SDLK_DOWN:
                        direction = MOVE_DOWN;
                        break;
                    }
            }
        }

        // Update ticks to compute FPS
        int currentTicks = this->ticks();
        int deltaTicks = currentTicks - prevTicks;
        prevTicks = currentTicks;

        // Wait if necessary
        if(deltaTicks < 1000/FRAMERATE)
            {
            SDL_Delay((1000/FRAMERATE) - deltaTicks);
        }

        // Update logic
        auto pi = 3.14159;
        auto t = currentTicks;
        //this->mario->X = 50+50*sin(t/50/(2*pi));
        //this->mario->Y = 80;
        int dx = 0;
        int dy = 0;
        switch(direction) {
            case MOVE_RIGHT:
                dx = 34;
                break;
            case MOVE_LEFT:
                dx = -34;
                break;
            case MOVE_DOWN:
                dy = +34;
                break;
            case MOVE_UP:
                dy = -34;
                break;
        }

        //Object *bombe = this->objects->at(1);
        //bombe->X = 200 + 50*cos(t/50/(2*pi));
        //bombe->Y = 200 + 50*sin(t/50/(2*pi));

        // Move mario
        if(dx != 0 || dy != 0) {
            // Mario's future position
            int x = this->mario->X+dx;
            int y = this->mario->Y+dy;

            // Position in grid
            int cx = x/34;
            int cy = y/34;

            // Get grid tile
            const char *tile;
            if(
                (cx < 0) ||
                (cy < 0) ||
                (cx >= this->map->Width()) ||
                (cy >= this->map->Height())
            ) {
                // out of bounds
                tile = NULL;
            } else {
                tile = this->map->Tiles().at(cy).at(cx);
            }

            // Check if can move
            if(
                tile == NULL ||
                (strcmp(tile, "water") == 0) ||
                (strcmp(tile, "mur") == 0)
            ) {
                // Can't move
            } else {
                this->mario->Move(dx, dy);
            }
        }

        // Detect collisions
        //if *mario
        int i = 0;
        for(auto &obj: *this->objects) {
            auto r1 = this->mario->BoundingRect();
            auto r2 = obj->BoundingRect();

            // Remove objects mario hits
            if(r1.Intersects(r2) || r2.Intersects(r1)) {
                printf("Mario hit %s at %d, %d\n", obj->Type(), obj->X, obj->Y);
                if(strcmp(obj->Type(), "dollar") == 0) {
                    this->mario->Coins += 1;
                    printf("Mario has %d coins\n", this->mario->Coins);
                }
                this->objects->erase(this->objects->begin() + i);
            } else {
                i++;
            }
        }

        // Dump objects
        for(auto &obj: *this->objects) {
            //printf("%s at %d, %d\n", obj->Type(), obj->X, obj->Y);
        }
        //printf("\n");

        // Update objects
        for(auto &obj: *this->objects) {
            obj->Update(t);
        }

        // Render
        this->render();
    }
}

void Game::render()
{
    SDL_RenderClear(this->renderer);
    this->renderMap();
    this->renderObjects();
    IUTSDL_RefreshScreen(this->renderer);
}

std::vector<Object *> *loadObjects(Map *map) {
    auto objects = new std::vector<Object *>();

    auto cellW = 34;
    auto cellH = 34;

    // Offsets
    int y = 0;
    for(auto &tileLine : map->Tiles()) {
        int x = 0;
        for(const char *tile : tileLine) {
            // Calculate position
            int px = x * cellW;
            int py = y * cellH;

            // Increment x
            x++;

            // Resolve object
            auto obj = tileToObject(tile);
            if(obj == NULL) {
                // If not resolved, skip
                continue;
            }

            // Set position
            obj->X = px;
            obj->Y = py;

            printf("Loaded object (%d, %d): %s\n", obj->X, obj->Y, obj->Type());

            // Add object
            objects->push_back(obj);
        }
        // Increment y
        y++;
    }

    return objects;
}

int Game::ticks() {
    return SDL_GetTicks();
}

Object *tileToObject(const char *tile) {
    if(strcmp(tile, "bombe") == 0) {
        return new Bombe();
    } else if(strcmp(tile, "dollar") == 0) {
        return new Dollar();
    } else if(strcmp(tile, "turtle") == 0) {
        return new Turtle();
    }
    return NULL;
}

void Game::renderMap() {
    auto map = this->map;

    auto cellW = 34;
    auto cellH = 34;

    // Offsets
    int y = 0;
    for(auto &tileLine : map->Tiles())
        {
        int x = 0;
        for(const char *tile : tileLine)
         {
            // Build rect
            SDL_Rect rect;
            rect.x = x * cellW;
            rect.y = y * cellH;
            rect.w = cellW;
            rect.h = cellH;

            // Increment x
            x++;

            // Render BG
            auto bg = bgTexture(tile);
            if(bg != NULL) {
                auto bgT = this->textureLoader->Load(bg);
                SDL_RenderCopy(this->renderer, bgT, NULL, &rect);
            }

            // Skip non background tiles
            if(!isBackgroundTile(tile)) {
                continue;
            }

            // Load texture
            auto texture = this->textureLoader->Load(std::string(tile));

            // Render
            SDL_RenderCopy(this->renderer, texture, NULL, &rect);
        }
        // Increment y
        y++;
    }
}

void Game::renderObjects() {
    for(auto &obj : *this->objects) {
        this->renderObject(obj);
    }
    this->renderObject(this->mario);
}

void Game::renderObject(Object *obj) {
    // Get object's sprite
    auto sprite = obj->Render();

    // Get sprite's rectangle
    auto rect = toSDLRect(sprite);

    // Load texture
    auto texture = this->textureLoader->Load(std::string(sprite.Name));

    // Render
    SDL_RenderCopy(this->renderer, texture, NULL, &rect);
    // Debug render
    if(true) {
        auto boundingRect = toSDLRect(obj->BoundingRect());
        SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRect(this->renderer, &boundingRect);
    }
}

bool isBackgroundTile(const char *tile) {
    if(
        (strcmp(tile, "mur") == 0)        ||
        (strcmp(tile, "water") == 0)      ||
        (strcmp(tile, "bridge") == 0)     ||
        (strcmp(tile, "background") == 0)
    ) {
        return true;
    }
    return false;
}

SDL_Rect toSDLRect(Rect r) {
    SDL_Rect rect;
    rect.x = r.X;
    rect.y = r.Y;
    rect.w = r.Width;
    rect.h = r.Height;
    return rect;
}

const char *bgTexture(const char *texture) {
    if(strcmp(texture, "bridge") == 0) {
        return "water";
    }

    return "background";
}
