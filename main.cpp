#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>

using namespace std;

class Game_Setup {
public:
    Game_Setup() {
        ifstream file("/Users/jordan/Desktop/OOPDS_Assignment/game.txt");

        int* game_settings = new int[3];
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
        int* TeamA = new int[size_a];

        file.clear();
        file.seekg(0, ios::beg);
        for (int i = 0; i < counter; i++) {
            getline(file, line);
        } 

        while (getline(file, line) && counter < 4 + size_a + 1) {
            cout << counter << endl;

            istringstream iss(line);
            string word;
            int value;

            while (iss >> word && counter < 4 + size_a) {
                istringstream wordStream(word);
                if (wordStream >> value) {
                    TeamA[counter - 4] = value;
                    cout << "value: " << value << endl;
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

        for (int i = 0; i < size_a; i++) {
            cout << i << ": " << TeamA[i] << endl;
        }

        //team b
        int* TeamB = new int[size_b];

        file.clear();
        file.seekg(0, ios::beg);
        for (int i = 0; i < counter; i++) {
            getline(file, line);
        } 


        while (getline(file, line) && counter < 4 + size_a + size_b + 1) {
            cout << counter << endl;

            istringstream iss(line);
            string word;
            int value;

            while (iss >> word) {
                istringstream wordStream(word);
                if (wordStream >> value) {
                    TeamB[counter - 5 - size_a] = value;
                    cout << "value: " << value << endl;
                }
            }
            counter++;
        }

        for (int i = 0; i < size_b; i++) {
            cout << i << ": " << TeamB[i] << endl;
        }


        int rows = game_settings[1], columns = game_settings[2];
        char** game_map = new char*[rows];
        for (int i = 0; i < rows; ++i) {
            game_map[i] = new char[columns]();
        }

        // fixed the first line not appearing
        // map processing
        file.clear();
        file.seekg(0, ios::beg);
        for (int i = 0; i < counter; i++) {
            getline(file, line);
        }

        counter = 0;
        while(getline(file, line)) {
            cout << counter << endl;


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

        for (int i = 0; i < game_settings[1]; i++) {
            for (int j = 0; j < game_settings[2]; j++) {
                cout << game_map[i][j] << " ";
            }
            cout << endl;
        }
        random_placement(game_settings, game_map);
    }

    void random_placement(int* game_settings, char** game_map) {
    char symbols[] = {'*', '$', '#', '@', '&', '~'};
    int x, y;

    random_device rd;
    mt19937 gen(rd());

    //debug stuff
    //int symbols_placed[] = {0, 0, 0, 0, 0, 0};

    for (int i = 3; i < 9; i++) {
        uniform_int_distribution<> x_dis(0, game_settings[1] - 1);
        uniform_int_distribution<> y_dis(0, game_settings[2] - 1);

        while (game_settings[i]-- > 0) {
            
            do {
                x = x_dis(gen);
                y = y_dis(gen);
            } while(game_map[x][y] != '0');
            game_map[x][y] = symbols[i - 3];
            
            //symbols_placed[i-3]++;
            cout << "Placed " << symbols[i - 3] << " at (" << x + 1 << ", " << y + 1 << ")" << endl;

            for (int i = 0; i < game_settings[1]; ++i) {
                for (int j = 0; j < game_settings[2]; ++j) {
                    cout << game_map[i][j] << " ";
                }
                cout << endl;
            }

            //for (auto i : symbols_placed) {
            //   cout << i << endl;
            //}
        }
    }
}
};

int main() {
    Game_Setup setup;
}