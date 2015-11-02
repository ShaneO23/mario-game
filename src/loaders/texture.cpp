#include "texture.h"
#include "../IUTSDL.h"
#include <SDL2/SDL.h>

using namespace std;

TextureLoader::TextureLoader(const string &prefix, SDL_Renderer *renderer) {
    this->prefix = string(prefix);
    this->renderer = renderer;
    this->cache = new map<string, SDL_Texture*>();
}

TextureLoader::~TextureLoader() {
    // Free textures in cache
    for(auto it=this->cache->begin(); it != this->cache->end(); it++) {
        SDL_DestroyTexture(it->second);
    }
    // Free cache
    delete(this->cache);
}

SDL_Texture *TextureLoader::Load(const string &name) {
    // In cache
    if(this->Has(name)) {
        return this->cache->at(name);
    }

    // Load
    auto texture = this->loadFromDisk(name);
    // Set cache
    this->cache->insert(pair<string, SDL_Texture*>(name, texture));
    // Return
    return this->cache->at(name);
}

string TextureLoader::filename(const string &name) {
    return this->prefix + name + ".bmp";
}

SDL_Texture *TextureLoader::loadFromDisk(const string &name) {
    return IUTSDL_LoadTexture(this->renderer, this->filename(name).c_str() ,0xFF,0xFF,0xFF);
}

bool TextureLoader::Has(const string &name) {
    return this->cache->count(name) > 0;
}

