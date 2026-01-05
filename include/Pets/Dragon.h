#pragma once

#include "../Pet.h"
#include <SFML/Graphics.hpp>

class Dragon : public Pet {
private:
    int FireballDamage;
    int RoarStunTime;

public:
    Dragon(std::string name = "", int speed = 0, int petID = 0, int health = 0, 
           int Attackdamage = 0, int DefensePower = 0, int FireballDamage = 0, 
           int RoarStunTime = 0);
    
    void setMove1(int dmg) override;
    int getMove1() const override;
    void setMove2(int time) override;
    int getMove2() const override;
    
    Dragon& operator=(const Dragon& other);
    Pet* copy() override;
    int getType() override;
    void executeMove1(sf::RenderWindow& window, Pet* enemy) override;
    void executeMove2(sf::RenderWindow& window, Pet* enemy) override;
};

