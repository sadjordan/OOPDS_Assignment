/***|***|****|
Program: seeingrobot.h
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
#ifndef SEEINGROBOT_H
#define SEEINGROBOT_H

#include <random>
#include <iostream>

using namespace std;

class SeeingRobot : virtual public Ship {
private:

protected:
    int directions[8][2] = { {-1, 1},  {0, 1},  {1, 1},  // Up-left, Up, Up-right
                             {-1, 0},           {1, 0},   // Left,       Right
                             {-1, -1}, {0, -1}, {1, -1}    // Down-left, Down, Down-right
    };
    char look_results[8];
    int target[2];
    virtual void look() = 0;
};

#endif