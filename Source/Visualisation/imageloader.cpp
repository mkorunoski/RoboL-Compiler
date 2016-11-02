#include "imageloader.h"

#include <QtOpenGL>
#include "data.h"

uint ImageLoader::loadImage(QString filename)
{
    QString location = QString("%1/%2/%3").arg(QCoreApplication::applicationDirPath(), "graphics", filename);

    QImage img(location.toStdString().c_str(), "BMP");
    img = QGLWidget::convertToGLFormat(img);    

    uint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width(), img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.bits());

    glBindTexture(GL_TEXTURE_2D, 0);    

    return texture;
}
