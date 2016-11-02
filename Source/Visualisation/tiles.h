#ifndef GRID_H
#define GRID_H

#include <vector>

#include "quad.h"
#include "data.h"

class Tiles
{
public:
    Tiles() : fields(0) { setGrid(fields); }
    Tiles(int fields);

    void draw();

    int getNumFields() { return fields; }
    void setGrid(int fields);
    std::vector<std::vector<Point> >& getGrid() { return grid; }
    void setTiles();

private:
    int fields;    
    std::vector<std::vector<Point> > grid;

    std::vector<std::vector<Quad> > tiles;
};

#endif // GRID_H
