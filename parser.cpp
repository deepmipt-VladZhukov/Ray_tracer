#include "parser.h"



parser::parser()
{
    std::fstream in("/Users/vlad/ray_tracing/gnome.rt");//Тут нужен полный путь до файла!!!
    std::string s;
    int state = 0;
    power = 1;
    distance = 1;
//    std::cout << getDoubleByStr("123.321") << std::endl;
//    std::cout.flush();
    while (in) {
        getline(in, s);
        std::vector<std::string> tst = get_tokens(s);
        for (size_t i = 0; i < tst.size(); i++) {
            if (tst[i][0] == '#')
                break;
            if (state == 0) {
                if (tst[i] == "viewport") {
                    state = 1;
                    break;
                }
                if (tst[i] == "materials") {
                    state = 2;
                    break;
                }
                if (tst[i] == "lights") {
                    state = 4;
                    break;
                }
                if (tst[i] == "geometry") {
//                    std::cout << "kikakjkrkeajlr" << std::endl;
                    state = 7;
                    break;
                }
            }
            if (state == 1) {
                if (tst[i] == "origin") {
                    i++;
                    double orX = getDoubleByStr(tst[i]);
                    i++;
                    double orY = getDoubleByStr(tst[i]);
                    i++;
                    double orZ = getDoubleByStr(tst[i]);
                    camera = Point(orX, orY, orZ);
                    break;
                }
                if (tst[i] == "topleft") {
                    i++;
                    double x = getDoubleByStr(tst[i]);
                    i++;
                    double y = getDoubleByStr(tst[i]);
                    i++;
                    double z = getDoubleByStr(tst[i]);
                    topleft = Point(x, y, z);
                    break;
                }
                if (tst[i] == "bottomleft") {
                    i++;
                    double x = getDoubleByStr(tst[i]);
                    i++;
                    double y = getDoubleByStr(tst[i]);
                    i++;
                    double z = getDoubleByStr(tst[i]);
                    bottomleft = Point(x, y, z);
                    break;
                }
                if (tst[i] == "topright") {
                    i++;
                    double x = getDoubleByStr(tst[i]);
                    i++;
                    double y = getDoubleByStr(tst[i]);
                    i++;
                    double z = getDoubleByStr(tst[i]);
                    topright = Point(x, y, z);
                    break;
                }
                if (tst[i] == "endviewport") {
                    state = 0;
                    break;
                }
            }
            if (state == 2) { // material
                if (tst[i] == "entry") {
                    mtrls.push_back(material());
                    state = 3;
                    break;
                }
                if (tst[i] == "endmaterials") {
                    state = 0;
                    break;
                }
            }
            if (state == 3) { //material entry
                if (tst[i] == "name") {
                    i++;
                    mtrls[mtrls.size() - 1].name = tst[i];
                    break;
                }
                if (tst[i] == "color") {
                    i++;
                    double r = getIntByStr(tst[i]);
                    i++;
                    double g = getIntByStr(tst[i]);
                    i++;
                    double b = getIntByStr(tst[i]);
                    mtrls[mtrls.size() - 1].color = QColor(r, g, b);
                    break;
                }
                if (tst[i] == "reflect") {
                    i++;
                    mtrls[mtrls.size() - 1].reflect = getDoubleByStr(tst[i]);
                    break;
                }
                if (tst[i] == "refract") {
                    i++;
                    mtrls[mtrls.size() - 1].refract = getDoubleByStr(tst[i]);
                    break;
                }
                if (tst[i] == "endentry") {
                    state = 2;
                    break;
                }
            }
            if (state == 4) {
                if (tst[i] == "reference") {
                    state = 5;
                    break;
                }
                if (tst[i] == "point") {
                    lights.push_back(light());
                    state = 6;
                    break;
                }
                if (tst[i] == "endlights") {
//                    std::cout << "endLights" << std::endl;
                    state = 0;
                    break;
                }
            }
            if (state == 5) {
                if (tst[i] == "power") {
                    i++;
                    power = getDoubleByStr(tst[i]);
                    break;
                }
                if (tst[i] == "distance") {
                    i++;
                    distance = getDoubleByStr(tst[i]);
                    break;
                }
                if (tst[i] == "endreference") {
                    state = 4;
                    break;
                }
            }
            if (state == 6) {
                if (tst[i] == "coords") {
                    i++;
                    double x = getDoubleByStr(tst[i]);
                    i++;
                    double y = getDoubleByStr(tst[i]);
                    i++;
                    double z = getDoubleByStr(tst[i]);
                    light& l = lights[lights.size() - 1];
                    l.p.x = x;
                    l.p.y = y;
                    l.p.z = z;
                    break;
                }
                if (tst[i] == "power") {
                    i++;
                    lights[lights.size() - 1].power = getDoubleByStr(tst[i]);
                    break;
                }
                if (tst[i] == "endpoint") {
//                    std::cout << "koko" << std::endl;
                    state = 4;
                    break;
                }
            }
            if (state == 7) {
                if (tst[i] == "sphere") {
                    state = 8;
//                    std::cout << "spher" << std::endl;
                    spheres.push_back(sphere());
                    break;
                }
                if (tst[i] == "triangle") {
                    state = 9;
                    triangles.push_back(triangle());
                    break;
                }
                if (tst[i] == "quadrangle") {
                    state = 10;
                    quadrangles.push_back(quadrangle());
                    break;
                }
                if (tst[i] == "endgeometry") {
                    state = 0;
                    break;
                }
            }
            if (state == 8) {
//                std::cout << "ya tyt" << std::endl;
                if (tst[i] == "coords"){
                    double x, y, z;
                    i++;
                    x = getDoubleByStr(tst[i]);
                    i++;
                    y = getDoubleByStr(tst[i]);
                    i++;
                    z = getDoubleByStr(tst[i]);
                    spheres[spheres.size() - 1].o = Point(x, y, z);
                    break;
                }
                if (tst[i] == "radius") {
                    i++;
                    spheres[spheres.size() - 1].r = getDoubleByStr(tst[i]);
                    break;
                }
                if (tst[i] == "material") {
                    i++;
                    spheres[spheres.size() - 1].name = tst[i];
                    break;
                }
                if (tst[i] == "endsphere")
                {
                    state = 7;
                    break;
                }
            }
            if (state == 9) {
                if (tst[i] == "vertex") {
                    double x, y, z;
                    triangle& tr = triangles[triangles.size() - 1];
                    x = getDoubleByStr(tst[i + 1]);
                    y = getDoubleByStr(tst[i + 2]);
                    z = getDoubleByStr(tst[i + 3]);
                    tr.a = Point(x, y, z);
//                    std::cout << tr.a << std::endl;
                    getline(in, s);
                    std::vector<std::string> tst = get_tokens(s);
                    x = getDoubleByStr(tst[i + 1]);
                    y = getDoubleByStr(tst[i + 2]);
                    z = getDoubleByStr(tst[i + 3]);
                    tr.b = Point(x, y, z);
                    getline(in, s);
                    tst = get_tokens(s);
                    x = getDoubleByStr(tst[i + 1]);
                    y = getDoubleByStr(tst[i + 2]);
                    z = getDoubleByStr(tst[i + 3]);
                    tr.c = Point(x, y, z);
                }
                if (tst[i] == "material")
                    triangles[triangles.size() - 1].name = tst[++i];
                if (tst[i] == "endtriangle")
                    state = 7;
            }
            if (state == 10) {
                if (tst[i] == "vertex") {
                    double x, y, z;
                    quadrangle& qr = quadrangles[quadrangles.size() - 1];
                    x = getDoubleByStr(tst[i + 1]);
                    y = getDoubleByStr(tst[i + 2]);
                    z = getDoubleByStr(tst[i + 3]);
                    qr.a = Point(x, y, z);
                    getline(in, s);
                    std::vector<std::string> tst = get_tokens(s);
                    x = getDoubleByStr(tst[i + 1]);
                    y = getDoubleByStr(tst[i + 2]);
                    z = getDoubleByStr(tst[i + 3]);
                    qr.b = Point(x, y, z);
                    getline(in, s);
                    tst = get_tokens(s);
                    x = getDoubleByStr(tst[i + 1]);
                    y = getDoubleByStr(tst[i + 2]);
                    z = getDoubleByStr(tst[i + 3]);
                    qr.c = Point(x, y, z);
                    getline(in, s);
                    tst = get_tokens(s);
                    x = getDoubleByStr(tst[i + 1]);
                    y = getDoubleByStr(tst[i + 2]);
                    z = getDoubleByStr(tst[i + 3]);
                    qr.d = Point(x, y, z);
                }
                if (tst[i] == "material") {
                    quadrangles[quadrangles.size()  -  1].name = tst[++i];
                }
                if (tst[i] == "endquadrangle")
                    state = 7;
            }
        }
    }
    std::cout << "poweeer" << power << " dist "<< distance << std::endl;
//    std::cout << "cam" << camera << std::endl;
//    std::cout << topleft << " " << bottomleft << " " << topright << std::endl;
//    for (size_t i = 0; i < mtrls.size(); i++)
//        std::cout << mtrls[i] << std::endl;
//    for (size_t i = 0; i < lights.size(); i++)
//        std::cout << lights[i] << std::endl;
//    for (size_t i = 0; i < spheres.size(); i++)
//        std::cout << spheres[i] << std::endl;
//    for (size_t i = 0; i < triangles.size(); i++)
//        std::cout << triangles[i] << std::endl;
//    for (size_t i = 0; i < quadrangles.size(); i++)
//        std::cout << quadrangles[i] << std::endl;
    std::cout.flush();
}

