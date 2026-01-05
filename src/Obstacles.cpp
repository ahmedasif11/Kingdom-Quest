#include "../include/Obstacles.h"
#include <iostream>
#include <cstdlib>

Obstacles::Obstacles(float x, float y) : x_Position(x), y_Position(y) {}

float Obstacles::getXPosition() const { return x_Position; }
float Obstacles::getYPosition() const { return y_Position; }
void Obstacles::setXPosition(float x) { x_Position = x; }
void Obstacles::setYPosition(float y) { y_Position = y; }

Stone::Stone(float x, float y) : Obstacles(x, y) {}

void Stone::display(sf::RenderWindow& window, sf::Texture& S, sf::Sprite& pic) {
    if (!S.loadFromFile("assets/images/Stone.png")) {
        std::cout << "Failed to load Stone.png\n";
        exit(0);
    }
    pic.setPosition({x_Position, y_Position});
    pic.setTexture(S);
}

Wall::Wall(float x, float y) : Obstacles(x, y) {}

void Wall::display(sf::RenderWindow& window, sf::Texture& W, sf::Sprite& pic) {
    if (!W.loadFromFile("assets/images/Wall.png")) {
        std::cout << "Failed to load Wall.png\n";
        exit(0);
    }
    pic.setPosition({x_Position, y_Position});
    pic.setTexture(W);
}

