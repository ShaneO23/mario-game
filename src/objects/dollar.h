#ifndef OBJECTS_DOLLAR_H
#define OBJECTS_DOLLAR_H

#include "./types.h"

struct Dollar : Object {
    Dollar() {
        this->Width = 34;
        this->Height = 34;
    }

    const char *Type() {
        return "dollar";
    }

    // Adjust bounding rect for sprite
    Rect BoundingRect() {
        return Rect(
            this->X+7,
            this->Y+7,
            20,
            20
        );
    }
};

#endif
