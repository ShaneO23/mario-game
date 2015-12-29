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

    // Adjust bounding rect for sprite
    Rect BoundingRect() {
        Rect r;
        r.X = this->X+5;
        r.Y = this->Y+5;
        r.Width = 20;
        r.Height = 20;
        return r;
    }
};

#endif
