#include "quad.h"

#include <QtOpenGL>
#include "imageloader.h"

Quad::Quad(const std::string& fname, Indices position)
{   
    texture = ImageLoader::loadImage(QString(fname.c_str()));    
    this->position = position;
}

void Quad::draw(std::vector<std::vector<Point> >& grid)
{
    if(position.equals(Indices(-1, -1)))
        return;

    glBindTexture(GL_TEXTURE_2D, texture);

    glPushMatrix();
    int i = position.getI();
    int j = position.getJ();    
    glTranslated(grid[i][j].getX(), grid[i][j].getY(), 0.0);

    double quadSize = D / 2.0;
    glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex4d(-quadSize, -quadSize, 0.0, 1.0);
    glTexCoord2i(1, 0);
    glVertex4d( quadSize, -quadSize, 0.0, 1.0);
    glTexCoord2i(1, 1);
    glVertex4d( quadSize,  quadSize, 0.0, 1.0);
    glTexCoord2i(0, 1);
    glVertex4d(-quadSize,  quadSize, 0.0, 1.0);
    glEnd();

    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
}
