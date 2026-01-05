#include "../../include/Pets/Unicorn.h"

Unicorn::Unicorn(std::string name, int speed, int petID, int health, int Attackdamage, 
                 int DefensePower, int SpeedBurst, int ShieldPower)
    : Pet(name, speed, petID, health, Attackdamage, DefensePower),
      SpeedBurst(SpeedBurst), ShieldPower(ShieldPower) {}

void Unicorn::setMove1(int burst) { SpeedBurst = burst; }
int Unicorn::getMove1() const { return SpeedBurst; }

void Unicorn::setMove2(int power) { ShieldPower = power; }
int Unicorn::getMove2() const { return ShieldPower; }

Unicorn& Unicorn::operator=(const Unicorn& other) {
    Pet::operator=(other);
    SpeedBurst = other.SpeedBurst;
    ShieldPower = other.ShieldPower;
    return *this;
}

Pet* Unicorn::copy() {
    return new Unicorn(*this);
}

int Unicorn::getType() {
    return petID;
}

void Unicorn::executeMove1(sf::RenderWindow& window, Pet* enemy) {
    speed += SpeedBurst;
    isSpeed = true;
}

void Unicorn::executeMove2(sf::RenderWindow& window, Pet* enemy) {
    isShield = true;
    enemy->setAttackDamage(enemy->getAttackDamage() - ShieldPower);
}

