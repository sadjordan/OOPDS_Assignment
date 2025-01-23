#ifndef DESTROYER_H
#define DESTROYER_H

#include <iostream>
using namespace std;

#include "ship.h"
#include "move.h"
#include "shoot.h"

class Destroyer : public Move {
private:
    char** game_map;
    Ship_Details* Ships;

public:
    Destroyer(char** game_map, Ship_Details* Ships) {
        cout << "Destroyer created! " << endl;
        cout << Ships << endl;
        this->game_map = game_map;
        this->Ships = Ships;

        cout << "ID: " << id << endl;
    }

    void action_plan() override {
        move(game_map, Ships, id);

    }
    
};

#endif