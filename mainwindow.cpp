#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <iostream>

MyRend::MyRend(int windowWidth, int windowHeight): windowWidth(windowWidth), windowHeight(windowHeight)
{
    this->setFixedWidth(windowWidth);
    this->setFixedHeight(windowHeight);
    QPalette palette(MyRend::palette());
    palette.setColor(backgroundRole(), Qt::white);
    setPalette(palette);
}

void MyRend::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::darkGreen);

/*
    int pixel_size = (int)fmin((int) windowWidth / Matrix::get_instance()->getw(),
                          (int) windowHeight / Matrix::get_instance()->geth());
    pixel_size = (int)fmax(1, pixel_size);
*/
    int pixel_size = 1;

//    std::cout << pixel_size << std::endl;
    for (size_t i = 0; i < Matrix::get_instance()->getw(); i++) {
        for (size_t j = 0; j < Matrix::get_instance()->geth(); j++) {
            QRect rectangle(i * pixel_size, j * pixel_size, pixel_size, pixel_size);
            painter.fillRect(rectangle, Matrix::get_instance()->getColorToDraw(i, j));
        }
    }
//    std::cout <<Matrix::get_instance()->getw() << "!!" << Matrix::get_instance()->geth() << std::endl;
//    for (size_t i = 0; i < Matrix::get_instance()->getw(); i++) {
//            for (size_t j = 0; j < Matrix::get_instance()->geth(); j++) {
//                std::cout <<  Matrix::get_instance()->getColor(i, j).blue();
//            }
//            std::cout << "\n";
//    }
//    std::cout.flush();

    painter.setPen(Qt::darkGray);
}

