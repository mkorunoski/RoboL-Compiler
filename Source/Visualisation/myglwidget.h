#ifndef MY_GL_WIDGET_H
#define MY_GL_WIDGET_H

#include <QtOpenGL>
#include <QGLWidget>
#include <QQueue>

#include "robolvisualisationengine.h"
#include "data.h"

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);

    ~MyGLWidget();

    void animate(QQueue<COMMANDS> q);

    RoboLVisualisationEngine * getEngine() { return engine; }
    void loadEnvironment();
    bool isEnvironmentLoaded() { return engine->isEnvironmentLoaded(); }

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private:
     RoboLVisualisationEngine *engine;
};

#endif // MY_GL_WIDGET_H
