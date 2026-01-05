#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <string>

// Collision detection
bool rectsIntersect(const sf::FloatRect& rect1, const sf::FloatRect& rect2);
bool checkCollision(sf::Sprite& pet, sf::Sprite& W1, sf::Sprite& W2, 
                    sf::Sprite& S1, sf::Sprite& S2);

// UI Helper functions with modern styling
void createButtonWithText(sf::RectangleShape*& btn, sf::Text*& txt, sf::Font& font, 
                         const std::string& label, double row, double col, float width, 
                         const sf::Color& fillColor = GameConstants::BUTTON_COLOR, 
                         const sf::Color& outlineColor = GameConstants::BUTTON_TEXT_COLOR);

void CreateButton(sf::RectangleShape*& btn, double row, double col, float width, 
                  const sf::Color& fillColor = GameConstants::BUTTON_COLOR, 
                  const sf::Color& outlineColor = GameConstants::BUTTON_TEXT_COLOR);

// Texture helper
sf::Texture& getDummyTexture();

// Level selection
float AskLevel(sf::RenderWindow& window);

