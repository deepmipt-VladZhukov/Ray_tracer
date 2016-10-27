//#pragma once
#include <iostream>
#include <cmath>
#ifndef GEOM
#define GEOM


class Point {
public:
    double x, y, z;
    Point() {x = 0, y = 0, z = 0;}
    Point(double x, double y, double z): x(x), y(y), z(z) {}
    friend const Point operator+(const Point& left, const Point& right);
    friend const Point operator-(const Point& left, const Point& right);
    friend const Point operator*(const Point& left, const double right);
    friend const Point operator/(const Point& left, const double right);
    friend const bool operator !=(const Point& left, const Point& right);
    friend std::ostream& operator<< (std::ostream &out, const Point &point);
    double len() const{
        return sqrt(x * x + y * y + z * z);
    }
    double dist(Point b) const {
        return (b - *this).len();
    }
};

static Point undefined_Point = Point(-123123, 123123, 12312);

inline const bool operator !=(const Point& left, const Point& right) {
    return left.x != right.x && left.y != right.y && left.z != right.z;
}

inline std::ostream& operator<< (std::ostream &out, const Point &point)
{
    out << "Point(" << point.x << ", " << point.y << ", " << point.z << ")";
    return out;
}

inline const Point operator*(const Point& left, const double right) {
    return Point(left.x * right, left.y * right, left.z * right);
}

inline const Point operator/(const Point& left, const double right) {
    return Point(left.x / right, left.y / right, left.z / right);
}

inline const Point operator+(const Point& left, const Point& right) {
    return Point(left.x + right.x, left.y + right.y, left.z + right.z);
}

inline const Point operator-(const Point& left, const Point& right) {
    return Point(left.x - right.x, left.y - right.y, left.z - right.z);
}

inline double determ(double a, double b, double c, double d, double e, double f, double g, double h, double i) {
    return a * (e*i - f*h) - b * (d*i - f*g) + c * (d*h - e*g);
}

inline double dot(Point a, Point b) {
//    std::cout << a << "*" << b << " = " << a.x * b.x + a.y * b.y + a.z * b.z;
//    std::cout.flush();
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline Point cross(Point a, Point b) {
    return Point(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

struct Plane {
    double a, b, c, d;
    Point pa, pb, pc;
    Plane(Point p1, Point p2, Point p3): pa(p1), pb(p2), pc(p3) {
        a = determ(1, p1.y, p1.z, 1, p2.y, p2.z, 1, p3.y, p3.z);
        b = determ(p1.x, 1, p1.z, p2.x, 1, p2.z, p3.x, 1, p3.z);
        c = determ(p1.x, p1.y, 1, p2.x, p2.y, 1, p3.x, p3.y, 1);
        d = -determ(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z);
    }
};
#endif // GEOM
