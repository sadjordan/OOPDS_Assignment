#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <iomanip>

#include "game_setup.h"
#include "linkedlist.cpp"

using namespace std;

int* Ship::game_settings = nullptr;
int Ship::ship_count = 0;
char** Ship::game_map = nullptr;
char* Ship::TeamA_symbols = nullptr;
char* Ship::TeamB_symbols = nullptr;
Linked_List<Ship*>* Ship::turn_queue = nullptr;
Linked_List<Ship*>* Ship::respawn_queue = nullptr;

class Look : public Ship {

};

class Destroy : public Ship {

};

void game_loop(Game_Setup* setup) {
    for (int i = 0; i < 2; i++) {
        if (Ship::respawn_queue->list_size() == 0) {
            break;
        } else {
            Ship::turn_queue->push_back((*Ship::respawn_queue)[0]);
            cout << (*Ship::respawn_queue)[0] << endl;
            Ship::respawn_queue->pop_front();
            cout << "Respawned" << endl;
        }
    }

    for (int i = 0; i < Ship::turn_queue->list_size(); i++) {
        cout << "————————————————————————————————————————————————" << endl;
        cout << i << endl;
        (*Ship::turn_queue)[i]->action_plan();
        setup->Print_Map();
    }

    // return 0 - completed without any events
    // return (coordinates) - destroyed another ship(s)

    cin.get();
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
    Ship::turn_queue = setup.Initial_Ship_Placement();
    Ship::respawn_queue = new Linked_List<Ship*>;
    cout<<endl;
    Ship::turn_queue->display();

    Ship::game_settings = setup.get_game_settings();
    Ship::game_map = setup.get_game_map();
    Ship::TeamA_symbols = setup.get_TeamA_symbols();
    Ship::TeamB_symbols = setup.get_TeamB_symbols();

    cout << Ship::turn_queue->list_size() << endl;
    game_loop(&setup);
}