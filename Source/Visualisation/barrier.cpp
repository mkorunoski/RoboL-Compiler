#include "barrier.h"

Barrier::Barrier(DIRECTION direction, int location, int start, int end)
{
    this->direction = direction;
    this->location  = location;
    this->start     = start;
    this->end       = end;

    quads = std::vector<Quad>();
    for(int i = start; i < end; ++i)
    {        
        if(direction == VERTICAL)
        {
            quads.insert(quads.end(), Quad("barrier_v", Indices(i, location)));
        }
        else if(direction == HORIZONTAL)
        {
            quads.insert(quads.end(), Quad("barrier_h", Indices(location, i)));
        }
    }    
}

void Barrier::draw(std::vector<std::vector<Point> >& grid)
{    
    for(uint i = 0; i < quads.size(); ++i)
    {
        quads[i].draw(grid);
    }
}
