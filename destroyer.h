#ifndef DESTROYER_H
#define DESTROYER_H

#include <iostream>
using namespace std;

#include "ship.h"
#include "move.h"
#include "shoot.h"
#include "destroy.h"
#include "look.h"

class Destroyer : public Move, public Shoot, public Destroy, public Look {
private:

public:
    Destroyer() {
        cout << "Destroyer created! " << endl;
    }

    void look() override {

        for (int i = 0; i < 8; i++) {
            try {
                look_results[i] = game_map[x + directions[i][0]][y + directions[i][1]];
            } catch (const out_of_range& oor) {
                look_results[i] = NULL;
            }
        }

    }

    void move() override {
        random_device rd;
        mt19937 gen(rd());

        // cout << "Move ship id: " << ship_id - 1 << endl;
        cout << type << endl;

        uniform_int_distribution<> movement_decider(1, 4);
        int anumber;
        
        for (int i = 0; i < 8; i++) {
            if (look_results[i] != '0' && look_results[i] != '1' && look_results[i] != NULL) {
                if (team == 'A') {
                    for (int i = 0; i < TeamB[0]; i++) {
                        if (TeamB_symbols[i] == look_results[i]) {
                            if (i == 1 || i == 3 || i == 4 || i == 6) {
                                // abstain from moving in order to destroy next turn
                                target[0] = x + directions[i][0];
                                target[1] = y + directions[i][1];
                                return;
                            } else if (i == 0) { //i == 5
                                game_map[x][y] = '0';
                                x--;
                                game_map[x][y] = symbol;
                                target[0] = x - 1;
                                target[1] = y + 1;
                                return;
                            } else if (i == 5) {
                                game_map[x][y] = '0';
                                y--;
                                game_map[x][y] = symbol;
                                target[0] = x - 1;
                                target[1] = y - 1;
                                return;
                            } else if (i == 2) {
                                game_map[x][y] = '0';
                                y++;
                                game_map[x][y] = symbol;
                                target[0] = x + 1;
                                target[1] = y + 1;
                                return;
                            }
                            else if (i == 7) {
                                game_map[x][y] = '0';
                                x++;
                                game_map[x][y] = symbol;
                                target[0] = x + 1;
                                target[1] = y - 1;
                                return;
                            }
                        }
                    }
                } else {
                    for (int i = 0; i < TeamA[0]; i++) {
                        if (TeamA_symbols[i] != look_results[i]) {
                            x = x + directions[i][0];
                            y = y + directions[i][1];
                            game_map[x][y] = symbol;
                            // cout << TeamA_symbols[i] << endl;
                            // cout << look_results[i] << endl; 
                            return;
                        }
                    }
                }
            }
        }

        //if nothing is seen revert to random movement
        
        bool valid_move = false;
        int counter = 0;

        int old_x = x;
        int old_y = y;

        while (!valid_move && counter < 12) {
            anumber = movement_decider(gen);

            switch (anumber) {
            case 1: // Up
                if (y + 1 < game_settings[2] && game_map[x][y + 1] == '0') {
                    cout << "(" << x << ", " << y << ")" << endl;
                    cout << "Up" << endl;
                    game_map[x][y] = '0';
                    y++;
                    game_map[x][y] = symbol;
                    valid_move = true;
                } else {
                    counter++;
                    cout << "Invalid move Up, out of bounds. Retrying..." << endl;
                }
                break;
            case 2: // Down
                if (y - 1 >= 0 && game_map[x][y - 1] == '0') {
                    cout << "(" << x << ", " << y << ")" << endl;
                    cout << "Down" << endl;
                    game_map[x][y] = '0';
                    y--;
                    game_map[x][y] = symbol;
                    valid_move = true;
                } else {
                    counter++;
                    cout << "Invalid move Down, out of bounds. Retrying..." << endl;
                }
                break;
            case 3: // Left
                if (x - 1 >= 0 && game_map[x - 1][y] == '0') {
                    cout << "(" << x << ", " << y << ")" << endl;
                    cout << "Left" << endl;
                    game_map[x][y] = '0';
                    x--;
                    game_map[x][y] = symbol;
                    valid_move = true;
                } else {
                    counter++;
                    cout << "Invalid move Left, out of bounds. Retrying..." << endl;
                }
                break;
            case 4: // Right
                if (x + 1 < game_settings[1] && game_map[x + 1][y] == '0') {
                    cout << "(" << x << ", " << y << ")" << endl;
                    cout << "Right" << endl;
                    game_map[x][y] = '0';
                    x++;
                    game_map[x][y] = symbol;
                    valid_move = true;
                } else {
                    counter++;
                    cout << "Invalid move Right, out of bounds. Retrying..." << endl;
                }
                break;
            default:
                cout << "Technically impossible so if you see this the world must be ending" << endl;
                break;
            }
        }

        if (x != old_x || y != old_y) {
            cout << "Movement successful!" << endl;
        } else {
            cout << "No movement was made" << endl;
        }

        cout << "Move end" << endl;
    }

    void destroy() override {
        //moving to destroy

        game_map[x][y] = '0'; 
        x = target[0];
        y = target[1];

        for (int i = 0; i < turn_queue->list_size(); i++) {
            if ((*turn_queue)[i]->get_x() == x && (*turn_queue)[i]->get_y() == y && (*turn_queue)[i]->get_team() != team) {
                cout << "Destroy function called!" << endl;
                Destroy::kill((*turn_queue)[i]);
            }
        }
    }

    void shoot() override {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dir_dis(-5, 5);
        int random_x = dir_dis(gen);
        int random_y = dir_dis(gen);

        while (abs(random_x) + abs(random_y) > 5 || abs(random_x) + abs(random_y) == 0) {
            random_x = dir_dis(gen);
            random_y = dir_dis(gen);
        }

        // this will calculate target position
        int target_x = x + random_x;
        int target_y = y + random_y;

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
                        Shoot::kill(target_x, target_y);

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
                        Shoot::kill(target_x, target_y);
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
        look();
        move();
        destroy();
        shoot();
    }
    
};

#endif