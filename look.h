#ifndef LOOK_H
#define LOOK_H

#include <random>
#include <iostream>

#include "game_setup.h"
#include "ship.h"

using namespace std;

class Look : virtual public Ship {
private:

protected:
    int directions[8][2] = { {-1, 1},  {0, 1},  {1, 1},  // Up-left, Up, Up-right
                             {-1, 0},           {1, 0},   // Left,       Right
                             {-1, -1}, {0, -1}, {1, -1}    // Down-left, Down, Down-right
    };
    char look_results[8];
    int target[2];
    virtual void look() = 0;
};

#endif