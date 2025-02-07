#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <fstream>
#include "linkedlist.h"

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
    string status;
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
    static int** symbol_map;
    static ofstream outputFile;

    static void cleanup();

    Ship();
    virtual ~Ship();

    virtual void action_plan() = 0;
    void display_info() const;

    void set_id(int new_id);
    void set_team(char new_team);
    void set_type(const string& new_type);
    void set_symbol(char new_symbol);
    void set_x(int new_x);
    void set_y(int new_y);
    void set_status(const string& new_status);
    void set_lives(int new_lives);
    void decrement_lives();
    void set_kills(int new_kills);
    void increment_kills();

    int get_id() const;
    char get_team() const;
    string get_type() const;
    char get_symbol() const;
    int get_x() const;
    int get_y() const;
    string get_status() const;
    int get_lives() const;
    int get_kills() const;
};

#endif
