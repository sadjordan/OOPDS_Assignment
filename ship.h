#ifndef SHIP_H
#define SHIP_H

#include <iostream>
using namespace std;

#include "linkedlist.cpp"


class Ship {
private:
    int no_ships;
protected:
    int id;
    static int ship_count;
    char team;
    string type;
    char symbol;
    int x;
    int y;
    string status = "Deployed";
    int lives = 3;
    int kills = 0;

public:
    static int* game_settings;
    static char** game_map;
    static char* TeamA_symbols;
    static char* TeamB_symbols;
    static string* TeamA_classes;
    static string* TeamB_classes;
    static int* TeamA;
    static int* TeamB;
    static Linked_List<Ship*>* turn_queue;
    static Linked_List<Ship*>* respawn_queue;
    static char* default_teamA_symbols;
    static char* default_teamB_symbols;

    virtual void action_plan() = 0;

    Ship() {
        cout << "Ship Created" << endl;
        ship_count++;
        id = ship_count;
        cout << id << endl;

        //Ships = Game_Setup::Ships;
    }

    virtual ~Ship() {
        ship_count--;

        cout << "Ship died" << endl;
    }

    void display_info() const {
        cout << "Ship ID: " << id << endl;
        cout << "Team: " << team << endl;
        cout << "Type: " << type << endl;
        cout << "Symbol: " << symbol << endl;
        cout << "Position: (" << x << ", " << y << ")" << endl;
        cout << "Status: " << status << endl;
        cout << "Lives: " << lives << endl;
        cout << "Kills: " << kills << endl;
    }

    void set_team(char new_team) { team = new_team; }
    void set_type(const string& new_type) { type = new_type; }
    void set_symbol(char new_symbol) { symbol = new_symbol; }
    void set_x(int new_x) { x = new_x; }
    void set_y(int new_y) { y = new_y; }
    void set_status(const string& new_status) { status = new_status; }
    void set_lives(int new_lives) { lives = new_lives; }
    void decrement_lives() { lives--; }
    void set_kills(int new_kills) { kills = new_kills; }
    void increment_kills() { kills++; }

    char get_team() const { return team; }
    string get_type() const { return type; }
    char get_symbol() const { return symbol; }
    int get_x() const { return x; }
    int get_y() const { return y; }
    string get_status() const { return status; }
    int get_lives() const { return lives; }
    int get_kills() const { return kills; }
};

#endif