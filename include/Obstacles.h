#pragma once

#include <SFML/Graphics.hpp>

class Obstacles {
protected:
    float x_Position;
    float y_Position;

public:
    Obstacles(float x, float y);
    float getXPosition() const;
    float getYPosition() const;
    void setXPosition(float x);
    void setYPosition(float y);
};

class Stone : public Obstacles {
public:
    Stone(float x = 0, float y = 0);
    void display(sf::RenderWindow& window, sf::Texture& S, sf::Sprite& pic);
};

class Wall : public Obstacles {
public:
    Wall(float x = 0, float y = 0);
    void display(sf::RenderWindow& window, sf::Texture& W, sf::Sprite& pic);
};

