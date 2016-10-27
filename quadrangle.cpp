#include "quadrangle.h"

Quadrangle::Quadrangle(Point a, Point b, Point c, Point d, size_t id, QColor color): Surf(a, b, c, id, color), a(a), b(b), c(c), d(d) {
}

bool Quadrangle::intersectWithRay(Point vector, Point vector_start, Point* res) {
    bool surf_inter = Surf::intersectWithRay(vector, vector_start, res);
    if (!surf_inter)
        return false;
    Point point = *res;
    Point cr1 = cross(point - a, b - a);
    Point cr2 = cross(point - b, c - b);
    Point cr3 = cross(point - c, d - c);
    Point cr4 = cross(point - d, a - d);
    bool is_one_dir12 = dot(cr1, cr2) > 0;
    bool is_one_dir23 = dot(cr2, cr3) > 0;
    bool is_one_dir34 = dot(cr3, cr4) > 0;
    bool is_one_dir41 = dot(cr4, cr1) > 0;
    return is_one_dir12 && is_one_dir23 && is_one_dir34 && is_one_dir41;
}

double Quadrangle::getCosNormal(Point vector, Point vector_start) {
    return Surf::getCosNormal(vector, vector_start);
}

Point Quadrangle::getNormal(Point vector_start) {
    return Surf::getNormal(vector_start);
}



long double Quadrangle::lower_limit(int i) {
    if (i == 0)
        return fmin(fmin(a.x, fmin(b.x, c.x)), d.x);
    if (i == 1)
        return fmin(fmin(a.y, fmin(b.y, b.y)), d.y);
    if (i == 2)
        return fmin(fmin(a.z, fmin(b.z, c.z)), d.z);
}


long double Quadrangle::upper_limit(int i) {
    if (i == 0)
        return fmax(fmax(a.x, fmax(b.x, c.x)), c.x);
    if (i == 1)
        return fmax(fmax(a.y, fmax(b.y, b.y)), b.y);
    if (i == 2)
        return fmax(fmax(a.z, fmax(b.z, c.z)), c.z);
}


double Quadrangle::center(int i) {
    Point cntr = (a + b + c + d) / 4;
    if (i == 0)
        return cntr.x;
    if (i == 1)
        return cntr.y;
    if (i == 2)
        return cntr.z;
}
