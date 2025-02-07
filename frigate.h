#ifndef FRIGATE_H
#define FRIGATE_H

#include <iostream>
#include "ship.h"
#include "shootingship.h"
#include "corvette.h"

class Frigate : public ShootingShip {
private:
    int cycle = 0;

public:
    Frigate();

    void promotion();

    void shoot() override;
    void action_plan() override;
};

#endif