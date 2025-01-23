#ifndef FRIGATE_H
#define FRIGATE_H

#include <iostream>
using namespace std;

#include "ship.h"
#include "move.h"
#include "shoot.h"

class Frigate : public Move {
private:
    char** game_map;

public:
    Frigate(char** game_map) {
        cout << "Frigate created! " << endl;
        this->game_map = game_map;

        cout << "ID: " << id << endl;
    }

    void action_plan() override {
        move(game_map, id);

    }
    
};

#endif