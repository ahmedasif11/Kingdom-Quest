#pragma once

#include "Pet.h"
#include <string>

class Pet;  // Forward declaration

class Guild {
private:
    Pet* Tank;
    Pet* Healer;
    Pet* DamageDealer;
    Pet* Striker;
    std::string guildName;
    std::string guildID;
    int GuildScore = 0;

public:
    Guild();
    Guild(Pet* P1, Pet* P2, Pet* P3, Pet* P4, std::string GuildName, std::string guildID);
    Guild(const Guild& other);
    
    void setGuildScore(int a);
    int getGuildScore() const;
    void setHealer(Pet* P);
    void setTank(Pet* P);
    void setDamageDealer(Pet* P);
    void setStriker(Pet* P);
    void setName(std::string name);
    void setID(std::string ID);
    std::string getName() const;
    std::string getId() const;
    Pet* getHealer() const;
    Pet* getTank() const;
    Pet* getDamageDealer() const;
    Pet* getStriker() const;
    
    bool operator>(const Guild& g) const;
    Guild& operator=(const Guild& other);
};

