#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <fstream>
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
int** Ship::symbol_map = nullptr;
ofstream Ship::outputFile("/Users/jordan/Desktop/Live_Projects/OOPDS_Assignment/output.txt");

void game_loop(Battlefield* setup) {
    cout << "Respawning..." << endl;
    Ship::outputFile << "Respawning..." << endl;  
    
    for (int i = 0; i < 2; i++) {
        if (Ship::respawn_queue->list_size() != 0) {
            Ship::turn_queue->push_back((*Ship::respawn_queue)[0]);
            // cout << (*Ship::respawn_queue)[0] << endl;
            // cout << (*Ship::respawn_queue)[0]->get_type() << endl;
            setup->Ship_Placement((*Ship::respawn_queue)[0]);
            (*Ship::respawn_queue)[0]->set_status("Deployed");
            
            // cout << (*Ship::respawn_queue)[0]->get_x() << endl;
            // cout << (*Ship::respawn_queue)[0]->get_y() << endl;
            cout << (*Ship::respawn_queue)[0]->get_type() << " with id: " << (*Ship::respawn_queue)[0]->get_id() 
                 << " Respawned at position (" << (*Ship::respawn_queue)[0]->get_x() << ", " << 
                 (*Ship::respawn_queue)[0]->get_y() << ")" << endl;
            Ship::outputFile << (*Ship::respawn_queue)[0]->get_type() << " with id: " << (*Ship::respawn_queue)[0]->get_id() 
                       << " Respawned at position (" << (*Ship::respawn_queue)[0]->get_x() << ", " << 
                       (*Ship::respawn_queue)[0]->get_y() << ")" << endl;  

            Ship::respawn_queue->pop_front();
            // cout << Ship::respawn_queue->list_size() << endl;
            // Ship::outputFile << Ship::respawn_queue->list_size() << endl;  
        }
    }

    for (int i = 0; i < Ship::turn_queue->list_size(); i++) {
        cout << endl;
        Ship::outputFile << endl;  
        
        cout << "It is " << (*Ship::turn_queue)[i]->get_type() << ", with id: " << 
            (*Ship::turn_queue)[i]->get_id() << "'s turn!" << endl;
        Ship::outputFile << "It is " << (*Ship::turn_queue)[i]->get_type() << ", with id: " << 
            (*Ship::turn_queue)[i]->get_id() << "'s turn!" << endl;  
        
        (*Ship::turn_queue)[i]->action_plan();
        setup->Print_Map();
    }

    Ship::respawn_queue->display();
    cout << "Ships in the resurrection queue: ";
    Ship::outputFile << "Ships in the resurrection queue: ";  

    if (!Ship::respawn_queue || Ship::respawn_queue->empty()) {
        cout << "Resurrection queue is empty." << endl;
        Ship::outputFile << "Resurrection queue is empty." << endl;  
        return;
    }

    cout << "\nResurrection Queue:\n";
    Ship::outputFile << "\nResurrection Queue:\n";  
    cout << "+----+-------+------------+--------+-------+" << endl;
    Ship::outputFile << "+----+-------+------------+--------+-------+" << endl;  
    cout << "| ID | Team  |    Type    | Symbol | Lives |" << endl;
    Ship::outputFile << "| ID | Team  |    Type    | Symbol | Lives |" << endl;  
    cout << "+----+-------+------------+--------+-------+" << endl;
    Ship::outputFile << "+----+-------+------------+--------+-------+" << endl;  

    for (int i = 0; i < Ship::respawn_queue->list_size(); i++) {
        Ship* ship = (*Ship::respawn_queue)[i]; // Access the ship at index i

        if (ship) {
            cout << "| " << setw(2) << ship->get_id()
                 << " |  " << setw(4) << ship->get_team()
                 << " | " << setw(11) << ship->get_type()
                 << " |   " << setw(2) << ship->get_symbol()
                 << " | " << setw(5) << ship->get_lives() << " |" << endl;
            Ship::outputFile << "| " << setw(2) << ship->get_id()
                       << " |  " << setw(4) << ship->get_team()
                       << " | " << setw(11) << ship->get_type()
                       << " |   " << setw(2) << ship->get_symbol()
                       << " | " << setw(5) << ship->get_lives() << " |" << endl;  
        }
    }

    cout << "+----+------+-------------+--------+-------+" << endl;
    Ship::outputFile << "+----+------+-------------+--------+-------+" << endl;  

    cin.get();
}

// game loop order
// 1. action plans according to the turn order linked list
// 2. resurrection (this might happen first but we can change that later)
// 3. iterate turn by 1

int main() {
    Battlefield setup;

    Ship::turn_queue = setup.Initial_Ship_Placement();
    Ship::respawn_queue = new Linked_List<Ship*>;
    cout << endl;
    Ship::outputFile << endl;  
    // Ship::turn_queue->display();
    // Ship::outputFile << "Turn queue displayed." << endl;  

    Ship::game_settings = setup.get_game_settings();
    Ship::game_map = setup.get_game_map();
    Ship::TeamA = setup.get_TeamA();
    Ship::TeamB = setup.get_TeamB();
    Ship::TeamA_classes = setup.get_TeamA_classes();
    Ship::TeamB_classes = setup.get_TeamB_classes();
    Ship::TeamA_symbols = setup.get_TeamA_symbols();
    Ship::TeamB_symbols = setup.get_TeamB_symbols();
    Ship::symbol_map = setup.get_symbol_map();

    Ship::default_teamA_symbols = new char[7];
    Ship::default_teamB_symbols = new char[7];
    
    {
        string tempA = "QWERTYU";
        string tempB = "ASDFGHJ";
        // From left to right: Battleship, Cruiser, Destroyer, Frigate, Corvette, Amphibious, SuperShip

        for (int i = 0; i < 7; i++) {
            Ship::default_teamA_symbols[i] = tempA[i];
            Ship::default_teamB_symbols[i] = tempB[i];
        }
    }
    // cout << Ship::turn_queue->list_size() << endl;
    // Ship::outputFile << Ship::turn_queue->list_size() << endl;  

    cin.get();

    cout << Ship::game_map << endl;
    Ship::outputFile << Ship::game_map << endl;  

    for (int i = 0; i < Ship::game_settings[0]; i++) {
        cout << endl;
        Ship::outputFile << endl;  
        cout << "_________________________________________________________________" << endl;
        Ship::outputFile << "_________________________________________________________________" << endl;  
        cout << "Loop number: " << i << endl;
        Ship::outputFile << "Loop number: " << i << endl;
        game_loop(&setup);

        int TeamA_counter = 0;
        int TeamB_counter = 0;

        for (int i = 0; i < Ship::turn_queue->list_size(); i++) {
            if ((*Ship::turn_queue)[i]->get_team() == 'A') {
                TeamA_counter++;
            } else {
                TeamB_counter++;
            }
        }
        for (int i = 0; i < Ship::respawn_queue->list_size(); i++) {
            if ((*Ship::respawn_queue)[i]->get_team() == 'A') {
                TeamA_counter++;
            } else {
                TeamB_counter++;
            }
        }

        if (TeamA_counter == 0) {
            cout << "Team B has Won the Game after a great struggle lasting " << i << " turns!" << endl;
            Ship::outputFile << "Team B has Won the Game after a great struggle lasting " << i << " turns!" << endl;  
            break;
        } else if (TeamB_counter == 0) {
            cout << "Team A has Won the Game after a bloody war lasting " << i << " turns!" << endl;
            Ship::outputFile << "Team A has Won the Game after a bloody war lasting " << i << " turns!" << endl;  
            break;
        }

        if (i == Ship::game_settings[0] - 1) {
            cout << "It's a tie!" << endl;
            Ship::outputFile << "It's a tie!" << endl;
        }
    }

    for (int i = 0; i < Ship::turn_queue->list_size(); i++) {
        delete (*Ship::turn_queue)[i];
    }
    for (int i = 0; i < Ship::respawn_queue->list_size(); i++) {
        delete (*Ship::respawn_queue)[i];
    }

    Ship::cleanup();
}
