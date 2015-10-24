#ifndef OBJECT_H
#define OBJECT_H

class Object {
public:
    char *texture;
    int x, y;

    Object(int x, int y, char *texture);
};

#endif
