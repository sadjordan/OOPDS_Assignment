#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <iostream>
using namespace std;

#include "ship.h"
#include "move.h"

class Battleship : public Move {
private:
    char** game_map;
    Ship_Details* Ships;

public:
    Battleship(char** game_map, Ship_Details* Ships) {
        cout << "Battleship created! " << endl;
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