#ifndef GAME_SETUP_H
#define GAME_SETUP_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <random>
#include "ship_details.h"
#include "battleship.h"

class Game_Setup {
private:
    int* game_settings;
    int* TeamA;
    int* TeamB;
    char* TeamA_symbols;
    char* TeamB_symbols;
    string* TeamA_classes;
    string* TeamB_classes;
    char** game_map;
    static Ship_Details* Ships;
    int no_ships;

public:
    Game_Setup() {
        ifstream file("/Users/jordan/Desktop/Live_Projects/OOPDS_Assignment/game.txt");

        game_settings = new int[3];
        int size_a, size_b;
        int counter = 0;
        string line;

        // initial game settings
        while (getline(file, line) && counter < 4) {
            //cout << counter << endl;

            istringstream iss(line);
            string word;
            int value;

            while (iss >> word && counter < 3) {
                istringstream wordStream(word);
                if (wordStream >> value) {
                    game_settings[counter] = value;
                }
            }

            while (iss >> word && counter == 3) {
                istringstream wordStream(word);
                if (wordStream >> value) {
                    size_a = value; // saves the number of ship types team a has
                }
            }

            counter++;
        }

        // team A
        TeamA = new int[size_a + 1];
        TeamA_symbols = new char[size_a];
        TeamA_classes = new string[size_a];
        TeamA[0] = size_a;

        file.clear();
        file.seekg(0, ios::beg);
        for (int i = 0; i < counter; i++) {
            getline(file, line);
        } 

        while (getline(file, line) && counter < 4 + size_a + 1) {
            //cout << counter << endl;

            istringstream iss(line);
            string word;
            string name;
            int value;

            while (iss >> word && counter < 4 + size_a) {
                istringstream wordStream(word);
                if (wordStream >> value) {
                    TeamA[counter - 3] = value;
                    //cout << "value: " << value << endl;
                }

                if (word.size() == 1 && !isdigit(word[0])) {
                    TeamA_symbols[counter - 4] = word[0];
                    //cout << word[0] << endl;
                }

                if (word.size() > 1 && !isdigit(word[0])) {
                    TeamA_classes[counter - 4] = word;
                }
            }

            while (iss >> word && counter == 4 + size_a) {
                istringstream wordStream(word);
                if (wordStream >> value) {
                    size_b = value;
                }
            }
            counter++;
        }

       /* for (int i = 0; i < size_a + 1; i++) {
            cout << i << ": " << TeamA[i] << endl;
        }

        for (int i = 0; i < TeamA[0]; i++) {
            cout << i << ": " << TeamA_symbols[i] << endl;
        }

        for (int i = 0; i < TeamA[0]; i++) {
            cout << i << ": " << TeamA_classes[i] << endl;
        } */

        //team b
        TeamB = new int[size_b + 1];
        TeamB_symbols = new char[size_b];
        TeamB_classes = new string[size_a];
        TeamB[0] = size_b;

        file.clear();
        file.seekg(0, ios::beg);
        for (int i = 0; i < counter; i++) {
            getline(file, line);
        } 


        while (getline(file, line) && counter < 4 + size_a + size_b + 1) {
            //cout << counter << endl;

            istringstream iss(line);
            string word;
            int value;

            while (iss >> word) {
                istringstream wordStream(word);
                if (wordStream >> value) {
                    TeamB[counter - 4 - size_a] = value;
                    //cout << "value: " << value << endl;
                }

                if (word.size() == 1 && !isdigit(word[0])) {
                    TeamB_symbols[counter - 5 - size_a] = word[0];
                    //cout << word[0] << endl;
                }

                if (word.size() > 1 && !isdigit(word[0])) {
                    TeamB_classes[counter - 5 - size_a] = word;
                }
            }
            counter++;
        }

        /* for (int i = 0; i < TeamB[0] + 1; i++) {
            cout << i << ": " << TeamB[i] << endl;
        }

        for (int i = 0; i < TeamB[0]; i++) {
            cout << i << ": " << TeamB_symbols[i] << endl;
        }

        for (int i = 0; i < TeamB[0]; i++) {
            cout << i << ": " << TeamB_classes[i] << endl;
        } */

        int rows = game_settings[1], columns = game_settings[2];
        game_map = new char*[rows];
        for (int i = 0; i < rows; ++i) {
            game_map[i] = new char[columns]();
        } //2d dynamically allocated arrauy

        // fixed the first line not appearing
        // map processing
        file.clear();
        file.seekg(0, ios::beg);
        for (int i = 0; i < counter; i++) {
            getline(file, line);
        }

        counter = 0;
        while(getline(file, line)) {
            //cout << counter << endl;


            istringstream iss(line);
            int value;
            int internal_counter = 0;
            while (iss >> value) {
                char temp = value + '0';
                game_map[counter][internal_counter] = temp;

                //cout << internal_counter << endl;
                internal_counter++;
            }
            counter++;
        }

        //for (int i = 0; i < 9; i++) {
        //    cout << game_settings[i] << endl;
        //}

        //cout << "setting 1: " << game_settings[1] << endl;
        //cout << "setting 2: " << game_settings[2] << endl;

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
    }

    ~Game_Setup() {
        cout << "Died" << endl;
    }

    void Initial_Ship_Placement() {
        //Random placement for the ships, initialises everything
        
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
                
                // Ships[ship_counter].id = ship_counter + 1;
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

                // Ships[ship_counter].id = ship_counter + 1;
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

    void Print_Map() {
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
    }

    int* get_game_settings() const { return game_settings; }
    int* get_TeamA() const { return TeamA; }
    int* get_TeamB() const { return TeamB; }
    char* get_TeamA_symbols() const { return TeamA_symbols; }
    char* get_TeamB_symbols() const { return TeamB_symbols; }
    string* get_TeamA_classes() const { return TeamA_classes; }
    string* get_TeamB_classes() const { return TeamB_classes; }
    char** get_game_map() const { return game_map; }
    int getno_ships() const { return no_ships;}
    Ship_Details* getShipDetails() const { return Ships; }

    void Create_Ship(Ship_Details* Ships, int no_ships) {
        cout << "Creating Ships" << endl;

        for (int i = 0; i < no_ships; i++) {
            if (Ships[i].type == "Battleship") {
                cout << "Detected" << endl;
                Ships[i].ship_ptr = new Battleship(game_map, Ships);
            }
        }
    }
    void getShips() {
        for (int i = 0; i < no_ships; i++) {
            cout << i << ": " << "Pointer: " << Ships[i].ship_ptr << ", Team: " << Ships[i].team << ", Type: " << Ships[i].type << ", Symbol: " << Ships[i].symbol << ", Position: (" << Ships[i].x << ", " << Ships[i].y << "), Status: " << Ships[i].status << ", Lives: " << Ships[i].lives << ", Kills: " << Ships[i].kills << endl;
            }
    }
};

#endif