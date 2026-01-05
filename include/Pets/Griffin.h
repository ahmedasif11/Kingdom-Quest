#pragma once

#include "../Pet.h"
#include <SFML/Graphics.hpp>

class Griffin : public Pet {
private:
    int Clawdamage;
    int BombStunMoves;

public:
    Griffin(std::string name = "", int speed = 0, int petID = 0, int health = 0, 
            int Attackdamage = 0, int DefensePower = 0, int Clawdamage = 0, 
            int BombStunMoves = 0);
    
    void setMove1(int dmg) override;
    int getMove1() const override;
    void setMove2(int stun) override;
    int getMove2() const override;
    
    Griffin& operator=(const Griffin& other);
    Pet* copy() override;
    int getType() override;
    void executeMove1(sf::RenderWindow& window, Pet* enemy) override;
    void executeMove2(sf::RenderWindow& window, Pet* enemy) override;
};

