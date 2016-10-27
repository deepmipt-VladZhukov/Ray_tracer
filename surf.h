#ifndef SURF_H
#define SURF_H
#include<sceneobject.h>

class Surf: public SceneObject
{
public:
    Plane p;
    virtual bool intersectWithRay(Point vector, Point vector_start, Point* res);
    virtual double getCosNormal(Point vector, Point vector_start);
    virtual Point getNormal(Point vector_start);
    double center(int i);
    long double lower_limit(int i);
    long double upper_limit(int i);
    Surf();
    Surf(Point a, Point b, Point c, size_t id, QColor color);
};

#endif // SURF_H
