#ifndef RAMSHIP_H
#define RAMSHIP_H

#include "ship.h"
#include <iostream>
#include <random>

class RamShip : virtual public Ship {
public:
    void ram(Ship* to_be_killed);
    virtual void destroy() = 0;
};

#endif
