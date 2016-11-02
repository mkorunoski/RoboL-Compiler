#-------------------------------------------------
#
# Project created by QtCreator 2016-08-21T14:47:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
qtHaveModule(opengl): QT += opengl

TARGET = RoboL
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    myglwidget.cpp \
    imageloader.cpp \
    robolvisualisationengine.cpp \
    envparser.cpp \
    quad.cpp \
    robot.cpp \
    coin.cpp \
    barrier.cpp \
    tiles.cpp

HEADERS  += mainwindow.h \
    myglwidget.h \
    imageloader.h \
    data.h \
    robolvisualisationengine.h \
    envparser.h \
    quad.h \
    robot.h \
    coin.h \
    barrier.h \
    tiles.h

FORMS    += mainwindow.ui

RESOURCES += \
    MyRes.qrc

OTHER_FILES +=
