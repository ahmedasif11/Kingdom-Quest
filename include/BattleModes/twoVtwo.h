#pragma once

#include "../Arena.h"
#include "../Pet.h"
#include "../Player.h"
#include "../Obstacles.h"
#include <SFML/Graphics.hpp>

class twoVtwo : public Arena {
private:
    Pet* userPet[2] = {nullptr, nullptr};
    Pet* AiPet[2] = {nullptr, nullptr};

public:
    twoVtwo(Wall& w1, Wall& w2, Stone& s1, Stone& s2);
    
    void setUserPet(Pet* temp, int index);
    void setAiPet(Pet* temp, int index);
    Pet* getAiPet(int index);
    Pet* getUserPet(int index);
    
    void Battle(sf::RenderWindow& window, sf::Font& font, Player& user);
};

