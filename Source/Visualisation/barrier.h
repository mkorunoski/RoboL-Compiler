#ifndef BARRIER_H
#define BARRIER_H

#include <vector>

#include "quad.h";

class Barrier
{
public:
    Barrier() { }

    Barrier(DIRECTION direction, int location, int start, int end);

    std::vector<Quad>& getQuads() { return quads; }

    void draw(std::vector<std::vector<Point> >& grid);

private:
    std::vector<Quad> quads;

    DIRECTION direction;
    int location;
    int start;
    int end;
};

#endif // BARRIER_H
