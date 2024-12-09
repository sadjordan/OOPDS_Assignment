#include <iostream>
#include <fstream>
#include <string>

using namespace std;




int main() {
    ifstream file("game.txt");

    if (!file.is_open()) {
        cout << "File was unable to be opened, ensure you are in the correct directory/ the file exists." << endl;
        return 1;
    } else {
        cout << "File is open!" << endl;
    }

    int iterations, width, height, battleships, cruisers, destroyers, frigates, corvettes, amphbious;
    int counter = 0;
    string line;

    while (getline(file, line)) {
        cout << line << endl;

        counter++;
    }
}