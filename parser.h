#ifndef PARSER_H
#define PARSER_H
#include "sphere.h"
#include "surf.h"
#include "triangle.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <stdlib.h>

inline std::vector<std::string> get_tokens(std::string sentence) {
    std::istringstream iss(sentence);
    std::vector<std::string> tokens;
    std::copy(std::istream_iterator<std::string>(iss),
              std::istream_iterator<std::string>(),
              std::back_inserter<std::vector<std::string> >(tokens));
    return tokens;
}

inline int getIntByStr(std::string s) {
    return atoi(s.c_str());
}

inline double getDoubleByStr(std::string s) {
    return atof(s.c_str());
}

struct material {
    std::string name;
    QColor color;
    double reflect;
    double refract;
    material(){};
    friend std::ostream& operator<< (std::ostream &out, const material &m);
};

inline std::ostream& operator<< (std::ostream &out, const material &m)
{
    out << "material(" << m.name << ", " << m.color.red() << ", " << m.reflect << ", " << m.refract << ")";
    return out;
}

struct light {
    Point p;
    double power;
    friend std::ostream& operator<< (std::ostream &out, const light &m);
};

inline std::ostream& operator<< (std::ostream &out, const light &l)
{
    out << "light(" << l.p << ", " << l.power;
    return out;
}

struct sphere {
    Point o;
    double r;
    std::string name;
    friend std::ostream& operator<< (std::ostream &out, const sphere &s);
};

inline std::ostream& operator<< (std::ostream &out, const sphere &s)
{
    out << "sphere(" << s.name << ", " << s.o << ", " << s.r;
    return out;
}

struct triangle {
    Point a, b, c;
    std::string name;
    friend std::ostream& operator<< (std::ostream &out, const triangle &m);
};

inline std::ostream& operator<< (std::ostream &out, const triangle &t)
{
    out << "triangle(" << t.name << ", " << t.a << ", " << t.b << ", " << t.c << std::endl;
    return out;
}

struct quadrangle {
    Point a, b, c, d;
    std::string name;
    friend std::ostream& operator<< (std::ostream &out, const triangle &q);
};

inline std::ostream& operator<< (std::ostream &out, const quadrangle &q)
{
    out << "quadrangle(" << q.name << ", " << q.a << ", " << q.b << ", " << q.c << ", " << q.d << std::endl;
    return out;
}


class parser
{
public:
    double power;
    double distance;
    Point camera;
    Point topleft;
    Point bottomleft;
    Point topright;
    std::vector<material> mtrls;
    std::vector<light> lights;
    std::vector<sphere> spheres;
    std::vector<triangle> triangles;
    std::vector<quadrangle> quadrangles;
    parser();
};



#endif // PARSER_H
