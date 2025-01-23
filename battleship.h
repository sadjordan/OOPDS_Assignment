#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <iostream>
using namespace std;

#include "ship.h"
#include "move.h"
#include "shoot.h"

class Battleship : public Move {
private:
    char** game_map;
    //int* game_settings;

public:
    Battleship(char** game_map) {
        cout << "Battleship created! " << endl;
        this->game_map = game_map;

        cout << "ID: " << id << endl;
    }

    Battleship() {

    }

    void action_plan() override {
        move(game_map, id);

    }
    
};

#endif