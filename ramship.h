#ifndef RAMSHIP_H
#define RAMSHIP_H

#include <iostream>
#include <random>

class RamShip : virtual public Ship {
private:

public:
    void ram(Ship* to_be_killed) {
        if (to_be_killed->get_lives() == 0) {
            cout << "The ship has no more lives" << endl;
            Ship* temp = to_be_killed;
            cout << "Pass 1" << endl;
            cout << temp << endl;
            cout << to_be_killed << endl;
            turn_queue->deleteNode(temp);
            cout << "Pass 2" << endl;
            delete temp;

            game_map[x][y] = symbol;

            return;
        }
        to_be_killed->set_status("In Respawn Queue");
        to_be_killed->decrement_lives();
        to_be_killed->set_x(NULL);
        to_be_killed->set_y(NULL);
        cout << "Pass 2" << endl;

        game_map[x][y] = symbol;
        cout << "Pass 3" << endl;

        cout << "A " << to_be_killed->get_type() << " from Team " << to_be_killed->get_team() << " was hit!" << endl;

        respawn_queue->push_back(to_be_killed);
        turn_queue->deleteNode(to_be_killed);
        cout << "Pass 4" << endl;
    }

    virtual void destroy() = 0;
};

#endif