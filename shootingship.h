#ifndef SHOOTINGSHIP_H
#define SHOOTINGSHIP_H

#include <iostream>
#include <random>
#include "ship.h"
#include "linkedlist.h"

class ShootingShip : virtual public Ship {
public:
    void kill(int target_x, int target_y);
    virtual void shoot() = 0;
};

#endif
