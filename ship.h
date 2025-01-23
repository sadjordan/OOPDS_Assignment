#ifndef SHIP_H
#define SHIP_H

#include <iostream>
using namespace std;


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
    virtual void action_plan() = 0;
    Ship() {
        cout << "Ship Created" << endl;
        ship_count++;
        id = ship_count;
        cout << id << endl;

        //Ships = Game_Setup::Ships;
    }

    ~Ship() {
        ship_count--;

        cout << "Ship death" << endl;
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
    void set_kills(int new_kills) { kills = new_kills; }
};

#endif