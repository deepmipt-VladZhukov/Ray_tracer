#include "matrix.h"
//Color::Color(int r, int g, int b):r(r), g(g), b(b) {}
//Color::Color(): r(0), g(0), b(0) {}

Matrix* Matrix::instance = 0;

const std::vector<std::vector<QColor> >& Matrix::get_mtrx() {
    return Matrix::mtrx;
}

size_t Matrix::getw() {
    return w;
}

size_t Matrix::geth() {
    return h;
}

Matrix::Matrix(size_t w, size_t h)
{
    this->w = w;
    this->h = h;
    mtrx = std::vector<std::vector<QColor> >(w);
    toDraw = std::vector<std::vector<QColor> >(w);
    for (size_t i = 0; i < w; i++) {
        mtrx[i] = std::vector<QColor>(h, QColor(0, 0, 0));
        toDraw[i] = std::vector<QColor>(h, QColor(0, 0, 0));
    }
}
