#ifndef OBJECTS_TURTLE_H
#define OBJECTS_TURTLE_H

#include "./types.h"

struct Turtle : Object {
    Turtle() {
        this->Width = 34;
        this->Height = 34;
    }

    const char *Type() {
        return "turtle";
    }

    Sprite Render() {
        return Sprite(
            "tortuev",
            this->X+7,
            this->Y+7,
            20,
            20
        );
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
