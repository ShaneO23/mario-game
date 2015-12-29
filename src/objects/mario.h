#ifndef OBJECTS_MARIO_H
#define OBJECTS_MARIO_H

#include "./types.h"

struct Mario : Object {
    Mario() {
        this->X = -10;
        this->Y = 80;
        this->Width = 34;
        this->Height = 34;
    }

    const char *Type() {
        return "mario";
    }
};

#endif
