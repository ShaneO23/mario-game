#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <map>
#include <string>

#include <SDL2/SDL.h>

class TextureLoader
 {
    std::string prefix;
    SDL_Renderer *renderer;
    std::map<std::string, SDL_Texture*> *cache;

    public:
        TextureLoader(const std::string &prefix, SDL_Renderer *renderer);
        ~TextureLoader();

        SDL_Texture *Load(const std::string &name);
        bool Has(const std::string &name);
    private:
        std::string filename(const std::string &name);
        SDL_Texture *loadFromDisk(const std::string &name);
};

#endif
