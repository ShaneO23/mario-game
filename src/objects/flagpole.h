#ifndef OBJECTS_FLAGPOLE_H
#define OBJECTS_FLAGPOLE_H

#include "./types.h"

struct Flagpole : Object {
    Flagpole() {
        this->Width = 34;
        this->Height = 34;
    }

    const char *Type() {
        return "flagpole";
    }

#endif // FLAGPOLE_H_INCLUDED
