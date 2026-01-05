#include "../include/SoundManager.h"
#include <iostream>
#include <cstdlib>

sf::SoundBuffer clickBuffer;
sf::Sound clickSound(clickBuffer);

void initializeClickSound() {
    if (!clickBuffer.loadFromFile("assets/sounds/ButtonClickSound.wav")) {
        std::cout << "Failed to load sound\n";
        exit(1);
    }
    clickSound.setBuffer(clickBuffer);
}

