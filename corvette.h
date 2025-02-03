#ifndef CORVETTE_H
#define CORVETTE_H

#include <iostream>
using namespace std;

#include "ship.h"
#include "move.h"
#include "shoot.h"

class Corvette : public Shoot {
private:

public:
    Corvette() {
        cout << "Corvette created! " << endl;
    }

        void shoot() override {
        int directions[8][2] = {
            {-1, -1}, {-1, 0}, {-1, 1},  // Up-left, Up, Up-right
            {0, -1},          {0, 1},   // Left,       Right
            {1, -1},  {1, 0}, {1, 1}    // Down-left, Down, Down-right
        };

        // will select a direction randomly to shoot
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dir_dis(0, 7);
        int dir = dir_dis(gen);

        // this will calculate target position
        int target_x = x + directions[dir][0];
        int target_y = y + directions[dir][1];

        cout << "Attacked location: (" << target_x + 1 << ", " << target_y + 1 << ")" << endl;
        cout << TeamA_symbols[0] << endl;
        cout << TeamB_symbols[0] << endl;
        cout << endl;

        if (target_x < 0 || target_x >= game_settings[1] || target_y < 0 || target_y >= game_settings[2]) {
            cout << "Wasted a shot! The Ship shot at a position exceeding the game map!" << endl;
            return;
        }

        if (game_map[target_x][target_y] != '0' && game_map[target_x][target_y] != '1') {
            if (team == 'A') {
                for (int i = 0; i < TeamB[0]; i++) {
                    if (TeamB_symbols[i] == game_map[target_x][target_y]) {
                        cout << TeamB_symbols[i] << endl;
                        cout << game_map[target_x][target_y] << endl; 

                        kills++;
                        cout << "Kill incremented" << endl;
                        kill(target_x, target_y);

                        //add promotion logic here?
                        //remember to change the ship symbol on the map
                        break;
                    }
                }
            } else {
                for (int i = 0; i < TeamA[0]; i++) {
                    if (TeamA_symbols[i] != game_map[target_x][target_y]) {
                        cout << TeamA_symbols[i] << endl;
                        cout << game_map[target_x][target_y] << endl; 

                        kills++;
                        cout << "Kill incremented" << endl;
                        kill(target_x, target_y);
                        break;
                    }
                }
            }
        }

        if (game_map[target_x][target_y] == '0' || game_map[target_x][target_y] == '1') {
            cout << "Missed! No enemy ship at target location." << endl;
        }
    }

    void action_plan() override {
        shoot();

    }
    
};

#endif