#include "../include/Guild.h"
#include "../include/Pet.h"

Guild::Guild() : guildName(""), guildID("") {
    Tank = nullptr;
    Healer = nullptr;
    DamageDealer = nullptr;
    Striker = nullptr;
}

Guild::Guild(Pet* P1, Pet* P2, Pet* P3, Pet* P4, std::string GuildName, std::string guildID)
    : guildName(GuildName), guildID(guildID) {
    Tank = P1;
    Healer = P2;
    DamageDealer = P3;
    Striker = P4;
}

Guild::Guild(const Guild& other) {
    Tank = other.Tank->copy();
    Healer = other.Healer->copy();
    DamageDealer = other.DamageDealer->copy();
    Striker = other.Striker->copy();
    GuildScore = other.GuildScore;
    guildName = other.guildName;
    guildID = other.guildID;
}

void Guild::setGuildScore(int a) {
    GuildScore = a;
}

int Guild::getGuildScore() const {
    return GuildScore;
}

void Guild::setHealer(Pet* P) {
    Healer = P;
}

void Guild::setTank(Pet* P) {
    Tank = P;
}

void Guild::setDamageDealer(Pet* P) {
    DamageDealer = P;
}

void Guild::setStriker(Pet* P) {
    Striker = P;
}

void Guild::setName(std::string name) {
    guildName = name;
}

void Guild::setID(std::string ID) {
    guildID = ID;
}

std::string Guild::getName() const {
    return guildName;
}

std::string Guild::getId() const {
    return guildID;
}

Pet* Guild::getHealer() const {
    return Healer;
}

Pet* Guild::getTank() const {
    return Tank;
}

Pet* Guild::getDamageDealer() const {
    return DamageDealer;
}

Pet* Guild::getStriker() const {
    return Striker;
}

bool Guild::operator>(const Guild& g) const {
    return GuildScore > g.GuildScore;
}

Guild& Guild::operator=(const Guild& other) {
    Tank = other.Tank->copy();
    Healer = other.Healer->copy();
    DamageDealer = other.DamageDealer->copy();
    Striker = other.Striker->copy();
    GuildScore = other.GuildScore;
    guildName = other.guildName;
    guildID = other.guildID;
    return *this;
}

