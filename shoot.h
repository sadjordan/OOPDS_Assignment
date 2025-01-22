#ifndef SHOOT_H
#define SHOOT_H

#include <iostream>
#include <random>
#include "ship.h"
#include "ship_details.h"

class Shoot : public Ship {  // INHERITANCE: Shoot inherits from the base class Ship
private:
    char** game_map;        // ENCAPSULATION: Private data members to store game map
    Ship_Details* Ships;    // ENCAPSULATION: Private data member to store ship details
    int* game_settings;     // ENCAPSULATION: Private data member to store game settings

public:
    // Constructor
    Shoot(char** game_map, Ship_Details* Ships, int* game_settings) {
        this->game_map = game_map;
        this->Ships = Ships;
        this->game_settings = game_settings;
    }

    // Shoot function
    void shoot(int ship_id) {
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
        int target_x = Ships[ship_id - 1].x + directions[dir][0];
        int target_y = Ships[ship_id - 1].y + directions[dir][1];

        // Check if the target is in the area of the map
        if (target_x < 0 || target_x >= game_settings[1] || target_y < 0 || target_y >= game_settings[2]) {
            cout << "Shoot out of bounds!" << endl;
            return;
        }

        // Check if the target is not the ship's own position
        if (target_x == Ships[ship_id - 1].x && target_y == Ships[ship_id - 1].y) {
            cout << "Cannot shoot at own position!" << endl;
            return;
        }

        // this check the other boat is enemy or from the same team
        char target_symbol = game_map[target_x][target_y];
        if (target_symbol != '0' && target_symbol != '1') {
            for (int i = 0; i < no_ships; i++) {
                if (Ships[i].x == target_x && Ships[i].y == target_y) {
                    if (Ships[i].team == Ships[ship_id - 1].team) {
                        cout << "Cannot shoot at team member!" << endl;
                        return;
                    }
                }
            }
        }

        // If the target is an enemy ship, reduce its lives
        for (int i = 0; i < no_ships; i++) {
            if (Ships[i].x == target_x && Ships[i].y == target_y) {
                if (Ships[i].team != Ships[ship_id - 1].team) {
                    Ships[i].lives--;  // ENCAPSULATION: Modifying private data member of Ship_Details
                    cout << "Enemy ship hit! Remaining lives: " << Ships[i].lives << endl;

                    if (Ships[i].lives == 0) {
                        Ships[i].status = "Destroyed";  // ENCAPSULATION: Modifying private data member
                        game_map[target_x][target_y] = '0';  // Remove the destroyed ship from the map
                        cout << "Enemy ship destroyed!" << endl;
                    }
                    return;
                }
            }
        }

        // If the target is empty or an island, just print a message
        if (game_map[target_x][target_y] == '0' || game_map[target_x][target_y] == '1') {
            cout << "Missed! No enemy ship at target location." << endl;
        }
    }
};

#endif