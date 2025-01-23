#ifndef LOOK_H
#define LOOK_H

#include <iostream>
#include <vector>

class Ship {
protected:
    int x, y; 
    int battlefieldWidth, battlefieldHeight;
    char symbol;

public:
    Ship(int startX, int startY, int width, int height, char sym)
        : x(startX), y(startY), battlefieldWidth(width), battlefieldHeight(height), symbol(sym) {}

    virtual ~Ship() = default;

    virtual void look(const std::vector<std::vector<char>>& battlefield) = 0; 
};

class Battleship : public Ship {
public:
    Battleship(int startX, int startY, int width, int height)
        : Ship(startX, startY, width, height, '*') {}

    void look(const std::vector<std::vector<char>>& battlefield) override {
        std::cout << "Battleship (" << x << ", " << y << ") is looking around:\n";
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int nx = x + i;
                int ny = y + j;

                if (nx >= 0 && nx < battlefieldHeight && ny >= 0 && ny < battlefieldWidth) {
                    std::cout << battlefield[nx][ny] << " ";
                } else {
                    std::cout << "X "; 
                }
            }
            std::cout << "\n";
        }
    }
};

#endif
