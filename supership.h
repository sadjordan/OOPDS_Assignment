#ifndef SUPERSHIP_H
#define SUPERSHIP_H

#include <iostream>
using namespace std;

#include "ship.h"
#include "movingship.h"
#include "shootingship.h"
#include "ramship.h"
#include "seeingrobot.h"

class Supership : public MovingShip, public ShootingShip, public RamShip, public SeeingRobot {
private:
    bool target_acquired = false;
    int previous[2];

public:
    Supership() {
        cout << "Supership created! " << endl;
    }

    void look() override {
        for (int i = 0; i < 8; i++) {
            if (x + directions[i][0] < 0 || x + directions[i][0] >= game_settings[1] || y + directions[i][1] < 0 || y + directions[i][1] >= game_settings[2]) {
                look_results[i] = '5';
            } else {
                cout << "test" << endl;
                look_results[i] = game_map[x + directions[i][0]][y + directions[i][1]];
            }
        }

        for (int i = 0; i < 8; i++) {
            cout << "Look results " << i << " :" << look_results[i] << endl;
        }
    }

void move() override {
        target_acquired = false;

        // Check for adjacent enemies
        for (int i = 0; i < 8; i++) {
            if (look_results[i] != '0' && look_results[i] != '1' && look_results[i] != '5') {
                if ((i == 1 || i == 3 || i == 4 || i == 6) && 
                    ((team == 'A' && look_results[i] == 'B') || (team == 'B' && look_results[i] == 'A'))) {
                    // Enemy is adjacent, abstain from moving
                    cout << "abstaining" << endl;
                    target[0] = x + directions[i][0];
                    target[1] = y + directions[i][1];
                    target_acquired = true;
                    return;
                }
            }
        }

        // Move towards enemy units if not adjacent
        for (int i = 0; i < 8; i++) {
            if (look_results[i] != '0' && look_results[i] != '1' && look_results[i] != '5') {
                if ((team == 'A' && look_results[i] == 'B') || (team == 'B' && look_results[i] == 'A')) {
                    if (i == 0 || i == 2 || i == 5 || i == 7) {
                        int new_x = x + directions[i][0];
                        int new_y = y + directions[i][1];
                        if (game_map[new_x][new_y] == '0') {
                            game_map[x][y] = '0';
                            x = new_x;
                            y = new_y;
                            game_map[x][y] = symbol;
                            // Save target coordinates (enemy position)
                            target[0] = x + directions[i][0];
                            target[1] = y + directions[i][1];
                            target_acquired = true;
                            cout << "target acquired" << endl;
                            return;
                        }
                    }
                }
            }
        }

        // If no enemies are found, move randomly
        bool valid_move = false;
        int counter = 0;

        int old_x = x;
        int old_y = y;

        random_device rd;
        mt19937 gen(rd());

        uniform_int_distribution<> movement_decider(1, 4);
        int anumber;

        while (!valid_move && counter < 12) {
            anumber = movement_decider(gen);

            switch (anumber) {
            case 1: // Up
                if (y + 1 < game_settings[2] && game_map[x][y + 1] == '0') {
                    game_map[x][y] = '0';
                    y++;
                    game_map[x][y] = symbol;
                    valid_move = true;
                } else {
                    counter++;
                }
                break;
            case 2: // Down
                if (y - 1 >= 0 && game_map[x][y - 1] == '0') {
                    game_map[x][y] = '0';
                    y--;
                    game_map[x][y] = symbol;
                    valid_move = true;
                } else {
                    counter++;
                }
                break;
            case 3: // Left
                if (x - 1 >= 0 && game_map[x - 1][y] == '0') {
                    game_map[x][y] = '0';
                    x--;
                    game_map[x][y] = symbol;
                    valid_move = true;
                } else {
                    counter++;
                }
                break;
            case 4: // Right
                if (x + 1 < game_settings[1] && game_map[x + 1][y] == '0') {
                    game_map[x][y] = '0';
                    x++;
                    game_map[x][y] = symbol;
                    valid_move = true;
                } else {
                    counter++;
                }
                break;
            default:
                cout << "Technically impossible so if you see this the world must be ending" << endl;
                break;
            }
        }
    }

    void destroy() override {
        //moving to destroy

        game_map[x][y] = '0'; 

        if (target_acquired == true) {
            x = target[0];
            y = target[1];
        }
    
        for (int i = 0; i < turn_queue->list_size(); i++) {
            if ((*turn_queue)[i]->get_x() == x && (*turn_queue)[i]->get_y() == y && (*turn_queue)[i]->get_team() != team) {
                // cout << "Destroy function called!" << endl;
                ram((*turn_queue)[i]);
            }
        }

        game_map[x][y] = symbol;
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
        int dir;

        do {
            dir = dir_dis(gen);
        } while (dir == previous[0] || dir == previous[1]);

        if (previous[0] == -1) {
            previous[0] = dir;
        } else if (previous[1] == -1) {
            previous[1] = previous[0];
            previous[0] = dir;
        }

        // this will calculate target position
        int target_x = x + directions[dir][0];
        int target_y = y + directions[dir][1];

        cout << "Attacked location: (" << target_x + 1 << ", " << target_y + 1 << ")" << endl;
        // cout << TeamA_symbols[0] << endl;
        // cout << TeamB_symbols[0] << endl;
        // cout << endl;

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
                        // cout << "Kill incremented" << endl;
                        // cout << "TeamB killed" << endl;
                        kill(target_x, target_y);

                        //add promotion logic here?
                        //remember to change the ship symbol on the map
                        break;
                    }
                }
            } else {
                for (int i = 0; i < TeamA[0]; i++) {
                    if (TeamA_symbols[i] == game_map[target_x][target_y]) {
                        cout << TeamA_symbols[i] << endl;
                        cout << game_map[target_x][target_y] << endl; 

                        kills++;
                        // cout << "Kill incremented" << endl;
                        // cout << "TeamA killed" << endl;
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
        previous[0] = -1;
        previous[1] = -1;
        look();
        move();
        destroy();
        shoot();
        shoot();
        shoot();
    }
    
};

#endif