#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Pet {
protected:
    std::string name;
    int speed;
    int petID;
    int health;  // Made accessible for derived classes to modify via setters
    int Attackdamage;
    int DefensePower;
    static const int MaxLevel = 10;
    int CurrentLevel = 1;
    bool isShield = false;
    bool isStun = false;
    bool isRevive = false;
    bool isFireBall = false;
    bool isSpeed = false;
    bool isClaw = false;
    bool griffinStun = false;
    int TrainingPoints = 0;

public:
    Pet(std::string name, int speed, int petID, int health, int Attackdamage, int DefensePower);
    
    // Getters
    std::string getName() const { return name; }
    int getSpeed() const { return speed; }
    int getPetID() const { return petID; }
    int getHealth() const { return health; }
    int getAttackDamage() const { return Attackdamage; }
    int getDefensePower() const { return DefensePower; }
    int getCurrentLevel() const { return CurrentLevel; }
    bool getIsRevive() const { return isRevive; }
    bool getIsShield() const { return isShield; }
    bool getGriffinStun() const { return griffinStun; }
    int getTrainingPoints() const { return TrainingPoints; }
    int getMaxLevel() const { return MaxLevel; }
    bool getFireball() const { return isFireBall; }
    bool getIsSpeed() const { return isSpeed; }
    bool getClaw() const { return isClaw; }
    bool getStun() const { return isStun; }
    
    // Setters
    void setName(std::string n) { name = n; }
    void setSpeed(int s) { speed = s; }
    void setPetID(int id) { petID = id; }
    void setHealth(int h) { health = h; }
    void setAttackDamage(int dmg) { Attackdamage = dmg; }
    void setDefensePower(int def) { DefensePower = def; }
    void setCurrentLevel(int lvl) { CurrentLevel = lvl; }
    void setIsRevive(bool alive) { isRevive = alive; }
    void setTrainingPoints(int tp) { TrainingPoints = tp; }
    void setFireball(bool a) { isFireBall = a; }
    void setIsSpeed(bool a) { isSpeed = a; }
    void setClaw(bool a) { isClaw = a; }
    void setStun(bool a) { isStun = a; }
    void setIsShield(bool a) { isShield = a; }
    void setGriffinStun(bool status) { griffinStun = status; }
    
    // Pure virtual functions
    virtual void setMove1(int) = 0;
    virtual int getMove1() const = 0;
    virtual void setMove2(int) = 0;
    virtual int getMove2() const = 0;
    virtual Pet* copy() = 0;
    virtual int getType() = 0;
    virtual void executeMove1(sf::RenderWindow& window, Pet* enemy) = 0;
    virtual void executeMove2(sf::RenderWindow& window, Pet* enemy) = 0;
    
    bool operator<(const int temp) {
        return health < temp;
    }
    
    Pet& operator=(const Pet& other);
};

