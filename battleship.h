#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <iostream>
#include <random>

#include "ship.h"
#include "shootingship.h"
#include "movingship.h"
#include "destroyer.h"

using namespace std;

class Battleship : public ShootingShip, public MovingShip {
private:
    //int* game_settings;
    int kills = 0;

public:
    Battleship();
    void promotion();
    void move() override;
    void shoot() override;
    void action_plan() override;
};

#endif
