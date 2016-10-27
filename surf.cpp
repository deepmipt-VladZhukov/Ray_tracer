#include "surf.h"

bool Surf::intersectWithRay(Point vector, Point vector_start, Point* res) {
    Point a = p.pa;
    Point b = p.pb;
    Point c = p.pc;
    Point x = vector_start;
    Point y = vector_start + vector;
    Point n = cross(b - a, c - a);
    // N / |N|
    Point v = a - x;
    double d = dot(n, v);
    Point w = y - x;
    double e = dot(n, w);
    *res =x + w * (d/e);
    if (e != 0 || d == 0)
        return true;
}

Point Surf::getNormal(Point vector_start) {
    Point a = p.pa;
    Point b = p.pb;
    Point c = p.pc;
    Point n = cross(a - b, c - a);
    return n;
}

double Surf::getCosNormal(Point vector, Point vector_start) {
    Point a = p.pa;
    Point b = p.pb;
    Point c = p.pc;
    Point x = vector_start;
    Point y = vector_start + vector;
    Point n = cross(a - b, c - a); //b - a give -norm vector
    return dot(n, vector) / n.len() / vector.len();
}

double Surf::center(int i) {
    return 0;
}

long double Surf::lower_limit(int i) {
    return -1000000;
}

long double Surf::upper_limit(int i) {
    return 1000000;
}

Surf::Surf(Point a, Point b, Point c, size_t id, QColor color): p(a, b, c), SceneObject(id, color) {
}

