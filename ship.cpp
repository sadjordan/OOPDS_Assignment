#include "ship.h"
using namespace std;

void Ship::cleanup() {
    cout << "Cleaning up Ship static variables" << endl;
    outputFile << "Cleaning up Ship static variables" << endl;

    if (game_settings) {
        delete game_settings;
        cout << "Deleted game_settings" << endl;
        outputFile << "Deleted game_settings" << endl;
    }
    if (TeamA) {
        delete TeamA;
        cout << "Deleted TeamA" << endl;
        outputFile << "Deleted TeamA" << endl;
    }
    if (TeamB) {
        delete TeamB;
        cout << "Deleted TeamB" << endl;
        outputFile << "Deleted TeamB" << endl;
    }
    if (TeamA_classes) {
        delete TeamA_classes;
        cout << "Deleted TeamA_classes" << endl;
        outputFile << "Deleted TeamA_classes" << endl;
    }
    if (TeamB_classes) {
        delete TeamB_classes;
        cout << "Deleted TeamB_classes" << endl;
        outputFile << "Deleted TeamB_classes" << endl;
    }
    if (TeamA_symbols) {
        delete TeamA_symbols;
        cout << "Deleted TeamA_symbols" << endl;
        outputFile << "Deleted TeamA_symbols" << endl;
    }
    if (TeamB_symbols) {
        delete TeamB_symbols;
        cout << "Deleted TeamB_symbols" << endl;
        outputFile << "Deleted TeamB_symbols" << endl;
    }
    if (default_teamA_symbols) {
        delete default_teamA_symbols;
        cout << "Deleted default_teamA_symbols" << endl;
        outputFile << "Deleted default_teamA_symbols" << endl;
    }
    if (default_teamB_symbols) {
        delete default_teamB_symbols;
        cout << "Deleted default_teamB_symbols" << endl;
        outputFile << "Deleted default_teamB_symbols" << endl;
    }
    if (turn_queue) {
        delete turn_queue;
        cout << "Deleted turn_queue" << endl;
        outputFile << "Deleted turn_queue" << endl;
    }
    if (respawn_queue) {
        delete respawn_queue;
        cout << "Deleted respawn_queue" << endl;
        outputFile << "Deleted respawn_queue" << endl;
    }

    game_settings = nullptr;
    cout << "Set game_settings to nullptr" << endl;
    outputFile << "Set game_settings to nullptr" << endl;
    
    TeamA = nullptr;
    cout << "Set TeamA to nullptr" << endl;
    outputFile << "Set TeamA to nullptr" << endl;
    
    TeamB = nullptr;
    cout << "Set TeamB to nullptr" << endl;
    outputFile << "Set TeamB to nullptr" << endl;
    
    TeamA_classes = nullptr;
    cout << "Set TeamA_classes to nullptr" << endl;
    outputFile << "Set TeamA_classes to nullptr" << endl;
    
    TeamB_classes = nullptr;
    cout << "Set TeamB_classes to nullptr" << endl;
    outputFile << "Set TeamB_classes to nullptr" << endl;
    
    TeamA_symbols = nullptr;
    cout << "Set TeamA_symbols to nullptr" << endl;
    outputFile << "Set TeamA_symbols to nullptr" << endl;
    
    TeamB_symbols = nullptr;
    cout << "Set TeamB_symbols to nullptr" << endl;
    outputFile << "Set TeamB_symbols to nullptr" << endl;
    
    default_teamA_symbols = nullptr;
    cout << "Set default_teamA_symbols to nullptr" << endl;
    outputFile << "Set default_teamA_symbols to nullptr" << endl;
    
    default_teamB_symbols = nullptr;
    cout << "Set default_teamB_symbols to nullptr" << endl;
    outputFile << "Set default_teamB_symbols to nullptr" << endl;
    
    turn_queue = nullptr;
    cout << "Set turn_queue to nullptr" << endl;
    outputFile << "Set turn_queue to nullptr" << endl;
    
    respawn_queue = nullptr;
    cout << "Set respawn_queue to nullptr" << endl;
    outputFile << "Set respawn_queue to nullptr" << endl;

    if (game_map) {
        for (int i = 0; i < ship_count; ++i) {
            delete[] game_map[i];
            cout << "Deleted game_map[" << i << "]" << endl;
            outputFile << "Deleted game_map[" << i << "]" << endl;
        }
        delete[] game_map;
        cout << "Deleted game_map" << endl;
        outputFile << "Deleted game_map" << endl;
        game_map = nullptr;
    }

    if (symbol_map) {
        for (int i = 0; i < ship_count; ++i) {
            delete[] symbol_map[i];
            cout << "Deleted symbol_map[" << i << "]" << endl;
            outputFile << "Deleted symbol_map[" << i << "]" << endl;
        }
        delete[] symbol_map;
        cout << "Deleted symbol_map" << endl;
        outputFile << "Deleted symbol_map" << endl;
        symbol_map = nullptr;
    }
}

Ship::Ship() {
    cout << "Ship Created" << endl;
    outputFile << "Ship Created" << endl;
    ship_count++;
    id = ship_count;
    cout << id << endl;
    outputFile << id << endl;
}

Ship::~Ship() {
    ship_count--;
    cout << type << " died!" << endl;
    outputFile << type << " died!" << endl;
}

void Ship::display_info() const {
    cout << "Ship ID: " << id << endl;
    cout << "Team: " << team << endl;
    cout << "Type: " << type << endl;
    cout << "Symbol: " << symbol << endl;
    cout << "Position: (" << x+1 << ", " << y+1 << ")" << endl;
    cout << "Status: " << status << endl;
    cout << "Lives: " << lives << endl;
    cout << "Kills: " << kills << endl;
    
    outputFile << "Ship ID: " << id << endl;
    outputFile << "Team: " << team << endl;
    outputFile << "Type: " << type << endl;
    outputFile << "Symbol: " << symbol << endl;
    outputFile << "Position: (" << x+1 << ", " << y+1 << ")" << endl;
    outputFile << "Status: " << status << endl;
    outputFile << "Lives: " << lives << endl;
    outputFile << "Kills: " << kills << endl;
}

void Ship::set_id(int new_id) {id = new_id; }
void Ship::set_team(char new_team) { team = new_team; }
void Ship::set_type(const string& new_type) { type = new_type; }
void Ship::set_symbol(char new_symbol) { symbol = new_symbol; }
void Ship::set_x(int new_x) { x = new_x; }
void Ship::set_y(int new_y) { y = new_y; }
void Ship::set_status(const string& new_status) { status = new_status; }
void Ship::set_lives(int new_lives) { lives = new_lives; }
void Ship::decrement_lives() { lives--; }
void Ship::set_kills(int new_kills) { kills = new_kills; }
void Ship::increment_kills() { kills++; }

int Ship::get_id() const { return id; }
char Ship::get_team() const { return team; }
string Ship::get_type() const { return type; }
char Ship::get_symbol() const { return symbol; }
int Ship::get_x() const { return x; }
int Ship::get_y() const { return y; }
string Ship::get_status() const { return status; }
int Ship::get_lives() const { return lives; }
int Ship::get_kills() const { return kills; }