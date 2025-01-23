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

public:
    Destroyer(char** game_map) {
        cout << "Destroyer created! " << endl;
        this->game_map = game_map;

        cout << "ID: " << id << endl;
    }

    void action_plan() override {
        move(game_map, id);

    }
    
};

#endif