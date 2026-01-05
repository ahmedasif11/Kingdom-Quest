#pragma once

#include <SFML/Audio.hpp>

// Global sound manager for UI sounds
extern sf::SoundBuffer clickBuffer;
extern sf::Sound clickSound;

void initializeClickSound();

