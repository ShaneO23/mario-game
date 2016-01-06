#ifndef OBJECTS_PLANT_H
#define OBJECTS_PLANT_H

#include "./types.h"

struct Plant : Object {
    Plant() {
        this->Width = 34;
        this->Height = 34;
    }

    const char *Type() {
        return "plant";
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
