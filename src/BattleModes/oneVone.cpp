#include "../../include/BattleModes/oneVone.h"
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

oneVone::oneVone(Wall& w1, Wall& w2, Stone& s1, Stone& s2) : Arena(w1, w2, s1, s2) {}

void oneVone::setUserPet(Pet* temp) {
    userPet = temp;
}

void oneVone::setAiPet(Pet* temp) {
    AiPet = temp;
}

Pet* oneVone::getAiPet() {
    return AiPet;
}

Pet* oneVone::getUserPet() {
    return userPet;
}

void oneVone::Battle(sf::RenderWindow& window, sf::Font& font, Player& user) {
    float level = AskLevel(window);
    sf::Text popupText(font, "", 28);
    popupText.setFillColor(sf::Color::White);
    popupText.setStyle(sf::Text::Bold);
    popupText.setPosition({GameConstants::X_RESOLUTION / 2.5f, GameConstants::Y_RESOLUTION / 3.0f});
    bool showPopup = false;
    sf::Clock popupClock;
    sf::Clock GameClock;
    sf::Clock aiMoveClock;
    float aiMoveInterval = 1.5f;
    sf::Vector2f aiDirection(0, 0);
    sf::Clock SpeedReset;
    sf::Text userHealth(font, "", 24), AiHealth(font, "", 24), clock(font, "", 24);
    clock.setPosition({10 * GameConstants::CELL_SIZE, 0.5f * GameConstants::CELL_SIZE});
    userHealth.setPosition({0.5f * GameConstants::CELL_SIZE, 0.5f * GameConstants::CELL_SIZE});
    AiHealth.setPosition({18 * GameConstants::CELL_SIZE, 0.5f * GameConstants::CELL_SIZE});
    sf::Clock frameClock;
    sf::Clock Move1Cooldown;
    sf::Clock Move2Cooldown;
    int currentFrame = 0;
    float frameTime = 0.2f;
    sf::Texture BG;
    sf::Texture Fireball;
    sf::Texture Claw;
    int MaxbulletCount = 10;
    bool activeBullets[10] = {0};
    sf::Texture userTex1, userTex2, userTex3, Bullet;
    sf::Texture aiTex1, aiTex2, aiTex3;
    sf::Texture Aibullet;
    const int MaxAIBullets = 10;
    bool activeAIBullets[MaxAIBullets] = {false};
    sf::Clock aiFireClock;
    float aiFireInterval = 0.5f;
    sf::Texture potionTex;
    
    // loading random arena bg
    int bgNum = rand() % 4 + 1;
    if (bgNum == 1)
        if (!BG.loadFromFile("assets/images/BattleBG.png")) {
            std::cout << "Image load Failure";
            exit(0);
        }
    if (bgNum == 2)
        if (!BG.loadFromFile("assets/images/BattleBG(1).png")) {
            std::cout << "Image load Failure";
            exit(0);
        }
    if (bgNum == 3)
        if (!BG.loadFromFile("assets/images/BattleBG(2).png")) {
            std::cout << "Image load Failure";
            exit(0);
        }
    if (bgNum == 4)
        if (!BG.loadFromFile("assets/images/BattleBG(3).png")) {
            std::cout << "Image load Failure";
            exit(0);
        }
    if (!potionTex.loadFromFile("assets/images/Potion.png")) {
        std::cout << "Failed to load Potion.png\n";
        exit(0);
    }
    if (!Aibullet.loadFromFile("assets/images/Bullet.png")) {
        std::cout << "Image load Failure";
        exit(0);
    }
    // Initialize aiBullet array after texture is loaded using placement new
    alignas(sf::Sprite) unsigned char aiBulletMem[sizeof(sf::Sprite) * MaxAIBullets];
    sf::Sprite* aiBullet = reinterpret_cast<sf::Sprite*>(aiBulletMem);
    for (int i = 0; i < MaxAIBullets; i++) {
        new(aiBullet + i) sf::Sprite(Aibullet);
    }

    // loading other sprites
    if (!Claw.loadFromFile("assets/images/Claw.png")) {
        std::cout << "Image load Failure";
        exit(0);
    }
    if (!Fireball.loadFromFile("assets/images/FireBall.png")) {
        std::cout << "Image load Failure";
        exit(0);
    }
    if (!Bullet.loadFromFile("assets/images/Bullet.png")) {
        std::cout << "Image load Failure";
        exit(0);
    }
    // Initialize bullet arrays after textures are loaded using placement new
    alignas(sf::Sprite) unsigned char bulletMem[sizeof(sf::Sprite) * MaxbulletCount];
    sf::Sprite* bullet = reinterpret_cast<sf::Sprite*>(bulletMem);
    for (int i = 0; i < MaxbulletCount; i++) {
        new(bullet + i) sf::Sprite(Bullet);
    }
    // aiBullet was already initialized above
    if (AiPet->getType() == 1) {
        if (!aiTex1.loadFromFile("assets/images/DragonSide2.png")) {
            std::cout << "Failed to load DragonSide2.png\n";
            exit(0);
        }
        if (!aiTex2.loadFromFile("assets/images/DragonSide2(0).png")) {
            std::cout << "Failed to load DragonSide2(0).png\n";
            exit(0);
        }
        if (!aiTex3.loadFromFile("assets/images/DragonSide2(1).png")) {
            std::cout << "Failed to load DragonSide2(1).png\n";
            exit(0);
        }
    }
    if (AiPet->getType() == 2) {
        if (!aiTex1.loadFromFile("assets/images/PhoenixSide2.png")) {
            std::cout << "Failed to load PhoenixSide2.png\n";
            exit(0);
        }
        if (!aiTex2.loadFromFile("assets/images/PhoenixSide2(0).png")) {
            std::cout << "Failed to load PhoenixSide2(0).png\n";
            exit(0);
        }
        if (!aiTex3.loadFromFile("assets/images/PhoenixSide2(1).png")) {
            std::cout << "Failed to load PhoenixSide2(1).png\n";
            exit(0);
        }
    }
    if (AiPet->getType() == 3) {
        if (!aiTex1.loadFromFile("assets/images/UnicornSide2.png")) {
            std::cout << "Failed to load UnicornSide2.png\n";
            exit(0);
        }
        if (!aiTex2.loadFromFile("assets/images/UnicornSide2(0).png")) {
            std::cout << "Failed to load UnicornSide2(0).png\n";
            exit(0);
        }
        if (!aiTex3.loadFromFile("assets/images/UnicornSide2(1).png")) {
            std::cout << "Failed to load UnicornSide2(1).png\n";
            exit(0);
        }
    }
    if (AiPet->getType() == 4) {
        if (!aiTex1.loadFromFile("assets/images/GriffinSide2.png")) {
            std::cout << "Failed to load GriffinSide2.png\n";
            exit(0);
        }
        if (!aiTex2.loadFromFile("assets/images/GriffinSide2(0).png")) {
            std::cout << "Failed to load GriffinSide2(0).png\n";
            exit(0);
        }
        if (!aiTex3.loadFromFile("assets/images/GriffinSide2(1).png")) {
            std::cout << "Failed to load GriffinSide2(1).png\n";
            exit(0);
        }
    }

    if (userPet->getType() == 1) {
        if (!userTex1.loadFromFile("assets/images/DragonSide1.png")) {
            std::cout << "Failed to load DragonSide1.png\n";
            exit(0);
        }
        if (!userTex2.loadFromFile("assets/images/DragonSide1(0).png")) {
            std::cout << "Failed to load DragonSide1(0).png\n";
            exit(0);
        }
        if (!userTex3.loadFromFile("assets/images/DragonSide1(1).png")) {
            std::cout << "Failed to load DragonSide1(1).png\n";
            exit(0);
        }
    }
    if (userPet->getType() == 2) {
        if (!userTex1.loadFromFile("assets/images/PhoenixSide1.png")) {
            std::cout << "Failed to load PhoenixSide1.png\n";
            exit(0);
        }
        if (!userTex2.loadFromFile("assets/images/PhoenixSide1(0).png")) {
            std::cout << "Failed to load PhoenixSide1(0).png\n";
            exit(0);
        }
        if (!userTex3.loadFromFile("assets/images/PhoenixSide1(1).png")) {
            std::cout << "Failed to load PhoenixSide1(1).png\n";
            exit(0);
        }
    }
    if (userPet->getType() == 3) {
        if (!userTex1.loadFromFile("assets/images/UnicornSide1.png")) {
            std::cout << "Failed to load UnicornSide1.png\n";
            exit(0);
        }
        if (!userTex2.loadFromFile("assets/images/UnicornSide1(0).png")) {
            std::cout << "Failed to load UnicornSide1(0).png\n";
            exit(0);
        }
        if (!userTex3.loadFromFile("assets/images/UnicornSide1(1).png")) {
            std::cout << "Failed to load UnicornSide1(1).png\n";
            exit(0);
        }
    }
    if (userPet->getType() == 4) {
        if (!userTex1.loadFromFile("assets/images/GriffinSide1.png")) {
            std::cout << "Failed to load GriffinSide1.png\n";
            exit(0);
        }
        if (!userTex2.loadFromFile("assets/images/GriffinSide1(0).png")) {
            std::cout << "Failed to load GriffinSide1(0).png\n";
            exit(0);
        }
        if (!userTex3.loadFromFile("assets/images/GriffinSide1(1).png")) {
            std::cout << "Failed to load GriffinSide1(1).png\n";
            exit(0);
        }
    }
    int StartHealth = userPet->getHealth();
    sf::Clock ClawTimer;
    sf::Clock StunTimer;
    sf::Clock shieldTimer;
    sf::Clock griffinStunTimer;
    sf::Clock BuffTimer;
    bool isBuff = false;
    sf::Sprite aiSprite(aiTex1);
    sf::Sprite userSprite(userTex1);
    sf::Sprite fireball(Fireball);
    sf::Sprite claw(Claw);
    bool ManaPotion = false;
    bool ShieldPotion = false;
    sf::Clock ShieldPotionClock;
    aiSprite.setPosition({17 * GameConstants::CELL_SIZE, 5 * GameConstants::CELL_SIZE});
    userSprite.setPosition({1 * GameConstants::CELL_SIZE, 5 * GameConstants::CELL_SIZE});
    sf::Texture stone1, stone2, wall1, wall2;
    sf::Sprite sprite_stone1(getDummyTexture()), sprite_stone2(getDummyTexture()), sprite_wall1(getDummyTexture()), sprite_wall2(getDummyTexture());
    sf::Sprite bg(BG);
    sf::Sprite potion(potionTex);
    sf::Clock potionTimer;
    bool showPotion = false;
    while (window.isOpen()) {
        window.clear();
        userHealth.setString("HP : " + std::to_string(userPet->getHealth()));
        AiHealth.setString("HP : " + std::to_string(AiPet->getHealth()));
        W1.display(window, wall1, sprite_wall1);
        W2.display(window, wall2, sprite_wall2);
        S1.display(window, stone1, sprite_stone1);
        S2.display(window, stone2, sprite_stone2);

        // animation of pet movement
        if (frameClock.getElapsedTime().asSeconds() > frameTime) {
            currentFrame++;
            if (currentFrame > 2)
                currentFrame = 0;

            if (currentFrame == 0) {
                userSprite.setTexture(userTex1);
                aiSprite.setTexture(aiTex1);
            }
            if (currentFrame == 1) {
                userSprite.setTexture(userTex2);
                aiSprite.setTexture(aiTex2);
            }
            if (currentFrame == 2) {
                userSprite.setTexture(userTex3);
                aiSprite.setTexture(aiTex3);
            }

            frameClock.restart();
        }
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            // When space key is released, fire a bullet if one is available
            else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
                if (keyReleased->code == sf::Keyboard::Key::Space) {
                    for (int i = 0; i < MaxbulletCount; ++i) {
                        if (!activeBullets[i]) {
                            clickSound.play();
                            activeBullets[i] = true;
                            bullet[i].setPosition({userSprite.getPosition().x + 50, userSprite.getPosition().y + 40});
                            break;
                        }
                    }
                }
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                // Mana Potion on M
                if (keyPressed->code == sf::Keyboard::Key::M) {
                    if (user.getNoOfManaPotions() > 0) {
                        clickSound.play();
                        user.setNoOfManaPotions(user.getNoOfManaPotions() - 1);
                        popupClock.restart();
                        popupText.setString("Mana Potion Used");
                        showPopup = true;
                        ManaPotion = true;
                    }
                }
                // Heal Potion on H
                if (keyPressed->code == sf::Keyboard::Key::H) {
                    if (user.getNoOfHealingPotions() > 0) {
                        clickSound.play();
                        user.setNoOfHealingPotions(user.getNoOfHealingPotions() - 1);
                        popupClock.restart();
                        popupText.setString("Healing Potion Used");
                        showPopup = true;
                        if (userPet->getHealth() < StartHealth)
                            userPet->setHealth(StartHealth);
                    }
                }
                // Buff Potion on B
                if (keyPressed->code == sf::Keyboard::Key::B) {
                    if (user.getNoOfBuffItems() > 0) {
                        clickSound.play();
                        user.setNoOfBuffItems(user.getNoOfBuffItems() - 1);
                        popupClock.restart();
                        popupText.setString("Buff Potion Used");
                        showPopup = true;
                        userPet->setAttackDamage(userPet->getAttackDamage() + 20);
                        userPet->setSpeed(userPet->getSpeed() + 5);
                        BuffTimer.restart();
                        isBuff = true;
                    }
                }
                // Shield on S
                if (keyPressed->code == sf::Keyboard::Key::S) {
                    if (user.getNoOfShields() > 0) {
                        clickSound.play();
                        user.setNoOfShields(user.getNoOfShields() - 1);
                        popupClock.restart();
                        popupText.setString("Shield Potion Used");
                        showPopup = true;
                        AiPet->setAttackDamage(AiPet->getAttackDamage() * 0.5);
                        ShieldPotionClock.restart();
                        ShieldPotion = true;
                    }
                }
                // Second special Move on X
                if (keyPressed->code == sf::Keyboard::Key::X) {
                    // Allow only if cooldown is over or Mana potion is used
                    if (Move2Cooldown.getElapsedTime().asSeconds() > 10.f || ManaPotion) {
                        clickSound.play();
                        popupClock.restart();
                        popupText.setString("Ability 2 Used");
                        showPopup = true;
                        Move2Cooldown.restart();
                        userPet->executeMove2(window, AiPet);
                        StunTimer.restart();
                        griffinStunTimer.restart();
                        shieldTimer.restart();
                        ManaPotion = false;
                    }
                }
                // First special move on Z
                if (keyPressed->code == sf::Keyboard::Key::Z) {
                    // Allow only if cooldown is over or Mana potion is used
                    if (Move1Cooldown.getElapsedTime().asSeconds() > 10.f || ManaPotion) {
                        clickSound.play();
                        popupClock.restart();
                        popupText.setString("Ability 1 Used");
                        showPopup = true;
                        Move1Cooldown.restart();
                        userPet->executeMove1(window, AiPet);
                        SpeedReset.restart();
                        ClawTimer.restart();
                        if (userPet->getFireball())
                            fireball.setPosition({userSprite.getPosition().x + 50, userSprite.getPosition().y + 40});
                        if (userPet->getClaw()) {
                            claw.setPosition({userSprite.getPosition().x + 120, userSprite.getPosition().y + 40});
                            if (aiSprite.getPosition().x <= userSprite.getPosition().x + 150 && aiSprite.getPosition().x >= userSprite.getPosition().x) {
                                AiPet->setHealth(AiPet->getHealth() - userPet->getMove1());
                            }
                        }
                        ManaPotion = false;
                    }
                }
                // movement of user by input
                sf::Vector2f direction(0, 0);
                if (keyPressed->code == sf::Keyboard::Key::Left)
                    direction = sf::Vector2f(-userPet->getSpeed(), 0);
                if (keyPressed->code == sf::Keyboard::Key::Right)
                    direction = sf::Vector2f(userPet->getSpeed(), 0);
                if (keyPressed->code == sf::Keyboard::Key::Up)
                    direction = sf::Vector2f(0, -userPet->getSpeed());
                if (keyPressed->code == sf::Keyboard::Key::Down)
                    direction = sf::Vector2f(0, userPet->getSpeed());

                // checking collision with obstacles
                if (direction.x != 0 || direction.y != 0) {
                    sf::Sprite tempSprite = userSprite;
                    tempSprite.move(direction);

                    if (tempSprite.getPosition().x >= 0 && tempSprite.getPosition().x <= 1100 &&
                        tempSprite.getPosition().y >= 0 && tempSprite.getPosition().y <= 580 &&
                        !checkCollision(tempSprite, sprite_wall1, sprite_wall2, sprite_stone1, sprite_stone2))
                        userSprite.move(direction);
                }
            }
        }
        // random ai movement after some time
        if (aiMoveClock.getElapsedTime().asSeconds() > aiMoveInterval) {
            int dir = rand() % 4;

            switch (dir) {
            case 0:
                aiDirection = sf::Vector2f(-AiPet->getSpeed(), 0);
                break;
            case 1:
                aiDirection = sf::Vector2f(AiPet->getSpeed(), 0);
                break;
            case 2:
                aiDirection = sf::Vector2f(0, -AiPet->getSpeed());
                break;
            case 3:
                aiDirection = sf::Vector2f(0, AiPet->getSpeed());
                break;
            }

            aiMoveClock.restart();
        }
        // check ai collision with obstacles before movement
        sf::Sprite tempAI = aiSprite;
        tempAI.move(aiDirection);
        if (tempAI.getPosition().x >= 0 && tempAI.getPosition().x <= 1100 &&
            tempAI.getPosition().y >= 0 && tempAI.getPosition().y <= 580 &&
            !checkCollision(tempAI, sprite_wall1, sprite_wall2, sprite_stone1, sprite_stone2)) {
            aiSprite.move(aiDirection);
        }
        // check collision of user bullet with obstacles
        for (int i = 0; i < MaxbulletCount; i++)
            if (activeBullets[i] == true)
                if (checkCollision(bullet[i], sprite_wall1, sprite_wall2, sprite_stone1, sprite_stone2) || bullet[i].getPosition().x > 1270) {
                    activeBullets[i] = false;
                }

        // check collision of user bullet with ai pet
        for (int i = 0; i < MaxbulletCount; i++)
            if (activeBullets[i] == true)
                if (rectsIntersect(aiSprite.getGlobalBounds(), bullet[i].getGlobalBounds())) {
                    hitSound.play();
                    if (userPet->getAttackDamage() > AiPet->getDefensePower())
                        AiPet->setHealth(AiPet->getHealth() - userPet->getAttackDamage() + AiPet->getDefensePower());
                    activeBullets[i] = false;
                }
        // move bullet on arena
        for (int i = 0; i < MaxbulletCount; i++) {
            if (activeBullets[i] == true) {
                bullet[i].move({5, 0});
            }
        }
        // check collision of dragon special ability fireball with obstacles
        if (userPet->getFireball())
            if (checkCollision(fireball, sprite_wall1, sprite_wall2, sprite_stone1, sprite_stone2)) {
                userPet->setFireball(false);
            }
        // check collision of dragon special ability fireball with ai pet
        if (userPet->getFireball())
            if (rectsIntersect(aiSprite.getGlobalBounds(), fireball.getGlobalBounds())) {
                hitSound.play();
                AiPet->setHealth(AiPet->getHealth() - userPet->getMove1());
                userPet->setFireball(false);
            }
        // fire ai bullets when its not stunned by any user pet special ability
        if (!AiPet->getStun() && !AiPet->getGriffinStun())
            if (aiFireClock.getElapsedTime().asSeconds() > aiFireInterval) {
                for (int i = 0; i < MaxAIBullets; ++i) {
                    if (!activeAIBullets[i]) {
                        activeAIBullets[i] = true;
                        aiBullet[i].setPosition({aiSprite.getPosition().x - 20, aiSprite.getPosition().y + 40});
                        break;
                    }
                }
                aiFireClock.restart();
            }
        // move ai bullets,check collision with obstacles and userpet
        for (int i = 0; i < MaxAIBullets; ++i) {
            if (activeAIBullets[i]) {
                aiBullet[i].move({-5, 0});
                if (checkCollision(aiBullet[i], sprite_wall1, sprite_wall2, sprite_stone1, sprite_stone2) ||
                    aiBullet[i].getPosition().x < 0) {
                    activeAIBullets[i] = false;
                }
                if (rectsIntersect(userSprite.getGlobalBounds(), aiBullet[i].getGlobalBounds())) {
                    hitSound.play();
                    if (AiPet->getAttackDamage() * level > userPet->getDefensePower())
                        userPet->setHealth(userPet->getHealth() - AiPet->getAttackDamage() * level + userPet->getDefensePower());
                    activeAIBullets[i] = false;
                }
            }
        }

        window.draw(bg);
        // shield potion timer
        if (ShieldPotionClock.getElapsedTime().asSeconds() > 10.f && ShieldPotion) {
            ShieldPotion = false;
            AiPet->setAttackDamage(AiPet->getAttackDamage() * 2);
        }
        // drawing active bullets
        for (int i = 0; i < MaxbulletCount; i++) {
            if (activeBullets[i])
                window.draw(bullet[i]);
        }
        // moving fireball if exists
        if (userPet->getFireball()) {
            fireball.move({5, 0});
        }
        // claw ability timer
        if (ClawTimer.getElapsedTime().asSeconds() > 1.f)
            userPet->setClaw(false);
        // speed ability timer
        if (userPet->getIsSpeed()) {
            if (SpeedReset.getElapsedTime().asSeconds() > 2.f) {
                userPet->setSpeed(userPet->getSpeed() - userPet->getMove1());
                userPet->setIsSpeed(false);
            }
        }
        // stun timer
        if (AiPet->getStun()) {
            if (StunTimer.getElapsedTime().asSeconds() > userPet->getMove2()) {
                AiPet->setStun(false);
            }
        }
        // griffin stun timer
        if (AiPet->getGriffinStun()) {
            if (griffinStunTimer.getElapsedTime().asSeconds() > userPet->getMove2()) {
                AiPet->setGriffinStun(false);
            }
        }
        // phoenix revive ability use
        if (userPet->getIsRevive() && userPet->getHealth() < 0) {
            userPet->setHealth(StartHealth);
            userPet->setIsRevive(false);
        }
        // game end when any of the pet dies
        if (!userPet->getIsRevive()) {
            if (*userPet < 0) {
                window.clear();
                sf::Texture losingScreen;
                if (!losingScreen.loadFromFile("assets/images/LosePage.png")) {
                    std::cout << "Image load failure";
                    exit(0);
                }
                sf::Sprite loss(losingScreen);
                window.draw(loss);
                window.display();
                sf::sleep(sf::seconds(5));
                return;
            }
        }
        if (*AiPet < 0) {
            window.clear();
            sf::Texture WinScreen;
            if (!WinScreen.loadFromFile("assets/images/WinPage.png")) {
                std::cout << "Image load failure";
                exit(0);
            }
            sf::Sprite Win(WinScreen);
            sf::Text popupText(font, "", 28);
            popupText.setFillColor(sf::Color::White);
            popupText.setStyle(sf::Text::Bold);
            popupText.setPosition({GameConstants::X_RESOLUTION / 2.4f, GameConstants::Y_RESOLUTION / 1.3f});
            user.setCurrency(user.getCurrency() + int(Prize * level));
            popupText.setString("You Got " + std::to_string(int(Prize * level)) + " Game Currency");
            window.draw(Win);
            window.draw(popupText);
            window.display();
            sf::sleep(sf::seconds(5));
            return;
        }

        // game ends if time exceeds
        if (GameClock.getElapsedTime().asSeconds() > TimeLimit) {
            if (userPet->getHealth() < AiPet->getHealth()) {
                window.clear();
                sf::Texture losingScreen;
                if (!losingScreen.loadFromFile("assets/images/LosePage.png")) {
                    std::cout << "Image load failure";
                    exit(0);
                }
                sf::Sprite loss(losingScreen);
                window.draw(loss);
                window.display();
                sf::sleep(sf::seconds(5));
                return;
            }
            if (userPet->getHealth() >= AiPet->getHealth()) {
                window.clear();
                sf::Texture WinScreen;
                if (!WinScreen.loadFromFile("assets/images/WinPage.png")) {
                    std::cout << "Image load failure";
                    exit(0);
                }
                sf::Sprite Win(WinScreen);
                sf::Text popupText(font, "", 28);
                popupText.setFillColor(sf::Color::White);
                popupText.setStyle(sf::Text::Bold);
                popupText.setPosition({GameConstants::X_RESOLUTION / 2.4f, GameConstants::Y_RESOLUTION / 1.3f});
                user.setCurrency(user.getCurrency() + int(Prize * level));
                popupText.setString("You Got " + std::to_string(int(Prize * level)) + " Game Currency");
                window.draw(Win);
                window.draw(popupText);
                window.display();
                sf::sleep(sf::seconds(5));
                return;
            }
        }

        // unicorn shield ability timer
        if (userPet->getIsShield() && shieldTimer.getElapsedTime().asSeconds() > 5.f) {
            AiPet->setAttackDamage(AiPet->getAttackDamage() + userPet->getMove2());
            userPet->setIsShield(false);
        }
        // buff potion timer
        if (isBuff)
            if (BuffTimer.getElapsedTime().asSeconds() > 5.f) {
                userPet->setAttackDamage(userPet->getAttackDamage() - 20);
                userPet->setSpeed(userPet->getSpeed() - 5);
                isBuff = false;
            }
        // spawn random potion after every 10 sec
        if (potionTimer.getElapsedTime().asSeconds() > 10.f) {
            do {
                float x = rand() % (1280 - 64);
                float y = rand() % (720 - 64);
                potion.setPosition({x, y});
            } while (checkCollision(potion, sprite_wall1, sprite_wall2, sprite_stone1, sprite_stone2));

            showPotion = true;
            potionTimer.restart();
        }
        // collect potion and do task of any random potion
        if (rectsIntersect(potion.getGlobalBounds(), userSprite.getGlobalBounds()) && showPotion) {
            showPotion = false;
            int num = rand() % 4 + 1;
            if (num == 1) {
                popupClock.restart();
                popupText.setString("Mana Potion Collected");
                showPopup = true;
                ManaPotion = true;
            }
            if (num == 2) {
                popupClock.restart();
                popupText.setString("Heal Potion Collected");
                showPopup = true;
                if (userPet->getHealth() < StartHealth)
                    userPet->setHealth(StartHealth);
            }
            if (num == 3) {
                popupClock.restart();
                popupText.setString("Buff Potion Collected");
                showPopup = true;
                userPet->setAttackDamage(userPet->getAttackDamage() + 20);
                userPet->setSpeed(userPet->getSpeed() + 5);
                BuffTimer.restart();
                isBuff = true;
            }
            if (num == 4) {
                popupClock.restart();
                popupText.setString("Shield Potion Collected");
                showPopup = true;
                AiPet->setAttackDamage(AiPet->getAttackDamage() * 0.5);
                ShieldPotionClock.restart();
                ShieldPotion = true;
            }
            potionTimer.restart();
        }

        clock.setString(std::to_string(int(TimeLimit - GameClock.getElapsedTime().asSeconds())));
        if (userPet->getClaw())
            window.draw(claw);
        if (userPet->getFireball())
            window.draw(fireball);
        window.draw(sprite_stone1);
        window.draw(sprite_stone2);
        window.draw(sprite_wall1);
        window.draw(sprite_wall2);
        window.draw(clock);
        for (int i = 0; i < MaxAIBullets; ++i) {
            if (activeAIBullets[i])
                window.draw(aiBullet[i]);
        }
        if (showPotion)
            window.draw(potion);

        window.draw(aiSprite);
        window.draw(userSprite);
        window.draw(AiHealth);
        window.draw(userHealth);
        if (showPopup && popupClock.getElapsedTime() > sf::seconds(2)) {
            showPopup = false;
        }
        if (showPopup)
            window.draw(popupText);

        window.display();
    }
}

