#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <iomanip>

#include "ship_details.h"
#include "game_setup.h"
#include "battleship.h"

using namespace std;

class Look : public Ship {

};

class Destroy : public Ship {

};

int Ship::ship_count = 0;
Ship_Details* Game_Setup::Ships = nullptr;

void game_loop(int no_ships, Ship_Details* Ships) {
    for (int i = 0; i < no_ships; i++) {
        if (Ships[i].type == "Battleship") {
            cout << "————————————————————————————————————————————————" << endl;
            (Ships[i].ship_ptr)->action_plan();
        }

    }
}

int main() {
    Game_Setup setup;

    // int* game_settings = setup.get_game_settings();
    // int* TeamA = setup.get_TeamA();
    // int* TeamB = setup.get_TeamB();
    // char* TeamA_symbols = setup.get_TeamA_symbols();
    // char* TeamB_symbols = setup.get_TeamB_symbols();
    // string* TeamA_classes = setup.get_TeamA_classes();
    // string* TeamB_classes = setup.get_TeamB_classes();
    // char** game_map = setup.get_game_map();

    setup.Initial_Ship_Placement();

    //Ship ship;

    //ship.getShips();
    Ship_Details* Ships = setup.getShipDetails();
    //cout << Ships << endl;
    int no_ships = setup.getno_ships();

    setup.Create_Ship(Ships, no_ships);
    cout << "num ships " << no_ships << endl;

    game_loop(no_ships, Ships);

    //ship.getShips();
}