#pragma once

#include "../Pet.h"
#include <SFML/Graphics.hpp>

class Unicorn : public Pet {
private:
    int SpeedBurst;
    int ShieldPower;

public:
    Unicorn(std::string name = "", int speed = 0, int petID = 0, int health = 0, 
            int Attackdamage = 0, int DefensePower = 0, int SpeedBurst = 0, 
            int ShieldPower = 0);
    
    void setMove1(int burst) override;
    int getMove1() const override;
    void setMove2(int power) override;
    int getMove2() const override;
    
    Unicorn& operator=(const Unicorn& other);
    Pet* copy() override;
    int getType() override;
    void executeMove1(sf::RenderWindow& window, Pet* enemy) override;
    void executeMove2(sf::RenderWindow& window, Pet* enemy) override;
};

