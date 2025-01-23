#ifndef CRUISER_H
#define CRUISER_H

#include <iostream>
using namespace std;

#include "ship.h"
#include "move.h"
#include "shoot.h"

class Cruiser : public Move {
private:
    char** game_map;

public:
    Cruiser(char** game_map) {
        cout << "Cruiser created! " << endl;
        this->game_map = game_map;

        cout << "ID: " << id << endl;
    }

    void action_plan() override {
        move(game_map, id);

    }
    
};

#endif