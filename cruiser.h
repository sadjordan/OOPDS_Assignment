#ifndef CRUISER_H
#define CRUISER_H

#include <iostream>
using namespace std;

#include "ship.h"
#include "move.h"
#include "shoot.h"

class Cruiser : public Move {
private:

public:
    Cruiser() {
        cout << "Cruiser created! " << endl;
    }

    void action_plan() override {
        move();

    }
    
};

#endif