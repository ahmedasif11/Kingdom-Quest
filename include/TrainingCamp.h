#pragma once

#include <SFML/Graphics.hpp>
#include "Pet.h"

class Pet;  // Forward declaration

class TrainingCamp {
private:
    int TokensGot;

public:
    void TrainPet(sf::RenderWindow& window, Pet* P, int i, sf::Text& popupText);
};

