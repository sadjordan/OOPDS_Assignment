#ifndef MOVE_H
#define MOVE_H

#include <random>
#include <iostream>

#include "game_setup.h"

using namespace std;

class Move : virtual public Ship {
private:

public:
    // Constructor if needed
    // Move(Ship_Details* Ships) {
    //     this->Ships = Ships;
    // }

    void move() {
        random_device rd;
        mt19937 gen(rd());

        // cout << "Move ship id: " << ship_id - 1 << endl;
        cout << type << endl;

        uniform_int_distribution<> movement_decider(1, 4);
        int anumber;
        bool valid_move = false;

        // Backup position before move
        int old_x = x;
        int old_y = y;

        // Keep trying until a valid move is found
        while (!valid_move) {
            anumber = movement_decider(gen);  // Generate a new random move

            switch (anumber) {
            case 1: // Up
                if (y + 1 < game_settings[2]) {
                    cout << "(" << x << ", " << y << ")" << endl;
                    cout << "Up" << endl;
                    game_map[x][y] = '0';  // Clear old position
                    y++;
                    game_map[x][y] = symbol;  // Set new position
                    valid_move = true;
                } else {
                    cout << "Invalid move Up, out of bounds. Retrying..." << endl;
                }
                break;
            case 2: // Down
                if (y - 1 >= 0) {
                    cout << "(" << x << ", " << y << ")" << endl;
                    cout << "Down" << endl;
                    game_map[x][y] = '0';
                    y--;
                    game_map[x][y] = symbol;
                    valid_move = true;
                } else {
                    cout << "Invalid move Down, out of bounds. Retrying..." << endl;
                }
                break;
            case 3: // Left
                if (x - 1 >= 0) {
                    cout << "(" << x << ", " << y << ")" << endl;
                    cout << "Left" << endl;
                    game_map[x][y] = '0';
                    x--;
                    game_map[x][y] = symbol;
                    valid_move = true;
                } else {
                    cout << "Invalid move Left, out of bounds. Retrying..." << endl;
                }
                break;
            case 4: // Right
                if (x + 1 < game_settings[1]) {
                    cout << "(" << x << ", " << y << ")" << endl;
                    cout << "Right" << endl;
                    game_map[x][y] = '0';
                    x++;
                    game_map[x][y] = symbol;
                    valid_move = true;
                } else {
                    cout << "Invalid move Right, out of bounds. Retrying..." << endl;
                }
                break;
            default:
                cout << "Technically impossible so if you see this the world must be ending" << endl;
                break;
            }
        }

        // If the ship's position has changed, we moved successfully
        if (x != old_x || y != old_y) {
            cout << "Movement successful!" << endl;
        }

        cout << "Move end" << endl;
    }
};

#endif
