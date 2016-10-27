#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <matrix.h>

class MyRend : public QWidget
{
private:
    int windowWidth;
    int windowHeight;
public:
    MyRend(int windowWidth, int windowHeight);

protected:
    void paintEvent(QPaintEvent *);
};

#endif // MAINWINDOW_H
