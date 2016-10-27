#-------------------------------------------------
#
# Project created by QtCreator 2016-04-22T22:00:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ray_tracing
TEMPLATE = app
CONFIG += c++11
#QMAKE_CXXFLAGS += -std=c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    matrix.cpp \
    sceneobject.cpp \
    sphere.cpp \
    scene.cpp \
    surf.cpp \
    triangle.cpp \
    parser.cpp \
    quadrangle.cpp \
    k_d_tree.cpp

HEADERS  += mainwindow.h \
    matrix.h \
    sceneobject.h \
    sphere.h \
    scene.h \
    surf.h \
    geom.h \
    triangle.h \
    parser.h \
    quadrangle.h \
    k_d_tree.h

FORMS    += mainwindow.ui

DISTFILES += \
    input.rt \
    gnome.rt \
    test.rt
