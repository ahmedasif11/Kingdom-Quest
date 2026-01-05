#pragma once

#include "../Pet.h"
#include <SFML/Graphics.hpp>

class Phoenix : public Pet {
private:
    int HealAmount;
    int didRebirth = 0;

public:
    Phoenix(std::string name = "", int speed = 0, int petID = 0, int health = 0, 
            int Attackdamage = 0, int DefensePower = 0, int HealAmount = 0);
    
    void setMove1(int amt) override;
    int getMove1() const override;
    void setMove2(int flag) override;
    int getMove2() const override;
    
    Pet* copy() override;
    Phoenix& operator=(const Phoenix& other);
    int getType() override;
    void executeMove1(sf::RenderWindow& window, Pet* enemy) override;
    void executeMove2(sf::RenderWindow& window, Pet* enemy) override;
};

