#ifndef SHIP_DETAILS_H
#define SHIP_DETAILS_H


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>

using namespace std;

class Ship;

struct Ship_Details {
        // int id;
        Ship* ship_ptr;
        char team;
        string type;
        char symbol;
        int x;
        int y;
        string status;
        int lives;
        int kills;
    };

#endif