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

    Sprite Render() {
        return Sprite(
            "bombe",
            this->X+5 + 50*cos(t/50/(2*3.14)),
            this->Y+5 + 50*sin(t/50/(2*3.14)),
            34,
            34
        );
    }

    // Adjust bounding rect for sprite
    Rect BoundingRect() {
        return Rect(
            this->X+10 + 50*cos(t/50/(2*3.14)),
            this->Y+10 + 50*sin(t/50/(2*3.14)),
            20,
            20
        );
    }
};

#endif
