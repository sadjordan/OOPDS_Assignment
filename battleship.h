#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <iostream>
using namespace std;

#include "ship.h"
#include "move.h"

class Battleship : public Ship {
public:
    Battleship() {
        cout << "Battleship created!" << endl;
    }

    // if (TeamA_classes[i - 1] == "Battleship") {
    //     Ships[ship_counter].ship_ptr = new Battleship;
    // }
        
};

#endif