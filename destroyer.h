#ifndef DESTROYER_H
#define DESTROYER_H

#include <iostream>
using namespace std;

#include "ship.h"
#include "move.h"
#include "shoot.h"

class Destroyer : public Move {
private:

public:
    Destroyer() {
        cout << "Destroyer created! " << endl;
    }

    void action_plan() override {
        move();

    }
    
};

#endif