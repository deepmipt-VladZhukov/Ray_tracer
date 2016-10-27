#include "triangle.h"
#include <iostream>

Triangle::Triangle(Point a, Point b, Point c, size_t id, QColor color): Surf(a, b, c, id, color), a(a), b(b), c(c) {
}

bool Triangle::intersectWithRay(Point vector, Point vector_start, Point* res) {
    bool surf_inter = Surf::intersectWithRay(vector, vector_start, res);
    if (!surf_inter)
        return false;
    Point point = *res;
    Point cr1 = cross(point - a, b - a);
    Point cr2 = cross(point - b, c - b);
    Point cr3 = cross(point - c, a - c);
    bool is_one_dir12 = dot(cr1, cr2) > 0;
    bool is_one_dir13 = dot(cr1, cr3) > 0;
    bool is_one_dir23 = dot(cr2, cr3) > 0;
    return is_one_dir12 && is_one_dir13 && is_one_dir23;
}

double Triangle::getCosNormal(Point vector, Point vector_start) {
    return Surf::getCosNormal(vector, vector_start);
}

double Triangle::center(int i) {
    Point cntr = (a + b + c) / 3;
    if (i == 0)
        return cntr.x;
    if (i == 1)
        return cntr.y;
    if (i == 2)
        return cntr.z;
}

long double Triangle::lower_limit(int i) {
    if (i == 0)
        return fmin(a.x, fmin(b.x, c.x));
    if (i == 1)
        return fmin(a.y, fmin(b.y, b.y));
    if (i == 2)
        return fmin(a.z, fmin(b.z, c.z));
}


long double Triangle::upper_limit(int i) {
    if (i == 0)
        return fmax(a.x, fmax(b.x, c.x));
    if (i == 1)
        return fmax(a.y, fmax(b.y, b.y));
    if (i == 2)
        return fmax(a.z, fmax(b.z, c.z));
}

Point Triangle::getNormal(Point vector_start) {
    return Surf::getNormal(vector_start);
}
