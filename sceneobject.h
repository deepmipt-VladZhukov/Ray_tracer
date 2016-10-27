#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <QtGui>
#include <geom.h>
class SceneObject
{
public:
    QColor color;
    size_t id;
    virtual bool intersectWithRay(Point vector, Point vector_start, Point* res) = 0;
    virtual double getCosNormal(Point vector, Point vector_start) = 0;
    virtual Point getNormal(Point vector_start) = 0;
    virtual double center(int i) = 0;
    virtual long double lower_limit(int i) = 0;
    virtual long double upper_limit(int i) = 0;
    Point first_intersection(Point vector, Point vector_start) {
        Point* tmp = new Point();
        bool intersect = intersectWithRay(vector, vector_start, tmp);
        Point res = Point(tmp->x, tmp->y, tmp->z);
        if (!intersect)
            return undefined_Point;
        return res;
    }

    SceneObject(size_t id, QColor color);
};

#endif // SCENEOBJECT_H
