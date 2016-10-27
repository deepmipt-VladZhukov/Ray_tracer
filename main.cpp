#include "mainwindow.h"
#include <QApplication>

#include <QtGui>
#include <scene.h>
#include <qdebug.h>
#include <sphere.h>
#include <memory>
#include <QElapsedTimer>

#define matrixInstance Matrix::get_instance()

int main(int argc, char *argv[]) {
//    int* val = new int(1);
//    std::shared_ptr<int> ptr(val);

    QTime myTimer;
    myTimer.start();
    // do something..
    QApplication a(argc, argv);
    Matrix::get_instance(1024, 768);//disp.width, disp.height);//sz, sz);
    MyRend widget(1024, 768);
    Scene scene = Scene();
    std::cout << myTimer.elapsed() << std::endl;
    scene.updateMatrix();
//    std::cout << "sdsf" << std::endl;
    widget.show();
//    widget.show();
    int nMilliseconds = myTimer.elapsed();
    std::cout << nMilliseconds << std::endl;
    std::cout.flush();
    return a.exec();
}
