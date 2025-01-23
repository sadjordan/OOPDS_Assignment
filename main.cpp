#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <iomanip>

#include "ship_details.h"
#include "game_setup.h"
#include "linkedlist.cpp"



using namespace std;

class Look : public Ship {

};

class Destroy : public Ship {

};

int Ship::ship_count = 0;
Ship_Details* Game_Setup::Ships = nullptr;

void game_loop(Linked_List<Ship*>* turn_queue, Game_Setup* setup) {
    for (int i = 0; i < turn_queue->list_size(); i++) {
        cout << "————————————————————————————————————————————————" << endl;
        cout << i << endl;
        (*turn_queue)[i]->action_plan();
        setup->Print_Map();
    }
}

// game loop order
// 1. action plans according to the turn order linked list
// 2. resurrection (this might happen first but we can change that later)
// 3. iterate turn by 1

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

    Linked_List<Ship*>* turn_queue;
    turn_queue = setup.Initial_Ship_Placement();
    setup.getShips();
    game_loop(turn_queue, &setup);

}