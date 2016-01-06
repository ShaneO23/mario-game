#ifndef OBJECTS_MARIO_H
#define OBJECTS_MARIO_H

#include "./types.h"

struct Mario : Object {
    int prevX;
    int prevY;

    Mario() {
        this->X = 0;
        this->Y = 0;
        this->prevX = 0;
        this->prevY = 0;
        this->Width = 34;
        this->Height = 34;
    }

    const char *Type() {
        return "mario";
    }

    // Adjust bounding rect for sprite
    Rect BoundingRect() {
        return Rect(
            this->X+10,
            this->Y+4,
            14,
            30
        );
    }

    Sprite Render() {
        return Sprite(
            this->directionalSprite(),
            this->X,
            this->Y,
            this->Width,
            this->Height
        );
    }

    void Move(int x, int y) {
        if(this->X + x < 0) {
            x = 0;
        }
        if(this->Y + y < 0) {
            y = 0;
        }
        if(x == 0 && y == 0) {
            return;
        }

        this->prevX = this->X;
        this->prevY = this->Y;
        Point::Move(x, y);
    }

    const char *directionalSprite() {
        auto dx = this->X - this->prevX;
        auto dy = this->Y - this->prevY;

        if(dx > 0) {
            return "mario-droite";
        } else if(dx < 0) {
            return "mario-gauche";
        } else if(dy > 0) {
            return "mario-bas";
        } else if(dy < 0) {
            return "mario-haut";
        }
        return "mario";
    }
};

#endif


