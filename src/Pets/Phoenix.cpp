#include "../../include/Pets/Phoenix.h"

Phoenix::Phoenix(std::string name, int speed, int petID, int health, int Attackdamage, 
                 int DefensePower, int HealAmount)
    : Pet(name, speed, petID, health, Attackdamage, DefensePower),
      HealAmount(HealAmount) {}

void Phoenix::setMove1(int amt) { HealAmount = amt; }
int Phoenix::getMove1() const { return HealAmount; }

void Phoenix::setMove2(int flag) { didRebirth = flag; }
int Phoenix::getMove2() const { return didRebirth; }

Pet* Phoenix::copy() {
    return new Phoenix(*this);
}

Phoenix& Phoenix::operator=(const Phoenix& other) {
    Pet::operator=(other);
    HealAmount = other.HealAmount;
    didRebirth = other.didRebirth;
    return *this;
}

int Phoenix::getType() {
    return petID;
}

void Phoenix::executeMove1(sf::RenderWindow& window, Pet* enemy) {
    setHealth(getHealth() + HealAmount);
}

void Phoenix::executeMove2(sf::RenderWindow& window, Pet* enemy) {
    if (didRebirth == 0)
        isRevive = true;
    didRebirth = 1;
}

