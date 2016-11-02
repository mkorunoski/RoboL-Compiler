#include "tiles.h"

Tiles::Tiles(int fields)
{
    setGrid(fields);
}

void Tiles::draw()
{
    for(int j = 0; j < fields; ++j)
    {
        for(int i = 0; i < fields; ++i)
        {
            tiles[i][j].draw(grid);
        }
    }
}

void Tiles::setGrid(int fields)
{
    this->fields = fields;
    grid.clear();
    grid = std::vector<std::vector<Point> >(fields, std::vector<Point>(fields));

    double D = Quad::D;

    double verticalCountHalf = fields / 2.0 - D / 2.0;
    double horizontalCountHalf = fields / 2.0 - D / 2.0;

    int horizontal = 0;
    for(double j = -horizontalCountHalf * D; j <= horizontalCountHalf * D; j += D, ++horizontal)
    {
        int vertical = 0;
        for(double i = - verticalCountHalf * D; i <= verticalCountHalf * D; i += D, ++vertical)
        {
            grid[vertical][horizontal] = Point(i, j);
        }
    }

    setTiles();
}

void Tiles::setTiles()
{
    tiles.clear();
    tiles = std::vector<std::vector<Quad> >(fields, std::vector<Quad>(fields));

    for(int j = 0; j < fields; ++j)
    {
        for(int i = 0; i < fields; ++i)
        {
            tiles[i][j] = Quad("tile", Indices(i, j));
        }
    }
}


