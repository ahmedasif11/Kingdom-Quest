#include "../../include/Pets/Dragon.h"

Dragon::Dragon(std::string name, int speed, int petID, int health, int Attackdamage, 
               int DefensePower, int FireballDamage, int RoarStunTime)
    : Pet(name, speed, petID, health, Attackdamage, DefensePower),
      FireballDamage(FireballDamage), RoarStunTime(RoarStunTime) {}

void Dragon::setMove1(int dmg) { FireballDamage = dmg; }
int Dragon::getMove1() const { return FireballDamage; }

void Dragon::setMove2(int time) { RoarStunTime = time; }
int Dragon::getMove2() const { return RoarStunTime; }

Dragon& Dragon::operator=(const Dragon& other) {
    Pet::operator=(other);
    FireballDamage = other.FireballDamage;
    RoarStunTime = other.RoarStunTime;
    return *this;
}

Pet* Dragon::copy() {
    return new Dragon(*this);
}

int Dragon::getType() {
    return petID;
}

void Dragon::executeMove1(sf::RenderWindow& window, Pet* enemy) {
    isFireBall = true;
}

void Dragon::executeMove2(sf::RenderWindow& window, Pet* enemy) {
    enemy->setStun(true);
}

