#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <iostream>
using namespace std;

#include "ship.h"
#include "move.h"
#include "shoot.h"

class Battleship : public Move, public Shoot {
private:
    char** game_map;
    //int* game_settings;

public:
    Battleship() {
        cout << "Battleship created! " << endl;
    }

    void action_plan() override {
        move();
        shoot();

    }
    
};

#endif