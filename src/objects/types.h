#ifndef OBJECTS_TYPES_H
#define OBJECTS_TYPES_H

struct Typed {
    virtual const char *Type() {
        return "unknown";
    }
};

struct Renderable {
    virtual void Render() {
        return;
    }
};

struct Point {
    int X;
    int Y;

    // Move moves a point by a given delta
    void Move(int x, int y) {
        this->X += x;
        this->Y += y;
    }
};

struct Rect : Point {
    int Width;
    int Height;

    // Insersects returns true if both Rectangles intersect
    bool Intersects(const Rect &r) {
        // They intersect if we contain one of it's 4 corners
        return (
            this->Contains(Point{r.X, r.Y}) ||
            this->Contains(Point{r.X+r.Width, r.Y}) ||
            this->Contains(Point{r.X, r.Y+r.Height}) ||
            this->Contains(Point{r.X+r.Width, r.Y+r.Height})
        );
    }

    // Is a sub rectangle contained inside us
    bool Contains(const Rect &r) {
        // A rectangle is contained in another it's upper left and lower right corners are
        return (
            this->Contains(Point{r.X, r.Y}) &&
            this->Contains(Point{r.X+r.Width, r.Y+r.Height})
        );
    }

    // Is a point contained inside us
    bool Contains(Point p) {
        return (
            (this->X <= p.X && p.X <= this->X+this->Width) &&
            (this->Y <= p.Y && p.Y <= this->Y+this->Height)
        );
    }
};

struct Object : Typed, Rect, Renderable {
    // Returns an object's BoundingRect
    // by default this is a copy of it's rectangle
    virtual Rect BoundingRect() {
        return Rect(*(Rect*)(this));
    }
};


#endif
