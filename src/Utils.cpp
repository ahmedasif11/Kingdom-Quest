#include "../include/Utils.h"
#include "../include/Constants.h"
#include <iostream>
#include <cstdlib>

sf::Texture& getDummyTexture() {
    static sf::Texture dummyTex;
    static bool initialized = false;
    if (!initialized) {
        sf::Image dummyImg({1, 1}, sf::Color::White);
        (void)dummyTex.loadFromImage(dummyImg);
        initialized = true;
    }
    return dummyTex;
}

bool rectsIntersect(const sf::FloatRect& rect1, const sf::FloatRect& rect2) {
    sf::Vector2f pos1 = rect1.position;
    sf::Vector2f size1 = rect1.size;
    sf::Vector2f pos2 = rect2.position;
    sf::Vector2f size2 = rect2.size;
    return pos1.x < pos2.x + size2.x &&
           pos1.x + size1.x > pos2.x &&
           pos1.y < pos2.y + size2.y &&
           pos1.y + size1.y > pos2.y;
}

bool checkCollision(sf::Sprite& pet, sf::Sprite& W1, sf::Sprite& W2, 
                    sf::Sprite& S1, sf::Sprite& S2) {
    return rectsIntersect(pet.getGlobalBounds(), W1.getGlobalBounds()) ||
           rectsIntersect(pet.getGlobalBounds(), W2.getGlobalBounds()) ||
           rectsIntersect(pet.getGlobalBounds(), S1.getGlobalBounds()) ||
           rectsIntersect(pet.getGlobalBounds(), S2.getGlobalBounds());
}

void createButtonWithText(sf::RectangleShape*& btn, sf::Text*& txt, sf::Font& font, 
                         const std::string& label, double row, double col, float width, 
                         const sf::Color& fillColor, const sf::Color& outlineColor) {
    btn = new sf::RectangleShape(sf::Vector2f(width, 55));
    btn->setFillColor(fillColor);
    btn->setPosition({col * GameConstants::CELL_SIZE, row * GameConstants::CELL_SIZE});
    
    // Modern styling with better outline and subtle shadow effect
    btn->setOutlineThickness(2.5f);
    btn->setOutlineColor(sf::Color(outlineColor.r, outlineColor.g, outlineColor.b, 200));

    txt = new sf::Text(font, label, 26);
    txt->setFillColor(GameConstants::BUTTON_TEXT_COLOR);
    txt->setStyle(sf::Text::Bold);

    sf::FloatRect textRect = txt->getLocalBounds();
    sf::Vector2f textSize = textRect.size;
    float textX = btn->getPosition().x + (width - textSize.x) / 2;
    float textY = btn->getPosition().y + (55 - textSize.y) / 2 - 5;
    txt->setPosition({textX, textY});
}

void CreateButton(sf::RectangleShape*& btn, double row, double col, float width, 
                  const sf::Color& fillColor, const sf::Color& outlineColor) {
    btn = new sf::RectangleShape(sf::Vector2f(width, 50));
    btn->setFillColor(fillColor);
    btn->setOutlineThickness(2);
    btn->setOutlineColor(outlineColor);
    btn->setPosition({col * GameConstants::CELL_SIZE, row * GameConstants::CELL_SIZE});
}

float AskLevel(sf::RenderWindow& window) {
    sf::Texture LevelBg;
    if (!LevelBg.loadFromFile("assets/images/Level.png")) {
        std::cout << "Image load Failure";
        exit(0);
    }
    sf::Sprite bg(LevelBg);
    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::E)
                    return 1;
                if (keyPressed->code == sf::Keyboard::Key::M)
                    return 1.5;
                if (keyPressed->code == sf::Keyboard::Key::H)
                    return 2;
            }
        }
        window.draw(bg);
        window.display();
    }
    return 1;
}

