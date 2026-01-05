#include "../include/Arena.h"
#include "../include/Obstacles.h"
#include <iostream>
#include <cstdlib>

Arena::Arena(Wall& w1, Wall& w2, Stone& s1, Stone& s2) : hitSound(hitBuffer) {
    W1 = w1;
    W2 = w2;
    S1 = s1;
    S2 = s2;
    if (!hitBuffer.loadFromFile("assets/sounds/hit.wav")) {
        std::cout << "Failed to load sound\n";
        exit(1);
    }
}

