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
        outputFile << "Cruiser created!" << endl;
    }

    void promotion() {
        cout << "Cruiser has been promoted to Destroyer!" << endl;
        outputFile << "Cruiser has been promoted to Destroyer!" << endl;

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
            // cout << "No symbol found for Destroyer. Using default symbol." << endl;
            promoted_ship->set_symbol(default_teamA_symbols[1]);
        } else if (found_symbol == false && team == 'B') {
            // cout << "No symbol found for Destroyer. Using default symbol." << endl;
            promoted_ship->set_symbol(default_teamB_symbols[1]);
        }

        //promoted_ship->set_symbol('5');

        game_map[x][y] = promoted_ship->get_symbol();
        symbol_map[x][y] = promoted_ship->get_id();

        delete this;
    }

    void look() override {
        for (int i = 0; i < 8; i++) {
            if (x + directions[i][0] < 0 || x + directions[i][0] >= game_settings[1] || y + directions[i][1] < 0 || y + directions[i][1] >= game_settings[2]) {
                look_results[i] = '5';
            } else {
                // cout << "test" << endl;
                look_results[i] = game_map[x + directions[i][0]][y + directions[i][1]];
            }
        }

        cout << "Ship completed looking!" << endl;
        outputFile << "Ship completed looking!" << endl;

        // for (int i = 0; i < 8; i++) {
        //     // cout << "Look results " << i << " :" << look_results[i] << endl;
        // }
    }

    void move() override {
        target_acquired = false;

        //check for adjacent enemies
        for (int i = 0; i < 8; i++) {
            if (look_results[i] != '0' && look_results[i] != '1' && look_results[i] != '5') {
                if (i == 1 || i == 3 || i == 4 || i == 6) {
                    if (team == 'A') {
                        for (int j = 0; j < TeamB[0]; j++) {
                            if (look_results[i] == TeamB_symbols[j]) {
                                target[0] = x + directions[i][0];
                                target[1] = y + directions[i][1];
                                target_acquired = true;

                                cout << "Abstaining from moving" << endl;
                                outputFile << "Abstaining from moving" << endl;
                                //enemy is rihgt left ontop or below, abstain from moving
                                // cout << "abstaining" << endl;
                                return;

                                //Okay quick explanation time
                                //Basically what is happening is that the program is checking if a target 
                                //exists below, above, on the right or left of the ship
                                //If it does exist the ship will abstain from moving in order to
                                //attack it when it calls its destriy function
                                //the location of the target is stored in the private attribute
                                //"target" which will then be used by destroy to 'step' onto the enemy ship
                            }
                        }
                    } else {
                        for (int j = 0; j < TeamA[0]; j++) {
                            if (look_results[i] == TeamA_symbols[j]) {
                                target[0] = x + directions[i][0];
                                target[1] = y + directions[i][1];
                                target_acquired = true;
                                cout << "Abstaining from moving" << endl;
                                outputFile << "Abstaining from moving" << endl;
                                //enemy is rihgt left ontop or below, abstain from moving
                                // cout << "abstaining" << endl;
                                return;
                            }
                        }
                    }
                }
            }
        }

        // move towards eneym units if in one of the corners
        for (int i = 0; i < 8; i++) {
            if (look_results[i] != '0' && look_results[i] != '1' && look_results[i] != '5') {
                if (i == 0 || i == 2 || i == 5 || i == 7) {
                    if (team == 'A') {
                        for (int j = 0; j < TeamB[0]; j++) {
                            if (look_results[i] == TeamB_symbols[j]) {
                                int new_x = x + directions[i][0];
                                int new_y = y + directions[i][1];
                                if (game_map[new_x][y] == '0') {
                                    target[0] = x + directions[i][0];
                                    target[1] = y + directions[i][1];
                                    cout << "The " << type << " moved from (" << x << ", " << y << ") --> ";
                                    outputFile << "The " << type << " moved from (" << x << ", " << y << ") --> ";
                                    game_map[x][y] = '0';
                                    symbol_map[x][y] = NULL;
                                    x = new_x;
                                    game_map[x][y] = symbol;
                                    symbol_map[x][y] = id;
                                    cout << "(" << x << ", " << y << ")" << endl;;
                                    outputFile << "(" << x << ", " << y << ")" << endl;;
                                    target_acquired = true;
                                    // cout << "target acquired" << endl;
                                    return;
                                } else if (game_map[x][new_y] == '0') {
                                    target[0] = x + directions[i][0];
                                    target[1] = y + directions[i][1];
                                    cout << "The " << type << " moved from (" << x << ", " << y << ") --> ";
                                    outputFile << "The " << type << " moved from (" << x << ", " << y << ") --> ";
                                    game_map[x][y] = '0';
                                    symbol_map[x][y] = NULL;
                                    y = new_y;
                                    game_map[x][y] = symbol;
                                    symbol_map[x][y] = id;
                                    cout << "(" << x << ", " << y << ")" << endl;;
                                    outputFile << "(" << x << ", " << y << ")" << endl;;
                                    target_acquired = true;
                                    // cout << "target acquired" << endl;
                                    return;

                                    //mega complicated part (this is as short and efficient as I can make
                                    //it so just hear me out)
                                    //if an enemy ship is present in one of the corners (top left, top
                                    //right, bottom left, bottom right) the ship will move up, down
                                    // or wherever will get it closer to the enemy ship so it can 'step'
                                    //or 'ram' into it when it calls its destroy func
                                    //now because of how squares work there are 2 paths to the enemy ship,
                                    // both result in the same result if both paths are not blocked
                                    // if a path is blocked the program will detect this can try the
                                    //other path, hence why there are if statements checking for available
                                    //positions. 
                                    //now how it gets the coords for this position is by taking the look_results
                                    //and using the 'directions' array to check where the look function found
                                    // the enemy ship
                                    //since these corners have a one coordinate position difference on both
                                    // the x and y axis, there is no need for an undoable number of if statements
                                    //to implement this move algorithm (which was my initial plan until I used
                                    // a brain cell)
                                    // oh and x2 for checking for team-a ships
                                }
                            }
                        }
                    } else if (team == 'B') {
                        for (int j = 0; j < TeamB[0]; j++) {
                            if (look_results[i] == TeamB_symbols[j]) {
                                int new_x = x + directions[i][0];
                                int new_y = y + directions[i][1];
                                if (game_map[new_x][y] == '0') {
                                    target[0] = x + directions[i][0];
                                    target[1] = y + directions[i][1];
                                    cout << "The " << type << " moved from (" << x << ", " << y << ") --> ";
                                    outputFile << "The " << type << " moved from (" << x << ", " << y << ") --> ";
                                    game_map[x][y] = '0';
                                    symbol_map[x][y] = NULL;
                                    x = new_x;
                                    game_map[x][y] = symbol;
                                    symbol_map[x][y] = id;
                                    cout << "(" << x << ", " << y << ")" << endl;;
                                    outputFile << "(" << x << ", " << y << ")" << endl;;
                                    target_acquired = true;
                                    // cout << "target acquired" << endl;
                                    return;
                                } else if (game_map[x][new_y] == '0') {
                                    target[0] = x + directions[i][0];
                                    target[1] = y + directions[i][1];
                                    cout << "The " << type << " moved from (" << x << ", " << y << ") --> ";
                                    outputFile << "The " << type << " moved from (" << x << ", " << y << ") --> ";
                                    game_map[x][y] = '0';
                                    symbol_map[x][y] = NULL;
                                    y = new_y;
                                    game_map[x][y] = symbol;
                                    symbol_map[x][y] = id;
                                    cout << "(" << x << ", " << y << ")" << endl;;
                                    outputFile << "(" << x << ", " << y << ")" << endl;;
                                    target_acquired = true;
                                    // cout << "target acquired" << endl;
                                    return;
                                }
                                // if no valid paths, resort to random movement
                            }
                        }
                    }
                }
            }
        }

        // if no enemies are found by look or no valid paths exist, move randomly
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
            case 1:
                if (y + 1 < game_settings[2] && game_map[x][y + 1] == '0') {
                    game_map[x][y] = '0';
                    symbol_map[x][y] = NULL;
                    cout << "The " << type << " moved from (" << x << ", " << y << ") --> ";
                    outputFile << "The " << type << " moved from (" << x << ", " << y << ") --> ";
                    y++;
                    cout << "(" << x << ", " << y << ")" << endl;;
                    outputFile << "(" << x << ", " << y << ")" << endl;;
                    game_map[x][y] = symbol;
                    symbol_map[x][y] = id;
                    valid_move = true;
                } else {
                    counter++;
                }
                break;
            case 2:
                if (y - 1 >= 0 && game_map[x][y - 1] == '0') {
                    game_map[x][y] = '0';
                    symbol_map[x][y] = NULL;
                    cout << "The " << type << " moved from (" << x << ", " << y << ") --> ";
                    outputFile << "The " << type << " moved from (" << x << ", " << y << ") --> ";
                    y--;
                    cout << "(" << x << ", " << y << ")" << endl;;
                    outputFile << "(" << x << ", " << y << ")" << endl;;
                    game_map[x][y] = symbol;
                    symbol_map[x][y] = id;
                    valid_move = true;
                } else {
                    counter++;
                }
                break;
            case 3:
                if (x - 1 >= 0 && game_map[x - 1][y] == '0') {
                    game_map[x][y] = '0';
                    symbol_map[x][y] = NULL;
                    cout << "The " << type << " moved from (" << x << ", " << y << ") --> ";
                    outputFile << "The " << type << " moved from (" << x << ", " << y << ") --> ";
                    x--;
                    cout << "(" << x << ", " << y << ")" << endl;;
                    outputFile << "(" << x << ", " << y << ")" << endl;;
                    game_map[x][y] = symbol;
                    symbol_map[x][y] = id;
                    valid_move = true;
                } else {
                    counter++;
                }
                break;
            case 4:
                if (x + 1 < game_settings[1] && game_map[x + 1][y] == '0') {
                    game_map[x][y] = '0';
                    symbol_map[x][y] = NULL;
                    cout << "The " << type << " moved from (" << x << ", " << y << ") --> ";
                    outputFile << "The " << type << " moved from (" << x << ", " << y << ") --> ";
                    x++;
                    cout << "(" << x << ", " << y << ")" << endl;;
                    outputFile << "(" << x << ", " << y << ")" << endl;;
                    game_map[x][y] = symbol;
                    symbol_map[x][y] = id;
                    valid_move = true;
                } else {
                    counter++;
                }
                break;
            // default:
                // cout << "Technically impossible so if you see this the world must be ending" << endl;
                // break;
            }
        }
    }

    void destroy() override {
        //moving to destroy/ step/ ram/ whatever

        if (target_acquired == true) {
            game_map[x][y] = '0';
            symbol_map[x][y] = NULL;
            x = target[0];
            y = target[1];

            cout << "Ramming target at (" << x << " ," << y << " )!" << endl;
            outputFile << "Ramming target at (" << x << " ," << y << " )!" << endl;

        } else {
            return; // if theres no target the ship cannot destroy anything
        }
    
        for (int i = 0; i < turn_queue->list_size(); i++) {
            //checking which ship actually needs to die
            if ((*turn_queue)[i]->get_x() == x && (*turn_queue)[i]->get_y() == y && (*turn_queue)[i]->get_team() != team) {
                // cout << "Destroy function called!" << endl;
                ram((*turn_queue)[i]);
               
            }
        }

        game_map[x][y] = symbol;
        symbol_map[x][y] = id;
    }

    void action_plan() override {
        look();
        move();
        destroy();
        if (kills > 3) {
            promotion();
        }
        // cout << "(" << x << ", " << y << ")" << endl;
    }
    
};

#endif