#ifndef FRIGATE_H
#define FRIGATE_H

#include <iostream>
using namespace std;

#include "ship.h"
#include "move.h"
#include "shoot.h"

class Frigate : public Move {
private:

public:
    Frigate() {
        cout << "Frigate created! " << endl;
    }

    void action_plan() override {
        move();

    }
    
};

#endif