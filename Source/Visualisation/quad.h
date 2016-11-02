#ifndef QUAD_H
#define QUAD_H

#include <vector>
#include <string>
#include <QtGlobal>

#include "data.h"

class Quad
{
public:
    const static double D = 1.0;

    Quad() { }
    Quad(const std::string& fname, Indices position);

    void draw(std::vector<std::vector<Point> >& grid);

    void setPosition(Indices position) { this->position = position; }
    Indices getPosition() { return position; }

protected:
    Indices position;    
    uint texture;
};

#endif // QUAD_H
