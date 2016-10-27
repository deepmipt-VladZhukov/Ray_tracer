#ifndef TRIANGLE_H
#define TRIANGLE_H
#include<sceneobject.h>
#include <surf.h>

class Triangle: public Surf
{
public:
    Point a, b, c;
    bool intersectWithRay(Point vector, Point vector_start, Point* res);
    double getCosNormal(Point vector, Point vector_start);
    Point getNormal(Point vector_start);
    double center(int i);
    long double lower_limit(int i);
    long double upper_limit(int i);
    Triangle(size_t id, QColor color);
    Triangle(Point a, Point b, Point c, size_t id, QColor color);
};

#endif // TRIANGLE_H
