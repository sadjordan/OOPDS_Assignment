#ifndef CRUISER_H
#define CRUISER_H

#include <iostream>
using namespace std;

#include "ship.h"
#include "move.h"
#include "destroy.h"
#include "look.h"

class Cruiser : public Move, public Destroy, public Look {
private:
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
                if (TeamB_classes[i] == "Cruiser") {
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
                cout << "test" << endl;
                look_results[i] = game_map[x + directions[i][0]][y + directions[i][1]];
            }
        }
    }

    void move() override {
        cout << "Cruiser move" << endl;

        // cout << "Move ship id: " << ship_id - 1 << endl;
        cout << type << endl;

        for (int i = 0; i < 8; i++) {
            cout << look_results[i] << endl;
        }
        
        
        for (int i = 0; i < 8; i++) {
            if (look_results[i] != '0' && look_results[i] != '1' && look_results[i] != '5') {
                if (team == 'A') {
                    for (int i = 0; i < TeamB[0]; i++) {
                        if (TeamB_symbols[i] == look_results[i]) {
                            if (i == 1 || i == 3 || i == 4 || i == 6) {
                                // abstain from moving in order to destroy next turn
                                target[0] = x + directions[i][0];
                                target[1] = y + directions[i][1];
                                return;
                            } else if (i == 0) { //i == 5
                                if (game_map[x - 1][y] == '0') {
                                    game_map[x][y] = '0';
                                    x--;
                                    game_map[x][y] = symbol;
                                    target[0] = x - 1;
                                    target[1] = y + 1;
                                    return;
                                } else if (game_map[x][y - 1] == '0') {
                                    game_map[x][y] = '0';
                                    y++;
                                    game_map[x][y] = symbol;
                                    target[0] = x - 1;
                                    target[1] = y + 1;
                                    return;
                                }
                            } else if (i == 5) {
                                if (game_map[x - 1][y] == '0') {
                                    game_map[x][y] = '0';
                                    x--;
                                    game_map[x][y] = symbol;
                                    target[0] = x - 1;
                                    target[1] = y - 1;
                                    return;
                                } else if (game_map[x][y - 1] == '0') {
                                    game_map[x][y] = '0';
                                    y--;
                                    game_map[x][y] = symbol;
                                    target[0] = x - 1;
                                    target[1] = y - 1;
                                    return;
                                }
                            } else if (i == 2) {
                                if (game_map[x + 1][y] == '0') {
                                    game_map[x][y] = '0';
                                    x++;
                                    game_map[x][y] = symbol;
                                    target[0] = x + 1;
                                    target[1] = y + 1;
                                    return;
                                } else if (game_map[x][y - 1] == '0') {
                                    game_map[x][y] = '0';
                                    y++;
                                    game_map[x][y] = symbol;
                                    target[0] = x + 1;
                                    target[1] = y + 1;
                                    return;
                                }
                            }
                            else if (i == 7) {
                                if (game_map[x + 1][y] == '0') {
                                    game_map[x][y] = '0';
                                    x++;
                                    game_map[x][y] = symbol;
                                    target[0] = x + 1;
                                    target[1] = y - 1;
                                    return;
                                } else if (game_map[x][y - 1] == '0') {
                                    game_map[x][y] = '0';
                                    y--;
                                    game_map[x][y] = symbol;
                                    target[0] = x + 1;
                                    target[1] = y - 1;
                                    return;
                                }
                            }
                        }
                    }
                } else {
                    for (int i = 0; i < TeamA[0]; i++) {
                        if (TeamA_symbols[i] == look_results[i]) {
                            if (i == 1 || i == 3 || i == 4 || i == 6) {
                                // abstain from moving in order to destroy next turn
                                target[0] = x + directions[i][0];
                                target[1] = y + directions[i][1];
                                return;
                            } else if (i == 0) { //i == 5
                                if (game_map[x - 1][y] == '0') {
                                    game_map[x][y] = '0';
                                    x--;
                                    game_map[x][y] = symbol;
                                    target[0] = x - 1;
                                    target[1] = y + 1;
                                    return;
                                } else if (game_map[x][y - 1] == '0') {
                                    game_map[x][y] = '0';
                                    y++;
                                    game_map[x][y] = symbol;
                                    target[0] = x - 1;
                                    target[1] = y + 1;
                                    return;
                                }
                            } else if (i == 5) {
                                if (game_map[x - 1][y] == '0') {
                                    game_map[x][y] = '0';
                                    x--;
                                    game_map[x][y] = symbol;
                                    target[0] = x - 1;
                                    target[1] = y - 1;
                                    return;
                                } else if (game_map[x][y - 1] == '0') {
                                    game_map[x][y] = '0';
                                    y--;
                                    game_map[x][y] = symbol;
                                    target[0] = x - 1;
                                    target[1] = y - 1;
                                    return;
                                }
                            } else if (i == 2) {
                                if (game_map[x + 1][y] == '0') {
                                    game_map[x][y] = '0';
                                    x++;
                                    game_map[x][y] = symbol;
                                    target[0] = x + 1;
                                    target[1] = y + 1;
                                    return;
                                } else if (game_map[x][y - 1] == '0') {
                                    game_map[x][y] = '0';
                                    y++;
                                    game_map[x][y] = symbol;
                                    target[0] = x + 1;
                                    target[1] = y + 1;
                                    return;
                                }
                            }
                            else if (i == 7) {
                                if (game_map[x + 1][y] == '0') {
                                    game_map[x][y] = '0';
                                    x++;
                                    game_map[x][y] = symbol;
                                    target[0] = x + 1;
                                    target[1] = y - 1;
                                    return;
                                } else if (game_map[x][y - 1] == '0') {
                                    game_map[x][y] = '0';
                                    y--;
                                    game_map[x][y] = symbol;
                                    target[0] = x + 1;
                                    target[1] = y - 1;
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }

        //if nothing is seen revert to random movement
        cout << "Random movement" << endl;
        cout << symbol << endl;
        
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

    void action_plan() override {
        look();
        move();
        destroy();
    }
    
};

#endif