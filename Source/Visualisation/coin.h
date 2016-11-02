#ifndef COIN_H
#define COIN_H

#include "quad.h"

class Coin : public Quad
{
public:
    Coin() { }
    Coin(Indices position);
};

#endif // COIN_H
