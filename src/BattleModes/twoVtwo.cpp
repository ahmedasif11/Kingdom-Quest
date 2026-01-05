#include "../../include/BattleModes/twoVtwo.h"
#include "../../include/Constants.h"
#include "../../include/Utils.h"
#include "../../include/SoundManager.h"
#include "../../include/Obstacles.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace sf;

twoVtwo::twoVtwo(Wall& w1, Wall& w2, Stone& s1, Stone& s2) : Arena(w1, w2, s1, s2) {}

void twoVtwo::setUserPet(Pet* temp, int index) {
    userPet[index] = temp;
}

void twoVtwo::setAiPet(Pet* temp, int index) {
    AiPet[index] = temp;
}

Pet* twoVtwo::getAiPet(int index) {
    return AiPet[index];
}

Pet* twoVtwo::getUserPet(int index) {
    return userPet[index];
}

// Note: twoVtwo Battle implementation is very similar to oneVone but uses arrays
// For now, this is a placeholder - the full implementation should be extracted from Game.cpp
// The structure is identical to oneVone but uses userPet[petNo] and AiPet[AiPetNo] instead
void twoVtwo::Battle(sf::RenderWindow& window, sf::Font& font, Player& user) {
    // Implementation needs to be extracted from Game.cpp lines 1761-2554
    // It's structurally identical to oneVone but uses arrays for pets
    // Key differences:
    // - Uses userPet[petNo] and AiPet[AiPetNo] instead of userPet and AiPet
    // - Has pet switching logic with petNo and AiPetNo variables
    // - Uses arrays for textures: userTex1[2], userTex2[2], etc.
    // - Uses arrays for sprites: userSprite[2], aiSprite[2]
    
    // For a working version, copy oneVone::Battle and adapt for arrays
    // See Game.cpp lines 1761-2554 for the full implementation
}

