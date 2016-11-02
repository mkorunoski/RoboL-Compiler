#include "mainwindow.h"
#include <QApplication>

#include <QtOpenGL>

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle("RoboL");
    w.setFixedSize(w.size());

    w.show();

    return a.exec();
}
