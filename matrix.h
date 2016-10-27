#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <QtGui>

class Matrix
{
private:
    static Matrix* instance;
    size_t w, h;
    std::vector<std::vector<QColor> > mtrx;
    std::vector<std::vector<QColor> > toDraw;
    Matrix() {}
    Matrix(size_t w, size_t h);
    Matrix( const Matrix& );
    Matrix& operator=( Matrix& );
public:
    static Matrix* get_instance(size_t w, size_t h) {
        if (!instance)
            instance = new Matrix(w, h);
        return instance;
    }
    static Matrix* get_instance() {
        if (!instance)
            instance = new Matrix();
        return instance;
    }

    size_t getw();
    size_t geth();
    void setColor(size_t i, size_t j, QColor q) {
        mtrx[i][j] = q;
    }

    QColor getColor(size_t i, size_t j){
        return mtrx[i][j];
    }

    void setColorToDraw(size_t i, size_t j, QColor q) {
        toDraw[i][j] = q;
    }

    QColor getColorToDraw(size_t i, size_t j) {
        return toDraw[i][j];
    }

    const std::vector<std::vector<QColor> >& get_mtrx();
};

#endif //MATRIX_H
