#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <random>
#include "linkedlist.h"
#include "battleship.h"
#include "cruiser.h"
#include "destroyer.h"
#include "frigate.h"
#include "corvette.h"
#include "amphibious.h"
#include "supership.h"

using namespace std;

class Battlefield {
private:
    int* TeamA;
    int* TeamB;
    char* TeamA_symbols;
    char* TeamB_symbols;
    string* TeamA_classes;
    string* TeamB_classes;
    char** game_map;
    int no_ships;
    int* game_settings;
    int** symbol_map;
    ofstream* outputFile;

public:
    Battlefield(ofstream& outfile);

    void Print_Map();
    Linked_List<Ship*>* Initial_Ship_Placement();
    void Ship_Placement(Ship* respawning_ship);

    int* get_game_settings() const;
    int* get_TeamA() const;
    int* get_TeamB() const;
    char* get_TeamA_symbols() const;
    char* get_TeamB_symbols() const;
    string* get_TeamA_classes() const;
    string* get_TeamB_classes() const;
    char** get_game_map() const;
    int getno_ships() const;
    int** get_symbol_map() const;
};

#endif