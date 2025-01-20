#ifndef SHIP_H
#define SHIP_H

#include <iostream>
using namespace std;


class Ship {
private:
    int no_ships;
protected:
    int id;
    static int ship_count;
public:
    virtual void action_plan() = 0;
    Ship() {
        cout << "Ship Created" << endl;
        ship_count++;
        id = ship_count;
        cout << id << endl;

        //Ships = Game_Setup::Ships;
    }


    ~Ship() {
        ship_count--;

        cout << "Ship death" << endl;
    }
};

#endif