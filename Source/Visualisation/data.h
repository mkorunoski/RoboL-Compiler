#ifndef DATA_H
#define DATA_H

enum DIRECTION { VERTICAL = 0, HORIZONTAL };
enum CARDINAL_DIRECTION { NORTH = 0, EAST, SOUTH, WEST };
enum COMMANDS { WALK = 0, TURN_LEFT, TURN_RIGHT, TAKE, LEAVE };

typedef struct Point
{
    double x;
    double y;

    Point() : x(0), y(0) { }
    Point(double x, double y) { this->x = x; this->y = y; }

    double getX() { return x; }
    double getY() { return y; }
}
Point;

typedef struct Indices
{
    int i;
    int j;

    Indices() : i(0), j(0) { }
    Indices(int i, int j) { this->i = i; this->j = j; }

    int getI() { return i; }
    int getJ() { return j; }

    void incrementI() { i++; }
    void incrementJ() { j++; }
    void decrementI() { i--; }
    void decrementJ() { j--; }

    int equals(Indices indices) { return (i == indices.i && j == indices.j); }
}
Indices;

#endif
