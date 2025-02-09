/***|***|****|
Program: amphibious.cpp
Course: Object Oriented Programming and Data Structures
Trimester: 2430
Name: Jordan Ling, Muhammad Izaan Khan Bin Mubarak, Selvasaachinn A/L Selvarasan, MONISH A/L MOORTHY 
ID: 241UC24151, 241UC2415K, 1211108941, 1211111608
Lecture Section: TC2L
Tutorial Section: TT5L
Email: jordan.ling.shen@student.mmu.edu.my, Muhammad.izaan.khan@student.mmu.edu.my,
        1211108941@student.mmu.edu.my, 1211111608@student.mmu.edu.my
Phone: 014-2286351, 016-7573174, 011-10872234, 011-54240624
***|***|****/

#include "amphibious.h"
using namespace std;


Amphibious::Amphibious() {
    cout << "Amphibious created!" << endl;
    outputFile << "Amphibious created!" << endl;
}

void Amphibious::promotion() {
    cout << "Amphibious has been promoted to SuperShip!" << endl;

    // cin.get();

    Ship* promoted_ship = new SuperShip;

    int replace_index = turn_queue->find_index(this);

    turn_queue->replace(replace_index, promoted_ship);

    promoted_ship->set_id(id);
    promoted_ship->set_x(x);
    promoted_ship->set_y(y);
    promoted_ship->set_team(team);
    promoted_ship->set_type("SuperShip");

    bool found_symbol = false;

    if (team == 'A') {
        for (int i = 0; i < TeamA[0]; i++) {
            if (TeamA_classes[i] == "SuperShip") {
                promoted_ship->set_symbol(TeamA_symbols[i]);
                found_symbol = true;
                break;
            }
        }
    } else {
        for (int i = 0; i < TeamB[0]; i++) {
            if (TeamB_classes[i] == "SuperShip") {
                promoted_ship->set_symbol(TeamB_symbols[i]);
                found_symbol = true;
                break;
            }
        }
    }

    if (found_symbol == false && team == 'A') {
        cout << "No symbol found for SuperShip. Using default symbol." << endl;
        promoted_ship->set_symbol(default_teamA_symbols[1]);
    } else if (found_symbol == false && team == 'B') {
        cout << "No symbol found for SuperShip. Using default symbol." << endl;
        promoted_ship->set_symbol(default_teamB_symbols[1]);
    }

    //promoted_ship->set_symbol('5');

    game_map[x][y] = promoted_ship->get_symbol();
    symbol_map[x][y] = promoted_ship->get_id();

    delete this;
}

void Amphibious::move() {
    random_device rd;
    mt19937 gen(rd());

    // cout << "Move ship id: " << ship_id - 1 << endl;
    // cout << type << endl;

    uniform_int_distribution<> movement_decider(1, 4);
    int anumber;
    bool valid_move = false;
    int counter = 0;

    int old_x = x;
    int old_y = y;

    while (!valid_move && counter < 12) {
        anumber = movement_decider(gen);
        // cout << "Test 1" << endl;
        // cout << "x: " << x << endl;
        // cout << "y: " << y << endl;
        // cout << game_map << endl;
        // cout << game_map[x][y + 1] << endl;

        switch (anumber) {
        case 1:
            if (y + 1 < game_settings[2] && game_map[x][y + 1] == '0') {
                game_map[x][y] = '0';
                symbol_map[x][y] = NULL;
                cout << "The " << type << " moved from (" << x+1 << ", " << y+1 << ") --> ";
                outputFile << "The " << type << " moved from (" << x+1 << ", " << y+1 << ") --> ";
                y++;
                cout << "(" << x+1 << ", " << y+1 << ")" << endl;
                outputFile << "(" << x+1 << ", " << y+1 << ")" << endl;
                game_map[x][y] = symbol;
                symbol_map[x][y] = id;
                valid_move = true;
            } else {
                counter++;
                // cout << "Invalid move Up, out of bounds. Retrying..." << endl;
            }
            break;
        case 2:
            if (y - 1 >= 0 && game_map[x][y - 1] == '0') {
                game_map[x][y] = '0';
                symbol_map[x][y] = NULL;
                cout << "The " << type << " moved from (" << x+1 << ", " << y+1 << ") --> ";
                outputFile << "The " << type << " moved from (" << x+1 << ", " << y+1 << ") --> ";
                y--;
                cout << "(" << x+1 << ", " << y+1 << ")" << endl;
                outputFile << "(" << x+1 << ", " << y+1 << ")" << endl;
                game_map[x][y] = symbol;
                symbol_map[x][y] = id;
                valid_move = true;
            } else {
                counter++;
                // cout << "Invalid move Down, out of bounds. Retrying..." << endl;
            }
            break;
        case 3:
            if (x - 1 >= 0 && game_map[x - 1][y] == '0') {
                game_map[x][y] = '0';
                symbol_map[x][y] = NULL;
                cout << "The " << type << " moved from (" << x+1 << ", " << y+1 << ") --> ";
                outputFile << "The " << type << " moved from (" << x+1 << ", " << y+1 << ") --> ";
                x--;
                cout << "(" << x+1 << ", " << y+1 << ")" << endl;
                outputFile << "(" << x+1 << ", " << y+1 << ")" << endl;
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
                cout << "The " << type << " moved from (" << x+1 << ", " << y+1 << ") --> ";
                outputFile << "The " << type << " moved from (" << x+1 << ", " << y+1 << ") --> ";
                x++;
                cout << "(" << x+1 << ", " << y+1 << ")" << endl;
                outputFile << "(" << x+1 << ", " << y+1 << ")" << endl;
                game_map[x][y] = symbol;
                symbol_map[x][y] = id;
                valid_move = true;
            } else {
                counter++;
                // cout << "Invalid move Right, out of bounds. Retrying..." << endl;
            }
            break;
        default:
            // cout << "Technically impossible so if you see this the world must be ending" << endl;
            break;
        }
    }

    // if (x != old_x || y != old_y) {
    //     cout << "Movement successful!" << endl;
    // }
    // cout << "(" << x + 1 << ", " << y + 1 << ")" << endl;

    // cout << "Move end" << endl;
}

void Amphibious::shoot()  {
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
                }
            }
        }
    }

    if (game_map[target_x][target_y] == '0' || game_map[target_x][target_y] == '1') {
        cout << "Missed! No enemy ship at target location." << endl;
        outputFile << "Missed! No enemy ship at target location." << endl;
    }
}

void Amphibious::action_plan() {
    move();
    shoot();
    shoot();

    if (kills > 4) {
        promotion();
    }
}