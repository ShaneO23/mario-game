#ifndef OBJECTS_BOMB_H
#define OBJECTS_BOMB_H

#include "./types.h"

struct Bombe : Object {
    Bombe() {
        this->Width = 34;
        this->Height = 34;
    }

    const char *Type() {
        return "bombe";
    }

    // Adjust bounding rect for sprite
    Rect BoundingRect() {
        return Rect(
            this->X+5,
            this->Y+5,
            20,
            20
        );
    }
};

#endif
