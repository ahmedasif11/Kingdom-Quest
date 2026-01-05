#include "../include/Player.h"
#include "../include/Pet.h"
#include "../include/Guild.h"

Player::Player(Pet* P1, Pet* P2, Pet* P3, Pet* P4) {
    PlayerPets = new Pet*[4];
    PlayerPets[0] = P1;
    PlayerPets[1] = P2;
    PlayerPets[2] = P3;
    PlayerPets[3] = P4;
    guilds = new Guild[MaxGuilds];
}

Player::~Player() {
    delete[] PlayerPets;
    delete[] guilds;
}

void Player::setID(int id) {
    ID = id;
}

int Player::getID() const {
    return ID;
}

void Player::SortGuilds() {
    for (int i = 0; i < NoOfGuilds - 1; ++i) {
        for (int j = 0; j < NoOfGuilds - i - 1; ++j) {
            if (guilds[j + 1] > guilds[j]) {
                Guild temp = guilds[j];
                guilds[j] = guilds[j + 1];
                guilds[j + 1] = temp;
            }
        }
    }
}

void Player::setName(const std::string& newName) {
    name = newName;
}

std::string Player::getName() const {
    return name;
}

void Player::setCurrency(int amount) { Currency = amount; }
void Player::setNoOfHealingPotions(int points) { NoOfHealingPoints = points; }
void Player::setNoOfManaPotions(int potions) { NoofManaPotions = potions; }
void Player::setNoOfBuffItems(int items) { NoOfBuffitems = items; }
void Player::setNoOfShields(int shields) { NoOfShields = shields; }
void Player::setNoOfGuilds(int count) { NoOfGuilds = count; }

int Player::getCurrency() const { return Currency; }
int Player::getNoOfHealingPotions() const { return NoOfHealingPoints; }
int Player::getNoOfManaPotions() const { return NoofManaPotions; }
int Player::getNoOfBuffItems() const { return NoOfBuffitems; }
int Player::getNoOfShields() const { return NoOfShields; }
int Player::getNoOfGuilds() const { return NoOfGuilds; }
int Player::getMaxGuilds() const { return MaxGuilds; }

void Player::RemoveGuild(int index) {
    for (int j = index; j < NoOfGuilds - 1; j++) {
        guilds[j] = guilds[j + 1];
    }
    NoOfGuilds--;
}

Guild* Player::GetGuild(int index) {
    return &guilds[index];
}

Guild* Player::GetGuildById(std::string id) {
    for (int i = 0; i < NoOfGuilds; i++) {
        if (guilds[i].getId() == id)
            return &guilds[i];
    }
    return nullptr;
}

Pet* Player::getPet(int index) {
    return PlayerPets[index];
}

