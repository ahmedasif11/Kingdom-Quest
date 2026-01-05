#include "../../include/Pets/Griffin.h"

Griffin::Griffin(std::string name, int speed, int petID, int health, int Attackdamage, 
                 int DefensePower, int Clawdamage, int BombStunMoves)
    : Pet(name, speed, petID, health, Attackdamage, DefensePower),
      Clawdamage(Clawdamage), BombStunMoves(BombStunMoves) {}

void Griffin::setMove1(int dmg) { Clawdamage = dmg; }
int Griffin::getMove1() const { return Clawdamage; }

void Griffin::setMove2(int stun) { BombStunMoves = stun; }
int Griffin::getMove2() const { return BombStunMoves; }

Griffin& Griffin::operator=(const Griffin& other) {
    Pet::operator=(other);
    Clawdamage = other.Clawdamage;
    BombStunMoves = other.BombStunMoves;
    return *this;
}

Pet* Griffin::copy() {
    return new Griffin(*this);
}

int Griffin::getType() {
    return petID;
}

void Griffin::executeMove1(sf::RenderWindow& window, Pet* enemy) {
    isClaw = true;
}

void Griffin::executeMove2(sf::RenderWindow& window, Pet* enemy) {
    enemy->setGriffinStun(true);
}

