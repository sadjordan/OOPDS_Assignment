#ifndef FRIGATE_H
#define FRIGATE_H

#include <iostream>
using namespace std;

#include "ship.h"
#include "shootingship.h"
#include "corvette.h"

class Frigate : public ShootingShip {
private:
    int cycle = 0;
public:
    Frigate() {
        cout << "Frigate created! " << endl;
        outputFile << "Frigate created!" << endl;
    }

    void promotion() {
        cout << "Frigate has been promoted to Corvette!" << endl;
        outputFile << "Frigate has been promoted to Corvette!" << endl;
        
        // cin.get();

        Ship* promoted_ship = new Corvette();

        int replace_index = turn_queue->find_index(this);

        turn_queue->replace(replace_index, promoted_ship);

        promoted_ship->set_id(id);
        promoted_ship->set_x(x);
        promoted_ship->set_y(y);
        promoted_ship->set_team(team);
        promoted_ship->set_type("Corvette");

        bool found_symbol = false;

        if (team == 'A') {
            for (int i = 0; i < TeamA[0]; i++) {
                if (TeamA_classes[i] == "Corvette") {
                    promoted_ship->set_symbol(TeamA_symbols[i]);
                    found_symbol = true;
                    break;
                }
            }
        } else {
            for (int i = 0; i < TeamB[0]; i++) {
                if (TeamB_classes[i] == "Corvette") {
                    promoted_ship->set_symbol(TeamB_symbols[i]);
                    found_symbol = true;
                    break;
                }
            }
        }

        if (found_symbol == false && team == 'A') {
            // cout << "No symbol found for Corvette. Using default symbol." << endl;
            promoted_ship->set_symbol(default_teamA_symbols[4]);
        } else if (found_symbol == false && team == 'B') {
            // cout << "No symbol found for Corvette. Using default symbol." << endl;
            promoted_ship->set_symbol(default_teamB_symbols[4]);
        }

        //promoted_ship->set_symbol('5');

        game_map[x][y] = promoted_ship->get_symbol();
        symbol_map[x][y] = promoted_ship->get_id();

        delete this;
    }


    void shoot() override {
        int directions[8][2] = { {-1, 1},  {0, 1},  {1, 1},  // Up-left, Up, Up-right
                                 {-1, 0},           {1, 0},  // Left,       Right
                                 {-1, -1}, {0, -1}, {1, -1}  // Down-left, Down, Down-right
        };
        // if a ship cannot look, then it cannot possibly know that its shot will exceed the map
        // or if a ship shoots randomly, then it must also disregard the map bounds

        if (cycle == 7) {
            cycle = 0;
        }

        // this will calculate target position
        int target_x = x + directions[cycle][0];
        int target_y = y + directions[cycle][1];

        cycle++;

        cout << "Attacked location: (" << target_x + 1 << ", " << target_y + 1 << ")" << endl;
        outputFile << "Attacked location: (" << target_x + 1 << ", " << target_y + 1 << ")" << endl;
        // cout << TeamA_symbols[0] << endl;
        // cout << TeamB_symbols[0] << endl;
        // cout << endl;

        if (target_x < 0 || target_x >= game_settings[1] || target_y < 0 || target_y >= game_settings[2]) {
            cout << "Wasted a shot! The Ship shot at a position exceeding the game map!" << endl;
            outputFile << "Wasted a shot! The Ship shot at a position exceeding the game map!" << endl;
            return;
        }

        if (game_map[target_x][target_y] != '0' && game_map[target_x][target_y] != '1') {
            if (team == 'A') {
                for (int i = 0; i < TeamB[0]; i++) {
                    if (TeamB_symbols[i] == game_map[target_x][target_y]) {
                        // cout << TeamB_symbols[i] << endl;
                        // cout << game_map[target_x][target_y] << endl; 

                        kills++;
                        // cout << "Kill incremented" << endl;
                        kill(target_x, target_y);

                        //add promotion logic here?
                        //remember to change the ship symbol on the map
                        break;
                    } else {
                        cout << "Order cancelled! Almost shot at a friendly ship!" << endl;
                        outputFile << "Order cancelled! Almost shot at a friendly ship!" << endl;
                    }
                }
            } else {
                for (int i = 0; i < TeamA[0]; i++) {
                    if (TeamA_symbols[i] == game_map[target_x][target_y]) {
                        // cout << TeamA_symbols[i] << endl;
                        // cout << game_map[target_x][target_y] << endl; 

                        kills++;
                        // cout << "Kill incremented" << endl;
                        kill(target_x, target_y);
                        break;
                    } else {
                        cout << "Order cancelled! Almost shot at a friendly ship!" << endl;
                        outputFile << "Order cancelled! Almost shot at a friendly ship!" << endl;
                    }
                }
            }
        }

        if (game_map[target_x][target_y] == '0' || game_map[target_x][target_y] == '1') {
            cout << "Missed! No enemy ship at target location." << endl;
            outputFile << "Missed! No enemy ship at target location." << endl;
        }
    }

    void action_plan() override {
        shoot();

        if (kills > 3) {
            promotion();
        }
    }
    
};

#endif