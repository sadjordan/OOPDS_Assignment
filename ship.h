#ifndef SHIP_H
#define SHIP_H

#include <iostream>
using namespace std;

#include "battleship.h"

class Ship {
private:
    Ship_Details* Ships;
    int no_ships;

public:
    Ship() {
        cout << "Ship Created" << endl;
    }

    Ship(int* game_settings, char** game_map, int* TeamA, int* TeamB, char* TeamA_symbols, char* TeamB_symbols, string* TeamA_classes, string* TeamB_classes) {
        //char symbols[] = {'*', '$', '#', '@', '&', '~'};
        int x, y, ship_counter = 0;

        no_ships = 0;

        for (int i = 1; i < TeamA[0] + 1; i++) {
            no_ships += TeamA[i];
        }

        for (int i = 1; i < TeamB[0] + 1; i++) {
            no_ships += TeamB[i];
        }

        Ships = new Ship_Details[no_ships];

        random_device rd;
        mt19937 gen(rd());

        //debug stuff
        //int symbols_placed[] = {0, 0, 0, 0, 0, 0};

        for (int i = 1; i < TeamA[0] + 1; i++) {
            uniform_int_distribution<> x_dis(0, game_settings[1] - 1);
            uniform_int_distribution<> y_dis(0, game_settings[2] - 1);

            while (TeamA[i]-- > 0) {
                
                do {
                    x = x_dis(gen);
                    y = y_dis(gen);
                } while(game_map[x][y] != '0'); // prevents placement on islands/ occupied coords
                
                Ships[ship_counter].id = ship_counter + 1;
                Ships[ship_counter].team = 'A';
                Ships[ship_counter].type = TeamA_classes[i - 1];
                Ships[ship_counter].symbol = TeamA_symbols[i - 1];
                Ships[ship_counter].x = x;
                Ships[ship_counter].y = y;
                Ships[ship_counter].status = "Placed";
                Ships[ship_counter].lives = 3;
                Ships[ship_counter].kills = 0;
                
                game_map[x][y] = TeamA_symbols[i - 1];
                
                //symbols_placed[i]++;
                cout << "Placed " << TeamA_symbols[i - 1] << " at (" << x + 1 << ", " << y + 1 << ")" << endl;

                cout << "   "; //col headers
                for (int j = 1; j <= game_settings[2]; j++) {
                    cout << " " << setw(3) << j;
                }
                cout << endl;

                for (int i = 0; i < game_settings[1]; i++) {
                    cout << "    ";
                    for (int j = 0; j < game_settings[2]; j++) {
                        cout << "+---";
                    }
                    cout << "+" << endl;

                    cout << setw(3) << i + 1 << " ";
                    for (int j = 0; j < game_settings[2]; j++) {
                        cout << "| " << game_map[i][j] << " ";
                    }
                    cout << "|" << endl;
                }

                cout << "    "; // final row stuff
                for (int j = 0; j < game_settings[2]; j++) {
                    cout << "+---";
                }
                cout << "+" << endl;

                //for (auto i : symbols_placed) {
                //   cout << i << endl;
                //}
                ship_counter++;
            }
        }

        for (int i = 1; i < TeamB[0] + 1; i++) {
            uniform_int_distribution<> x_dis(0, game_settings[1] - 1);
            uniform_int_distribution<> y_dis(0, game_settings[2] - 1);

            while (TeamB[i]-- > 0) {
                
                do {
                    x = x_dis(gen);
                    y = y_dis(gen);
                } while(game_map[x][y] != '0'); // prevents placement on islands/ occupied coords
                game_map[x][y] = TeamB_symbols[i - 1];

                Ships[ship_counter].id = ship_counter + 1;
                Ships[ship_counter].team = 'B';
                Ships[ship_counter].type = TeamB_classes[i - 1];
                Ships[ship_counter].symbol = TeamB_symbols[i - 1];
                Ships[ship_counter].x = x;
                Ships[ship_counter].y = y;
                Ships[ship_counter].status = "Placed";
                Ships[ship_counter].lives = 3;
                Ships[ship_counter].kills = 0;
                
                //symbols_placed[i]++;
                cout << "Placed " << TeamB_symbols[i - 1] << " at (" << x + 1 << ", " << y + 1 << ")" << endl;

                cout << "   "; //col headers
                for (int j = 1; j <= game_settings[2]; j++) {
                    cout << " " << setw(3) << j;
                }
                cout << endl;

                for (int i = 0; i < game_settings[1]; i++) {
                    cout << "    ";
                    for (int j = 0; j < game_settings[2]; j++) {
                        cout << "+---";
                    }
                    cout << "+" << endl;

                    cout << setw(3) << i + 1 << " ";
                    for (int j = 0; j < game_settings[2]; j++) {
                        cout << "| " << game_map[i][j] << " ";
                    }
                    cout << "|" << endl;
                }

                cout << "    "; // final row stuff
                for (int j = 0; j < game_settings[2]; j++) {
                    cout << "+---";
                }
                cout << "+" << endl;

                //for (auto i : symbols_placed) {
                //   cout << i << endl;
                //}
                ship_counter++;
            }
        }

        //for (int i = 0; i < ship_counter; i++) {
        //    cout << Ships[i].id  << " " << Ships[i].team  << " " << Ships[i].type << " "  << Ships[i].symbol << " " << Ships[i].x << " " << Ships[i].y << endl;
        //}
        
        //cout << ship_counter << endl;
    }

    void getShips() {
        for (int i = 0; i < no_ships; i++) {
            cout << i << ": " << "ID: " << Ships[i].id << ", Pointer: " << Ships[i].ship_ptr << ", Team: " << Ships[i].team << ", Type: " << Ships[i].type << ", Symbol: " << Ships[i].symbol << ", Position: (" << Ships[i].x << ", " << Ships[i].y << "), Status: " << Ships[i].status << ", Lives: " << Ships[i].lives << ", Kills: " << Ships[i].kills << endl;
            }
        }

    Ship_Details* getShipDetails() {
        return Ships;
    }

    int getno_ships() {
        return no_ships;
    }
};

#endif