#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <iostream>
#include <vector>
#include <string>

const int battlefieldWidth = 10;
const int battlefieldHeight = 10;
extern char battlefield[battlefieldHeight][battlefieldWidth];

// Abstract Base Class for Ships
class Ship {
protected:
    int positionX, positionY;
    char symbol;
    std::string team;

public:
    Ship(int x, int y, char sym, const std::string& t);
    virtual ~Ship();

    virtual void destroyEnemy(int x, int y);
    bool isEnemyShip(int x, int y);
    void printPosition() const;
};

// Derived Class for Destroyer
class Destroyer : public Ship {
public:
    Destroyer(int x, int y, char sym, const std::string& t);

    void takeTurn();
};

// Battlefield Initialization and Display
void initializeBattlefield();
void displayBattlefield();

#endif // BATTLEFIELD_H
