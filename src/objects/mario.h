#ifndef OBJECTS_MARIO_H
#define OBJECTS_MARIO_H

#include "./types.h"

struct Mario : Object {
    int prevX;
    int prevY;

    Mario() {
        this->X = 0;
        this->Y = -2;
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
        Rect r;
        r.X = this->X+10;
        r.Y = this->Y+4;
        r.Width = 14;
        r.Height = 30;
        return r;
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
        return "mario_start";
    }
};

#endif


