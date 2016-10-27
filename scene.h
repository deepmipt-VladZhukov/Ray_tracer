#ifndef SCENE_H
#define SCENE_H
#include <sceneobject.h>
#include <matrix.h>
#include <iostream>
#include <QtDebug>
#include <cmath>
#include <limits>
#include <k_d_tree.h>
#define matrixInstance Matrix::get_instance()

struct camera {
    Point pos;
};

struct display {
    Point a, b, c, d;
    double width, height;
    Point dw, dh;
    display() {}
    display(Point topleft, Point bottomleft, Point topright) {
        a = topleft;
        b = topright;
        c = bottomleft + (b - a);
        d = c - (b - a);
        dw = b - a;
        dh = d - a;
        width = dw.len();
        height = dh.len();
    }

//    display(Point a, Point b, Point c):a(a), b(b), c(c) {
//        d = c - (b - a);
//        dw = b - a;
//        dh = d - a;
//    }

    display(double width1, double height1) {
        this->width = width1;
        this->height = height1;
        a = Point(0, 0, 0);
        b = Point(width, 0, 0);
        c = Point(width, height, 0);
        d = Point(0, height, 0);
        d = c - (b - a);
        dw = b - a;
        dh = d - a;
    }
};

struct Light {
    Point pos;
    double intense;
    Light(){}
    Light(Point p, double i): pos(p), intense(i){}
};

class Scene
{
private:
    camera cam;
    display disp;
    std::vector<Light> lights;
    std::vector<SceneObject*> objects;
    std::vector<std::shared_ptr<SceneObject>> to_kd_objcts;
    k_d_tree objects_kd;
    bool is_dark(Point vector, Point start, size_t id, double dist) {
        ray r = ray(start, vector);
        std::pair<Point,std::shared_ptr<SceneObject>> intersect_object = objects_kd.find_closest(r);
//        Point* tmp = new Point();
//        for (size_t i = 0; i < objects.size(); i++) {
//            if (objects[i]->id != id && objects[i]->intersectWithRay(vector, start, tmp)) {
//                Point d = *tmp - start;
//                if (dist > d.len() && dot(d, vector) > 0)
//                    return true;
//            }
//        }
//        return false;
        if (intersect_object.second == nullptr)
            return false;

    }

public:
    void updateMatrix() {
        int cntW = matrixInstance->getw();
        int cntH = matrixInstance->geth();
        double k = disp.width/ (double)disp.height;
        if (k > cntW / (double)cntH)
            cntH = (1/k)*cntW;
        else
            cntW = k * cntH;




        /*

          //WTF CODE
        int cntWOld = cntW;
        int cntHOld = cntH;
//        double k = fmin(disp.width /cntW, disp.height / cntH);
//        cntH *= k;
//        cntW *= k;
//        std::cout << k << "!" << std::endl;
        double k = disp.width / disp.height;
        double podgonianW = 1, podgonianH = 1;
        if (cntW / cntH > k) {
            podgonianW = fmin(1, disp.width / (double)cntW);
            cntW *= podgonianW;
            podgonianH =(podgonianW * cntW) / (k * cntH);
//            std::cout << disp.height << "uu1u" << cntH << std::endl;
            cntH *= podgonianH;
        }
        else {
            podgonianH = fmin(disp.height / (double)cntH, 1);
            cntH *= podgonianH;
            podgonianW = podgonianH * cntH * k  / (double) cntW;
//            std::cout << disp.height << "uu2u" << cntW << std::endl;
            cntW *= podgonianW;
        }
//        std::cout << podgonianW << "rqwe " << podgonianH << std::endl;


//        cntW = (int) (podgonianW * cntW);
//        cntH = (int) (podgonianH * cntH);



        double cf = cntWOld / (double)cntW;
        double cntH_new = cf * cntH;
        if (cntH_new < cntHOld) {
            cntH = cntH_new;
            cntW = cntW * cf;
        }
        cf = cntHOld / (double) cntH;
        double cntW_new = cf * cntW;
        if (cntW_new < cntWOld) {
            cntW = cntW_new;
            cntH = cntH * cf;
        }

*/




        Point dw = disp.dw / cntW;
        Point dh = disp.dh / cntH;
//        std::cout << cntW << " @@ " << cntH << std::endl;
//        std::cout << disp.width << " @@ " << disp.height << std::endl;
//        if(disp.width / disp.height == cntW / cntH)
//            std::cout << "eboooola" << std::endl;
//        Point dw = disp.dw * k / cntW;
//        Point dh = disp.dh * k / cntH;
//        std::cout << dw << "-- " << dh << std::endl;
        std::vector<Point> intr_p;
        std::vector<std::pair<int, int> > mtrxP;
        std::vector<SceneObject*> objects_id;
        for (int i = 0; i < cntW - 1; i++)
            for (int j = 0; j < cntH - 1; j++) {
                Point p = disp.a + dw / 2 + dh / 2 + dw * i + dh * j;
                Point dir = p - cam.pos;
                Point* res = new Point();
                Point tmp_intr_p;
                SceneObject*tmp_objects_id;
                double cur_dist = std::numeric_limits<double>::max();
                /*
                bool intersected = false;
                for (size_t k = 0; k < objects.size(); k++) {
                    if (objects[k]->intersectWithRay(dir, cam.pos, res) &&
                            dot(dir, *res - p) > 0) {
                        intersected = true;

                        double tmp_dist = (*res - cam.pos).len();
                        if (tmp_dist < cur_dist) {
                            matrixInstance->setColor(i, j, objects[k]->color);
                            cur_dist = tmp_dist;
                            tmp_intr_p = *res;
                            tmp_objects_id = objects[k];
                        }
                    }
                }

                if (intersected) {
                    intr_p.push_back(tmp_intr_p);
                    mtrxP.push_back(std::make_pair(i, j));
                    objects_id.push_back(tmp_objects_id);
//                    std::cout << "kokoko" << std::endl;
                }
                */
//                /*
                ray r(cam.pos, dir);
//                std::cout << r.direction << " " << r.start << std::endl;
//                std::cout.flush();
                std::pair<Point,std::shared_ptr<SceneObject>> intersect_object = objects_kd.find_closest(r);
                if (intersect_object.second != nullptr) {
                    intr_p.push_back(intersect_object.first);
                    mtrxP.push_back(std::make_pair(i, j));
                    objects_id.push_back(intersect_object.second.get());
                    matrixInstance->setColor(i, j, objects_id[objects_id.size() - 1]->color);
//                    if (objects_id[objects_id.size() - 1]->color.red() == 75 &&
//                            objects_id[objects_id.size() - 1]->color.green() == 75)
//                                std::cout << "eu" << std::endl;
                }
//                */

                //kekkeke
            }
        for (size_t i = 0; i < lights.size(); i++) {
            for (size_t j = 0; j < intr_p.size(); j++) {
                double dx = lights[i].pos.x - intr_p[j].x;
                double dy = lights[i].pos.y - intr_p[j].y;
                double dz = lights[i].pos.z - intr_p[j].z;
                Point dir = Point(dx, dy, dz);
                double dist = dx * dx + dy * dy + dz * dz;
                double intence = lights[i].intense;
                QColor q = matrixInstance->getColor(mtrxP[j].first, mtrxP[j].second);
                QColor qToDraw = matrixInstance->getColorToDraw(mtrxP[j].first, mtrxP[j].second);
                intence = intence / dist;
                double cos = objects_id[j]->getCosNormal(dir, intr_p[j]);
                if (dot(objects_id[j]->getNormal(intr_p[j]), intr_p[j] - cam.pos) > 0)
                    cos *= -1;
                if (cos < 0)
                    cos = 0;
                intence *= std::abs(cos);
                if (is_dark(dir, intr_p[j], objects_id[j]->id, sqrt(dist))) {
                    intence = 0;
//                    std::cout << "wow" << std::endl;
                }
//                intence = 1;
                double r = qToDraw.red() + q.red() * intence;
                double g = qToDraw.green() + q.green() * intence;
                double b = qToDraw.blue() + q.blue() * intence;
//                std::cout << intence<< std::endl;
                matrixInstance->setColorToDraw(mtrxP[j].first, mtrxP[j].second,
                                QColor(fmin(r, 100), fmin(g, 100), fmin(b, 100), 255));
            }
        }
    }
    Scene();
};

#endif // SCENE_H
