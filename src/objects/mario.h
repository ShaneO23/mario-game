#ifndef OBJECTS_MARIO_H
#define OBJECTS_MARIO_H

#include "./types.h"

struct Mario : Object {
    Mario() {
        this->X = 0;
        this->Y = 0;
        this->Width = 34;
        this->Height = 34;
    }

    const char *Type() {
        return "mario";
    }

    // Adjust bounding rect for sprite
    Rect BoundingRect() {
        Rect r;
        r.X = this->X+10;
        r.Y = this->Y+4;
        r.Width = 14;
        r.Height = 30;
        return r;
    }
};

#endif


