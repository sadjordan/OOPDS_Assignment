#ifndef AMPHIBIOUS_H
#define AMPHIBIOUS_H

#include <iostream>
using namespace std;

#include "ship.h"
#include "movingship.h"
#include "shootingship.h"
#include "supership.h"

class Amphibious : public MovingShip, public ShootingShip {
private:
    char ship_is_on = '0';

public:
    Amphibious();
    void promotion();
    void move() override;
    void shoot() override;
    void action_plan() override;
};

#endif