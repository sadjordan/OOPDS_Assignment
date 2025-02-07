#ifndef CRUISER_H
#define CRUISER_H

#include <iostream>
#include "ship.h"
#include "destroyer.h"
#include "movingship.h"
#include "ramship.h"
#include "seeingrobot.h"

class Cruiser : public MovingShip, public RamShip, public SeeingRobot {
private:
    bool target_acquired = false;

public:
    Cruiser();
    void promotion();
    void look() override;
    void move() override;
    void destroy() override;
    void action_plan() override;
};

#endif