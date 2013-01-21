#ifndef MATHS_H
#define MATHS_H

typedef struct Point2f{
    float x;
    float y;

    Point2f()
    {
        this->x = 0.0f;
        this->y = 0.0f;
    }

    Point2f(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
}Point2f;

typedef struct Point2i{
    int x;
    int y;

    Point2i()
    {
        this->x = 0;
        this->y = 0;
    }

    Point2i(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
}Point2i;

#endif // MATHS_H
