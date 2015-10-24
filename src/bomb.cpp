#include "bomb.h"

Object *MakeBomb(int x, int y) {
    return new Object(x, y, "bombe.bmp");
}
