#include "myglwidget.h"

#include <QtOpenGL>
#include <QQueue>

MyGLWidget::MyGLWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::DoubleBuffer), parent)
{
    engine = new RoboLVisualisationEngine(this);    
}

MyGLWidget::~MyGLWidget()
{
    delete(engine);
}


void MyGLWidget::animate(QQueue<COMMANDS> q)
{
    engine->setMoves(q);
    engine->animate();
}

void MyGLWidget::loadEnvironment()
{
    engine->loadEnvironment();
}

void MyGLWidget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_TEXTURE_2D);
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glTranslated(0.0, 0.0, -1.0);

    engine->draw();

    glPopMatrix();
}

void MyGLWidget::resizeGL(int width, int height)
{    
    glViewport(0, 0, width, height);
}

