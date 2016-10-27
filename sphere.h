#ifndef SPHERE_H
#define SPHERE_H
#include <sceneobject.h>

class Sphere: public SceneObject
{
private:
    double r;
    Point cntr;
public:
    bool intersectWithRay(Point vector, Point vector_start, Point* res);
    double getCosNormal(Point vector, Point vector_start);
    Point getNormal(Point vector_start);
    double center(int i);
    Sphere(size_t id, QColor color);
    Sphere(Point center, double r, size_t id, QColor color);
    long double lower_limit(int i);
    long double upper_limit(int i);
};

#endif // SPHERE_H
