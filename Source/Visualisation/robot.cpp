#include "robot.h"

#include <QString>
#include <iostream>

Robot::Robot(Indices position, CARDINAL_DIRECTION direction, int takenCoins) :
    Quad("robot", position)
{    
    this->direction  = direction;
    this->takenCoins = takenCoins;
}

QString Robot::walk(std::vector<std::vector<Point> >& grid, std::vector<Barrier>& barriers)
{
    int fields = grid.size();
    int i = position.getI();
    int j = position.getJ();
    switch (direction)
    {
    case NORTH:
        if(j + 1 < fields)
        {
            Indices newPosition(i, j + 1);
            if(!collisionDetector(newPosition, barriers))            
                position.incrementJ();            
            else
                return QString("Can't move forward. There's a wall in front of the robot.");
        }
        else        
            return QString("Can't walk outside the environment.");
        break;
    case EAST:        
        if(i + 1 < fields)
        {
            Indices newPosition(i + 1, j);
            if(!collisionDetector(newPosition, barriers))            
                position.incrementI();            
            else            
                return QString("Can't move forward. There's a wall in front of the robot.");
        }        
        else        
            return QString("Can't walk outside the environment.");
        break;
    case SOUTH:        
        if(j - 1 >= 0)
        {
            Indices newPosition(i, j - 1);
            if(!collisionDetector(newPosition, barriers))            
                position.decrementJ();            
            else            
                return QString("Can't move forward. There's a wall in front of the robot.");
        }
        else        
            return QString("Can't walk outside the environment.");
        break;
    case WEST:        
        if(i - 1 >= 0)
        {
            Indices newPosition(i - 1, j);
            if(!collisionDetector(newPosition, barriers))            
                position.decrementI();            
            else            
                return QString("Can't move forward. There's a wall in front of the robot.");
        }
        else        
            return QString("Can't walk outside the environment.");
        break;
    }

    return QString();
}

void Robot::turnLeft()
{
    int dir = (int) direction;
    dir -= 1;
    dir < 0 ? dir = 3 : 0;
    direction = (CARDINAL_DIRECTION) dir;
}

void Robot::turnRight()
{
    int dir = (int) direction;
    dir += 1;
    dir > 3 ? dir = 0 : 3;
    direction = (CARDINAL_DIRECTION) dir;
}

QString Robot::take(std::vector<Coin>& coins)
{    
    for(uint i = 0; i < coins.size(); ++i)
    {
        if(position.equals(coins[i].getPosition()))
        {
            //coins[i].setPosition(Indices(-1, -1));
            coins.erase(coins.begin() + i);
            takenCoins++;
            return QString();
        }
    }
    return QString("There's no coin underneath the robot.");
}

QString Robot::leave(std::vector<Coin>& coins)
{
    if(takenCoins > 0)
    {        
        for(uint i = 0; i < coins.size(); ++i)
        {
            if(position.equals(coins[i].getPosition()))
                return QString("Can't place a coin on top of another.");           
        }
        coins.push_back(Coin(position));
        takenCoins--;
        return QString();
    }
    else
        return QString("The robot doesn't have coins left.");    
}

bool Robot::collisionDetector(Indices& newPosition, std::vector<Barrier>& barriers) {
    for(uint i = 0; i < barriers.size(); ++i)
    {
        std::vector<Quad>& quads = barriers.at(i).getQuads();
        for(uint j = 0; j < quads.size(); ++j)
        {
            if(newPosition.equals(quads.at(j).getPosition()))
            {
                return true;
            }
        }
    }
    return false;
}
