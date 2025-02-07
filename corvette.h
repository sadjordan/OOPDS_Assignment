#ifndef CORVETTE_H
#define CORVETTE_H

#include <iostream>
#include "ship.h"
#include "shootingship.h"

class Corvette : public ShootingShip {
public:
    Corvette();
    void shoot() override;
    void action_plan() override;
};

#endif