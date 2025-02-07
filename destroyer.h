#ifndef DESTROYER_H
#define DESTROYER_H

#include <iostream>
#include <random>
#include "ship.h"
#include "movingship.h"
#include "shootingship.h"
#include "ramship.h"
#include "seeingrobot.h"
#include "supership.h"

class Destroyer : public MovingShip, public ShootingShip, public RamShip, public SeeingRobot {
private:
    bool target_acquired = false;

public:
    Destroyer();

    void promotion();

    void look() override;
    void move() override;
    void destroy() override;
    void shoot() override;
    void action_plan() override;
};

#endif