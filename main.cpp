#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    ifstream file("/Users/jordan/Desktop/OOPDS_Assignment/game.txt");

    int game_settings[9];
    int counter = 0;
    string line;

    while (getline(file, line) && counter < 9) {

        istringstream iss(line);
        string word;
        int value;

        while (iss >> word && counter < 9) {
            istringstream wordStream(word);
            if (wordStream >> value) {
                game_settings[counter] = value;
            }
        }
        counter++;
    }

    int rows = game_settings[1], cols = game_settings[2];
    int** game_map = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        game_map[i] = new int[cols]();
    }

    //counter = 0;

    while(getline(file, line)) {
        //cout << counter << endl;
        istringstream iss(line);
        int value;
        int internal_counter = 0;
        while (iss >> value) {
            game_map[counter-8][internal_counter] = value;
            internal_counter++;
        }
        counter++;
    }

    //for (auto i: game_settings) {
    //    cout << i << endl;
    //}

    for (int i = 0; i < game_settings[1]; ++i) {
        for (int j = 0; j < game_settings[2]; ++j) {
            cout << game_map[i][j] << " ";
        }
        cout << endl;
    }
    
}