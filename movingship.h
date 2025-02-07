#ifndef MOVINGSHIP_H
#define MOVINGSHIP_H

#include <random>
#include <iostream>

using namespace std;

class MovingShip : virtual public Ship {
private:

public:
    virtual void move() = 0;
};

#endif
