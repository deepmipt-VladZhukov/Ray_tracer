//
// Created by yury on 07.05.16.
//

#ifndef RAY_TRACING_K_D_TREE_H
#define RAY_TRACING_K_D_TREE_H

#include <cmath>
#include <algorithm>
#include <memory>
#include <sceneobject.h>

struct ray {
    Point start, direction;
    ray(Point start, Point direction): start(start), direction(direction) {};
};

static long double undefined = 1000000;
static long double epsilon = 10E-5;

class k_d_tree {
private:
    static bool cmp_x(std::shared_ptr<SceneObject> first, std::shared_ptr<SceneObject> second);
    static bool cmp_y(std::shared_ptr<SceneObject> first, std::shared_ptr<SceneObject> second);
    static bool cmp_z(std::shared_ptr<SceneObject> first, std::shared_ptr<SceneObject> second);

    struct box {
    public:
        Point min;
        Point max;
        box() = default;
        box(const Point& min_, const Point& max_);
        ~box() = default;
        bool intersects(const ray& r) const;
    private:
        typedef std::pair<long double, long double> segment;
        static void normalize(segment& segm);
    };

    struct node {
        box bounding_box;
        std::shared_ptr<SceneObject> median;
        int axis;
        std::shared_ptr<node> left;
        std::shared_ptr<node> right;
        node(std::vector<std::shared_ptr<SceneObject>>::iterator begin,
             std::vector<std::shared_ptr<SceneObject>>::iterator end,
             int axis_);
        std::shared_ptr<SceneObject> find_closest(const ray& r) const;
    };

    std::shared_ptr<node> root;
public:
    std::pair<Point, std::shared_ptr<SceneObject>> find_closest(const ray& r);
    k_d_tree(std::vector<std::shared_ptr<SceneObject>>& base);
    k_d_tree(){};
    ~k_d_tree() = default;
};


#endif //RAY_TRACING_K_D_TREE_H
