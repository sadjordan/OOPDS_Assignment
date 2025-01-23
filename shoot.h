#ifndef SHOOT_H
#define SHOOT_H

#include <iostream>
#include <random>
#include "ship.h"
#include "ship_details.h"

class Shoot : virtual public Ship {  // INHERITANCE: Shoot inherits from the base class Ship
private:

public:
    // Constructor
    Shoot() {
    }

    // Shoot function
    void shoot() {
        // POLYMORPHISM: This function can be overridden by derived classes if needed.

        // Directions for shooting: up, down, left, right, and diagonals
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

        if (game_map[target_x][target_y] != '0' && game_map[target_x][target_y] != '1') {
            if (team == 'A') {
                for (int i = 1; i < TeamA_symbols[0] + 1; i++) {
                    if (TeamA_symbols[i] != game_map[target_x][target_y]) {
                        return;
                    }
                }
            } else {
                for (int i = 1; i < TeamB_symbols[0] + 1; i++) {
                    if (TeamB_symbols[i] != game_map[target_x][target_y]) {
                        return;
                    }
                }
            }
        }

        // // Check if the target is in the area of the map
        // if (target_x < 0 || target_x >= game_settings[1] || target_y < 0 || target_y >= game_settings[2]) {
        //     cout << "Shot at position exceeding game map!" << endl;
        //     return;
        // }

        // this check the other boat is enemy or from the same team
        // char target_symbol = game_map[target_x][target_y];
        // if (target_symbol != '0' && target_symbol != '1') {
        //     for (int i = 0; i < no_ships; i++) {
        //         if (x == target_x && y == target_y) {
        //             if (team == Ships[ship_id - 1].team) {
        //                 cout << "Friendly position! Shoot order cancelled" << endl;
        //             }
        //         }
        //     }
        // }

        // // If the target is an enemy ship, reduce its lives
        // for (int i = 0; i < no_ships; i++) {
        //     if (x == target_x && y == target_y) {
        //         if (team != Ships[ship_id - 1].team) {
        //             lives--;  // ENCAPSULATION: Modifying private data member of Ship_Details
        //             cout << "Enemy ship hit! Remaining lives: " << lives << endl;
        // 
        //             // if (lives == 0) {
        //             //     status = "Destroyed";  // ENCAPSULATION: Modifying private data member
        //             //     game_map[target_x][target_y] = '0';  // Remove the destroyed ship from the map
        //             //     cout << "Enemy ship destroyed!" << endl;
        //             // }
        //             return;
        //         }
        //     }
        // }

        if (game_map[target_x][target_y] == '0' || game_map[target_x][target_y] == '1') {
            cout << "Missed! No enemy ship at target location." << endl;
        }
    }
};

#endif