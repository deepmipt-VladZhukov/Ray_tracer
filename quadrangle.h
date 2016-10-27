#ifndef QUADRANGLE_H
#define QUADRANGLE_H
#include<sceneobject.h>
#include <surf.h>


class Quadrangle: public Surf
{
public:
//    Quadrangle();
    Point a, b, c, d;
    bool intersectWithRay(Point vector, Point vector_start, Point* res);
    double getCosNormal(Point vector, Point vector_start);
    Point getNormal(Point vector_start);
    Quadrangle(size_t id, QColor color);
    Quadrangle(Point a, Point b, Point c, Point d, size_t id, QColor color);
    long double lower_limit(int i);
    long double upper_limit(int i);
    double center(int i);
};

#endif // QUADRANGLE_H
