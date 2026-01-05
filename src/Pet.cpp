#include "../include/Pet.h"

Pet::Pet(std::string name, int speed, int petID, int health, int Attackdamage, int DefensePower)
    : name(name), speed(speed), petID(petID), health(health), Attackdamage(Attackdamage), DefensePower(DefensePower) {}

Pet& Pet::operator=(const Pet& other) {
    name = other.name;
    speed = other.speed;
    petID = other.petID;
    health = other.health;
    Attackdamage = other.Attackdamage;
    DefensePower = other.DefensePower;
    CurrentLevel = other.CurrentLevel;
    isShield = other.isShield;
    isStun = other.isStun;
    isRevive = other.isRevive;
    isFireBall = other.isFireBall;
    isSpeed = other.isSpeed;
    isClaw = other.isClaw;
    griffinStun = other.griffinStun;
    TrainingPoints = other.TrainingPoints;
    return *this;
}

