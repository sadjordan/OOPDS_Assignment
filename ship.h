#ifndef SHIP_H
#define SHIP_H

#include <iostream>
using namespace std;


class Ship {
private:
    int no_ships;

    Ship_Details* Ships;
protected:
    int id;
    static int ship_count;

public:
    virtual void action_plan() = 0;
    Ship() {
        cout << "Ship Created" << endl;
        ship_count++;
        id = ship_count - 1;
        cout << id << endl;

        //Ships = Game_Setup::Ships;
    }


    ~Ship() {
        ship_count--;

        cout << "Ship death" << endl;
    }

    void getShips() {
        for (int i = 0; i < no_ships; i++) {
            cout << i << ": " << "ID: " << Ships[i].id << ", Pointer: " << Ships[i].ship_ptr << ", Team: " << Ships[i].team << ", Type: " << Ships[i].type << ", Symbol: " << Ships[i].symbol << ", Position: (" << Ships[i].x << ", " << Ships[i].y << "), Status: " << Ships[i].status << ", Lives: " << Ships[i].lives << ", Kills: " << Ships[i].kills << endl;
            }
    }
};

#endif