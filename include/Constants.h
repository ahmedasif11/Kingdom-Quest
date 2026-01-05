#pragma once

#include <SFML/Graphics.hpp>

namespace GameConstants {
    // Screen resolution
    const int X_RESOLUTION = 1280;
    const int Y_RESOLUTION = 720;
    const int CELL_SIZE = 64;
    const int COLS = X_RESOLUTION / CELL_SIZE;
    const int ROWS = Y_RESOLUTION / CELL_SIZE;
    
    // Game configuration
    const int MAX_LEVEL = 10;
    const int MAX_GUILDS = 5;
    const int MAX_BULLETS = 10;
    
    // UI Colors - Modern color scheme
    const sf::Color BUTTON_COLOR(45, 45, 60);        // Dark slate blue
    const sf::Color BUTTON_TEXT_COLOR(220, 220, 230); // Light gray-white
    const sf::Color BUTTON_HOVER_COLOR(65, 75, 95);   // Lighter slate blue
    const sf::Color POPUP_BG_COLOR(25, 25, 40);       // Darker background
    const sf::Color HEALTH_COLOR(220, 50, 50);        // Bright red
    const sf::Color TEXT_COLOR(240, 240, 250);        // Near white
}

