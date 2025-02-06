#ifndef CRUISER_H
#define CRUISER_H

#include <iostream>
using namespace std;

#include "ship.h"
#include "movingship.h"
#include "ramship.h"
#include "seeingrobot.h"

class Cruiser : public MovingShip, public RamShip, public SeeingRobot {
private:
    bool target_acquired = false;
public:
    Cruiser() {
        cout << "Cruiser created! " << endl;
    }

    void promotion() {
        cout << "Cruiser has been promoted to Destroyer!" << endl;

        // cin.get();

        Ship* promoted_ship = new Destroyer;

        int replace_index = turn_queue->find_index(this);

        turn_queue->replace(replace_index, promoted_ship);

        promoted_ship->set_x(x);
        promoted_ship->set_y(y);
        promoted_ship->set_team(team);
        promoted_ship->set_type("Destroyer");

        bool found_symbol = false;

        if (team == 'A') {
            for (int i = 0; i < TeamA[0]; i++) {
                if (TeamA_classes[i] == "Destroyer") {
                    promoted_ship->set_symbol(TeamA_symbols[i]);
                    found_symbol = true;
                    break;
                }
            }
        } else {
            for (int i = 0; i < TeamB[0]; i++) {
                if (TeamB_classes[i] == "Destroyer") {
                    promoted_ship->set_symbol(TeamB_symbols[i]);
                    found_symbol = true;
                    break;
                }
            }
        }

        if (found_symbol == false && team == 'A') {
            cout << "No symbol found for Cruiser. Using default symbol." << endl;
            promoted_ship->set_symbol(default_teamA_symbols[1]);
        } else if (found_symbol == false && team == 'B') {
            cout << "No symbol found for Cruiser. Using default symbol." << endl;
            promoted_ship->set_symbol(default_teamB_symbols[1]);
        }

        //promoted_ship->set_symbol('5');

        game_map[x][y] = promoted_ship->get_symbol();

        delete this;
    }

    void look() override {
        for (int i = 0; i < 8; i++) {
            if (x + directions[i][0] < 0 || x + directions[i][0] >= game_settings[1] || y + directions[i][1] < 0 || y + directions[i][1] >= game_settings[2]) {
                look_results[i] = '5';
            } else {
                look_results[i] = game_map[x + directions[i][0]][y + directions[i][1]];
            }
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
        x = target[0];
        y = target[1];

        for (int i = 0; i < turn_queue->list_size(); i++) {
            if ((*turn_queue)[i]->get_x() == x && (*turn_queue)[i]->get_y() == y && (*turn_queue)[i]->get_team() != team) {
                // cout << "Destroy function called!" << endl;
                ram((*turn_queue)[i]);
            }
        }

        game_map[x][y] = symbol;
    }

    void action_plan() override {
        look();
        move();
        if (target_acquired == true) {
            destroy();
        }
        if (kills > 3) {
            promotion();
        }
        cout << "(" << x << ", " << y << ")" << endl;
    }
    
};

#endif