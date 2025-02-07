#ifndef SUPERSHIP_H
#define SUPERSHIP_H

#include <iostream>
#include <random>
#include "ship.h"
#include "movingship.h"
#include "shootingship.h"
#include "ramship.h"
#include "seeingrobot.h"

class SuperShip : public MovingShip, public ShootingShip, public RamShip, public SeeingRobot {
private:
    bool target_acquired = false;
    int previous[2];

public:
    SuperShip();

    void look() override;
    void move() override;
    void destroy() override;
    void shoot() override;
    void action_plan() override;
};

#endif