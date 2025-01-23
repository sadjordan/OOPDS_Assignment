#ifndef MOVE_H
#define MOVE_H

#include <random>
#include <iostream>

using namespace std;

class Move : public Ship {
private:

public:
    // Move(Ship_Details* Ships) {
    //     this->Ships = Ships;
    // }

    void move(char** game_map, Ship_Details* Ships, int ship_id) {
        random_device rd;
        mt19937 gen(rd());

        cout << "Move ship id: " << ship_id-1 << endl;
        cout << Ships << endl;

        cout << type << endl;

        uniform_int_distribution<> movement_decider(1, 4);
        int anumber = movement_decider(gen);

        switch (anumber) {
        case 1:
            cout << "Up" << endl;
            game_map[x][y] = '0';
            y++;
            game_map[x][y] = symbol;
            break;
        case 2:
            cout << "Down" << endl;
            game_map[x][y] = '0';
            y--;
            game_map[x][y] = symbol;
            break;
        case 3:
            cout << "Left" << endl;
            game_map[x][y] = '0';
            x--;
            game_map[x][y] = symbol;
            break;
        case 4:
            cout << "Right" << endl;
            game_map[x][y] = '0';
            x++;
            game_map[x][y] = symbol;
            break;
        default:
            cout << "Technically impossible so if you see this the world must be ending" << endl;
            break;
        }

        cout << "Move end" << endl;
    }


};

#endif