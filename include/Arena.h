#pragma once

#include "Obstacles.h"
#include <SFML/Audio.hpp>

class Wall;
class Stone;

class Arena {
protected:
    Wall W1;
    Wall W2;
    Stone S1;
    Stone S2;
    int Prize = 200;
    float TimeLimit = 60.f;
    sf::SoundBuffer hitBuffer;
    sf::Sound hitSound;

public:
    Arena(Wall& w1, Wall& w2, Stone& s1, Stone& s2);
    virtual ~Arena() = default;
};

