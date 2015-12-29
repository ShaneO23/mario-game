#ifndef OBJECTS_BOMB_H
#define OBJECTS_BOMB_H

#include "./types.h"

struct Bomb : Object {
    Bomb() {
        this->Width = 34;
        this->Height = 34;
    }

    const char *Type() {
        return "bombe";
    }
};

#endif
