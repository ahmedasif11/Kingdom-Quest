#pragma once

#include "../Arena.h"
#include "../Pet.h"
#include "../Player.h"
#include "../Obstacles.h"
#include <SFML/Graphics.hpp>

class oneVone : public Arena {
private:
    Pet* userPet = nullptr;
    Pet* AiPet = nullptr;

public:
    oneVone(Wall& w1, Wall& w2, Stone& s1, Stone& s2);
    
    void setUserPet(Pet* temp);
    void setAiPet(Pet* temp);
    Pet* getAiPet();
    Pet* getUserPet();
    
    void Battle(sf::RenderWindow& window, sf::Font& font, Player& user);
};

