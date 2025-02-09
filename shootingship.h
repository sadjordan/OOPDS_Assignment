/***|***|****|
Program: shootingship.h
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
#ifndef SHOOTINGSHIP_H
#define SHOOTINGSHIP_H

#include <iostream>
#include <random>
#include "ship.h"
#include "linkedlist.h"

class ShootingShip : virtual public Ship {
public:
    void kill(int target_x, int target_y);
    virtual void shoot() = 0;
};

#endif
