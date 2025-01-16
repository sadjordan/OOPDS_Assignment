#ifndef MOVE_H
#define MOVE_H

#include <random>
#include <iostream>
using namespace std;

class Move : public Ship {
private:

public:
    void move(char** game_map, Ship_Details* Ships, int ship_id) {
        random_device rd;
        mt19937 gen(rd());

        uniform_int_distribution<> movement_decider(1, 4);
        int anumber = movement_decider(gen);

        switch (anumber) {
        case 1:
            cout << "Case 1" << endl;
            break;
        case 2:
            cout << "Case 2" << endl;
            break;
        case 3:
            cout << "Case 3" << endl;
            break;
        case 4:
            cout << "Case 4" << endl;
            break;
        default:
            cout << "Default case" << endl;
            break;
        }
    }
};

#endif