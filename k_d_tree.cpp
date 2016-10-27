//
// Created by yury on 07.05.16.
//

#include "k_d_tree.h"

k_d_tree::box::box(const Point& min_, const Point& max_)
        : min(min_),
          max(max_) {}

bool k_d_tree::cmp_x(std::shared_ptr<SceneObject> first, std::shared_ptr<SceneObject> second) {
    return first->center(0) < second->center(0);
}

bool k_d_tree::cmp_y(std::shared_ptr<SceneObject> first, std::shared_ptr<SceneObject> second) {
    return first->center(1) < second->center(1);
}

bool k_d_tree::cmp_z(std::shared_ptr<SceneObject> first, std::shared_ptr<SceneObject> second) {
    return first->center(2) < second->center(2);
}

k_d_tree::node::node(std::vector<std::shared_ptr<SceneObject>>::iterator begin,
                     std::vector<std::shared_ptr<SceneObject>>::iterator end,
                     int axis_)
        : axis(axis_) {
    long double x1 = undefined;
    long double y1 = x1;
    long double z1 = x1;
    long double x2 = -undefined;
    long double y2 = x2;
    long double z2 = x2;

    for (auto it = begin; it != end; ++it) {
        x1 = fminl(x1, (*it)->lower_limit(0));
        y1 = fminl(y1, (*it)->lower_limit(1));
        z1 = fminl(z1, (*it)->lower_limit(2));
        x2 = fmaxl(x2, (*it)->upper_limit(0));
        y2 = fmaxl(y2, (*it)->upper_limit(1));
        z2 = fmaxl(z2, (*it)->upper_limit(2));
    }

    bounding_box = box(Point(x1, y1, z1), Point(x2, y2, z2));
    if (axis == 0) {
        std::nth_element(begin, begin + (end - begin) / 2, end, cmp_x);
    }
    if (axis == 1) {
        std::nth_element(begin, begin + (end - begin) / 2, end, cmp_y);
    }
    if (axis == 2) {
        std::nth_element(begin, begin + (end - begin) / 2, end, cmp_z);
    }

    auto mid = begin + (end - begin) / 2;
    median = *mid;
    node* left_ptr = nullptr;
    if (begin != mid) {
        left_ptr = new node(begin, mid, (axis + 1) % 3);
    }
    node* right_ptr = nullptr;
    if (mid + 1 != end) {
        right_ptr = new node(mid + 1, end, (axis + 1) % 3);
    }
    left = std::shared_ptr<node>(left_ptr);
    right = std::shared_ptr<node>(right_ptr);
}

bool k_d_tree::box::intersects(const ray& r) const {
    segment t_x;
    if (fabsl(r.direction.x) < epsilon) {
        t_x.first = -undefined;
        t_x.second = undefined;
    }
    else {
        t_x.first = (min.x - r.start.x) / r.direction.x;
        t_x.second = (max.x - r.start.x) / r.direction.x;
    }
    segment t_y;
    if (fabsl(r.direction.y) < epsilon) {
        t_y.first = -undefined;
        t_y.second = undefined;
    }
    else {
        t_y.first = (min.y - r.start.y) / r.direction.y;
        t_y.second = (max.y - r.start.y) / r.direction.y;
    }
    segment t_z;
    if (fabsl(r.direction.z) < epsilon) {
        t_z.first = -undefined;
        t_z.second = undefined;
    }
    else {
        t_z.first = (min.z - r.start.z) / r.direction.z;
        t_z.second = (max.z - r.start.z) / r.direction.z;
    }
    normalize(t_x);
    normalize(t_y);
    normalize(t_z);
    segment result(fmaxl(t_x.first,
                         fmaxl(t_y.first, t_z.first)),
                   fminl(t_x.second,
                         fminl(t_y.second, t_z.second)));
    return (result.second > -epsilon && result.first <= result.second + epsilon);
}

void k_d_tree::box::normalize(segment& segm) {
    if (segm.first > segm.second) {
        std::swap(segm.first, segm.second);
    }
}

std::shared_ptr<SceneObject> k_d_tree::node::find_closest(const ray& r) const {
    if (! bounding_box.intersects(r)) {
        return std::shared_ptr<SceneObject>(nullptr);
    }
    std::shared_ptr<SceneObject> closest_SceneObject_left(nullptr);
    std::shared_ptr<SceneObject> closest_SceneObject_right(nullptr);
    if (left) {
        closest_SceneObject_left = left->find_closest(r);
    }
    if (right) {
        closest_SceneObject_right = right->find_closest(r);
    }

    Point median_Point = median->first_intersection(r.direction, r.start);
    Point left_Point = undefined_Point;
    Point right_Point = undefined_Point;
    if (closest_SceneObject_left) {
                left_Point = closest_SceneObject_left->first_intersection(r.direction, r.start);
    }
    if (closest_SceneObject_right) {
        right_Point = closest_SceneObject_right->first_intersection(r.direction, r.start);
    }
    int number_closest = 0;
    long double closest_distance = r.start.dist(median_Point);

    if (r.start.dist(left_Point) < closest_distance) {
        number_closest = 1;
        closest_distance = r.start.dist(left_Point);
    }
    if (r.start.dist(right_Point) < closest_distance) {
        number_closest = 2;
    }
    if (number_closest == 0) {
        return median;
    }
    if (number_closest == 1) {
        return closest_SceneObject_left;
    }
    return closest_SceneObject_right;
}

std::pair<Point, std::shared_ptr<SceneObject>> k_d_tree::find_closest(const ray& r) {
    auto candidate = root->find_closest(r);
    if (candidate && candidate->first_intersection(r.direction, r.start) != undefined_Point) {
        return std::make_pair(candidate->first_intersection(r.direction, r.start), candidate);
    }
    else {
        return std::make_pair(undefined_Point, std::shared_ptr<SceneObject>(nullptr));
    }
}

k_d_tree::k_d_tree(std::vector<std::shared_ptr<SceneObject>>& base)
        : root(new node(base.begin(), base.end(), 0)) {}
