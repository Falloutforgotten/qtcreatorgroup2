#-------------------------------------------------
#
# Project created by QtCreator 2017-03-19T20:57:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qSimulate
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scene.cpp \
    station.cpp

HEADERS  += mainwindow.h \
    scene.h \
    station.h \
    commandstationadd.h \
    commandstationmove.h \
    commandstationdelete.h \
    keymovement.h
