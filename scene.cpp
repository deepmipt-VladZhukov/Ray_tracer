#include "scene.h"
#include "sphere.h"
#include "surf.h"
#include "triangle.h"
#include "quadrangle.h"
#include "parser.h"
#include <map>

Scene::Scene(/*double width, double height*/)
{
    parser prs = parser();
    size_t id = 0;
    cam.pos = prs.camera;
    disp = display(prs.topleft, prs.bottomleft, prs.topright);
    double sz = fmin(disp.width, disp.height);
    Matrix::get_instance(disp.width, disp.height);//sz, sz);
//    std::cout << "parse" << std::endl;
//    std::cout.flush();
    std::vector<material> mtrlsDiscr = prs.mtrls;
    std::map<std::string, material> get_material;
    for (size_t i = 0; i < mtrlsDiscr.size(); i++) {
        get_material.insert(std::make_pair(mtrlsDiscr[i].name, mtrlsDiscr[i]));
    }
    std::vector<sphere> spDiscr = prs.spheres;
    std::vector<triangle> trDiscr = prs.triangles;
    for (size_t i = 0; i < spDiscr.size(); i++) {
        Sphere* sph = new Sphere(spDiscr[i].o, spDiscr[i].r, id++,  get_material[spDiscr[i].name].color);
        objects.push_back(sph);
    }
    for (size_t i = 0; i < trDiscr.size(); i++) {
        Triangle* tr = new Triangle(trDiscr[i].a, trDiscr[i].b, trDiscr[i].c, id++, get_material[trDiscr[i].name].color);
        objects.push_back(tr);
    }
    std::vector<quadrangle> qrDiscr = prs.quadrangles;
    for (size_t i = 0; i < qrDiscr.size(); i++) {
//        std::cout << qrDiscr[i] << std::endl;
        Quadrangle* qr = new Quadrangle(qrDiscr[i].a, qrDiscr[i].b,
                                        qrDiscr[i].c, qrDiscr[i].d, id++, get_material[qrDiscr[i].name].color);
        objects.push_back(qr);
    }

    for (size_t i = 0; i < objects.size(); i++) {
        to_kd_objcts.push_back(std::move(std::shared_ptr<SceneObject>(objects[i])));
    }
    long double k = prs.distance * prs.distance / prs.power;
    objects_kd = k_d_tree(to_kd_objcts);
    std::vector<light> lightsDiscr = prs.lights;
    for (size_t i = 0; i < lightsDiscr.size(); i++) {
        Light l = Light(lightsDiscr[i].p, lightsDiscr[i].power * k);
        lights.push_back(l);
    }
}
