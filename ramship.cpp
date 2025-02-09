/***|***|****|
Program: ramship.cpp
Course: Object Oriented Programming and Data Structures
Trimester: 2430
Name: Jordan Ling, Muhammad Izaan Khan Bin Mubarak, Selvasaachinn A/L Selvarasan, MONISH A/L MOORTHY 
ID: 241UC24151, 241UC2415K, 1211108941, 1211111608
Lecture Section: TC2L
Tutorial Section: TT5L
Email: jordan.ling.shen@student.mmu.edu.my, Muhammad.izaan.khan@student.mmu.edu.my,
        1211108941@student.mmu.edu.my, 1211111608@student.mmu.edu.my
Phone: 014-2286351, 016-7573174, 011-10872234, 011-54240624
***|***|****/
#include "ramship.h"
using namespace std;

void RamShip::ram(Ship* to_be_killed) {
    if (to_be_killed->get_lives() == 0) {
        cout << "An enemy ship " << to_be_killed->get_type() << ", with the id " << to_be_killed->get_id() << " from Team " << to_be_killed->get_team() << " was rammed!" << endl;
        outputFile << "An enemy ship " << to_be_killed->get_type() << ", with the id " << to_be_killed->get_id() << " from Team " << to_be_killed->get_team() << " was rammed!" << endl;
        
        cout << "The enemy ship has no more lives" << endl;
        outputFile << "The enemy ship has no more lives" << endl;
        Ship* temp = to_be_killed;
        // cout << "Pass 1" << endl;
        // cout << temp << endl;
        // cout << to_be_killed << endl;
        turn_queue->deleteNode(temp);
        // cout << "Pass 2" << endl;
        delete temp;

        game_map[x][y] = symbol;
        symbol_map[x][y] = id;

        return;
    }
    to_be_killed->set_status("In Respawn Queue");
    to_be_killed->decrement_lives();
    to_be_killed->set_x(NULL);
    to_be_killed->set_y(NULL);
    // cout << "Pass 2" << endl;

    game_map[x][y] = symbol;
    symbol_map[x][y] = id;
    // cout << "Pass 3" << endl;

    cout << "A " << to_be_killed->get_type() << " from Team " << to_be_killed->get_team() << " was rammed!" << endl;
    outputFile << "A " << to_be_killed->get_type() << " from Team " << to_be_killed->get_team() << " was rammed!" << endl;

    respawn_queue->push_back(to_be_killed);
    turn_queue->deleteNode(to_be_killed);
    // cout << "Pass 4" << endl;
}