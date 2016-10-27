#include "sphere.h"
#include <iostream>
Sphere::Sphere(size_t id, QColor color): SceneObject(id, color){}
Sphere::Sphere(Point cntr, double r, size_t id1, QColor color): r(r), cntr(cntr), SceneObject(id1, color){
}

double Sphere::getCosNormal(Point vector, Point vector_start) {
    vector_start.x -= cntr.x;
    vector_start.y -= cntr.y;
    vector_start.z -= cntr.z;
    double res = vector.x * vector_start.x + vector.y * vector_start.y + vector.z * vector_start.z;
//    std::cout << res / vector.len() / vector_start.len() << " " << std::endl;
//    std::cout.flush();
    return res / vector.len() / vector_start.len();
}

Point Sphere::getNormal(Point vector_start) {
    vector_start.x -= cntr.x;
    vector_start.y -= cntr.y;
    vector_start.z -= cntr.z;
    return vector_start;
}

double Sphere::center(int i) {
    if (i == 0)
        return cntr.x;
    if (i == 1)
        return cntr.y;
    if (i == 2)
        return cntr.z;
}

long double Sphere::lower_limit(int i) {
    if (i == 0)
        return cntr.x - r;
    if (i == 1)
        return cntr.y - r;
    if (i == 2)
        return cntr.z - r;
}

long double Sphere::upper_limit(int i) {
    if (i == 0)
        return cntr.x + r;
    if (i == 1)
        return cntr.y + r;
    if (i == 2)
        return cntr.z + r;
}

bool Sphere::intersectWithRay(Point vector, Point vector_start, Point* res) {
//    std::cout << vector.x << " " << vector.y << "--" << vector_start.x << " " << vector_start.y << std::endl;
//    std::cout.flush()cout;
    double a = vector.x * vector.x
                        + vector.y * vector.y
                        + vector.z * vector.z;

    double b = 2 * (vector.x * (vector_start.x - cntr.x)
                             + vector.y * (vector_start.y - cntr.y)
                             + vector.z * (vector_start.z - cntr.z));

    double c = cntr.x * cntr.x
                        + cntr.y * cntr.y
                        + cntr.z * cntr.z
                        + vector_start.x * vector_start.x
                        + vector_start.y * vector_start.y
                        + vector_start.z * vector_start.z
                        - 2 * (vector_start.x * cntr.x
                               + vector_start.y * cntr.y
                               + vector_start.z * cntr.z)
                        - r * r;

        double D = b * b - 4 * a * c;

        if(D < 0)
            return false;
        double EPSILON = 10E-5;
        double sqrt_D = sqrt(D);
        double a_2 = 2 * a;

        double t1 = (-b + sqrt_D) / a_2;
        double t2 = (-b - sqrt_D) / a_2;

        double min_t = (t1 < t2) ? t1 : t2;
        double max_t = (t1 > t2) ? t1 : t2;

        double t = (min_t > EPSILON) ? min_t : max_t;

        if(t < EPSILON)
            return false;

        res->x = vector_start.x + t * vector.x;
        res->y = vector_start.y + t * vector.y;
        res->z = vector_start.z + t * vector.z;
        return true;
}
