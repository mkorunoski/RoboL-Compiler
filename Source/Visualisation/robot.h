#ifndef ROBOT_H
#define ROBOT_H

#include <vector>

#include "data.h"
#include "quad.h"
#include "coin.h"
#include "barrier.h"

class Robot : public Quad
{    
public:
    Robot() : Quad("robot", Indices(-1, -1)), direction(NORTH), takenCoins(0) { }
    Robot(Indices position, CARDINAL_DIRECTION direction, int takenCoins);

    QString walk(std::vector<std::vector<Point> >& grid, std::vector<Barrier>& barriers);
    void turnLeft();
    void turnRight();
    QString take(std::vector<Coin>& coins);
    QString leave(std::vector<Coin>& coins);
    int getTakenCoins() { return takenCoins; }
    int setTakenCoins(int takenCoins) { this->takenCoins = takenCoins; }

    bool collisionDetector(Indices& newPosition, std::vector<Barrier>& barriers);

private:
    CARDINAL_DIRECTION direction;    
    int takenCoins;
};

#endif // ROBOT_H
