#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <iomanip>

#include "battlefield.h"
#include "linkedlist.cpp"

using namespace std;

int* Ship::game_settings = nullptr;
int Ship::ship_count = 0;
char** Ship::game_map = nullptr;
int* Ship::TeamA = nullptr;
int* Ship::TeamB = nullptr;
string* Ship::TeamA_classes = nullptr;
string* Ship::TeamB_classes = nullptr;
char* Ship::TeamA_symbols = nullptr;
char* Ship::TeamB_symbols = nullptr;
Linked_List<Ship*>* Ship::turn_queue = nullptr;
Linked_List<Ship*>* Ship::respawn_queue = nullptr;
char* Ship::default_teamA_symbols = nullptr;
char* Ship::default_teamB_symbols = nullptr; 

void game_loop(Battlefield* setup) {
    cout << "Another Game Loop" << endl;

    for (int i = 0; i < 2; i++) {
        if (Ship::respawn_queue->list_size() != 0) {
            Ship::turn_queue->push_back((*Ship::respawn_queue)[0]);
            cout << (*Ship::respawn_queue)[0] << endl;
            cout << (*Ship::respawn_queue)[0]->get_type() << endl;
            setup->Ship_Placement((*Ship::respawn_queue)[0]);
            cout << (*Ship::respawn_queue)[0]->get_x() << endl;
            cout << (*Ship::respawn_queue)[0]->get_y() << endl;
            Ship::respawn_queue->pop_front();
            cout << "Respawned" << endl;
            cout << Ship::respawn_queue->list_size() << endl;
        }
    }

    for (int i = 0; i < Ship::turn_queue->list_size(); i++) {
        cout << "————————————————————————————————————————————————" << endl;
        cout << "Turn: " << i << endl;
        cout << (*Ship::turn_queue)[i]->get_type() << endl;
        cout << "(" << (*Ship::turn_queue)[i]->get_x()+ 1<< ", " << (*Ship::turn_queue)[i]->get_y()+1 << ")" << endl;
        (*Ship::turn_queue)[i]->action_plan();
        setup->Print_Map();
    }

    Ship::respawn_queue->display();
    cin.get();
}

// game loop order
// 1. action plans according to the turn order linked list
// 2. resurrection (this might happen first but we can change that later)
// 3. iterate turn by 1

int main() {
    Battlefield setup;


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
    Ship::TeamA = setup.get_TeamA();
    Ship::TeamB = setup.get_TeamA();
    Ship::TeamA_classes = setup.get_TeamA_classes();
    Ship::TeamB_classes = setup.get_TeamB_classes();
    Ship::TeamA_symbols = setup.get_TeamA_symbols();
    Ship::TeamB_symbols = setup.get_TeamB_symbols();

    Ship::default_teamA_symbols = new char[7]; // {"å", "ß", "ö", "Å", "◊", "Ö", "∑"};
    Ship::default_teamB_symbols = new char[7]; // {"∆", "∫", "µ", "√", "ç", "Ω", "æ"};
    
    {
        string tempA = "QWERTYU";
        string tempB = "ASDFGHJ";
        // From left to right: Battleship, Cruiser, Destroyer, Frigate, Corvette, Amphibious, SuperShip

        for (int i = 0; i < 7; i++) {
            Ship::default_teamA_symbols[i] = tempA[i];
            Ship::default_teamB_symbols[i] = tempB[i];
        }
    }
    cout << Ship::turn_queue->list_size() << endl;

    cin.get();

    cout << Ship::game_map << endl;

    for (int i = 0; i < Ship::game_settings[0]; i++) {
        cout << "Loop number: " << i << endl;
        game_loop(&setup);
    }
    
}