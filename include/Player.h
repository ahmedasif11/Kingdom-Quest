#pragma once

#include "Pet.h"
#include "Guild.h"
#include "Constants.h"
#include <string>

class Pet;  // Forward declaration
class Guild;  // Forward declaration

class Player {
private:
    Pet** PlayerPets;
    int Currency = 500;
    int NoOfHealingPoints = 0;
    int NoofManaPotions = 0;
    int NoOfBuffitems = 0;
    int NoOfShields = 0;
    static const int MaxGuilds = 5;
    Guild* guilds;
    int NoOfGuilds = 0;
    int ID;
    std::string name;

public:
    Player(Pet* P1, Pet* P2, Pet* P3, Pet* P4);
    ~Player();
    
    void setID(int id);
    int getID() const;
    void SortGuilds();
    void setName(const std::string& newName);
    std::string getName() const;
    
    void setCurrency(int amount);
    void setNoOfHealingPotions(int points);
    void setNoOfManaPotions(int potions);
    void setNoOfBuffItems(int items);
    void setNoOfShields(int shields);
    void setNoOfGuilds(int count);
    
    int getCurrency() const;
    int getNoOfHealingPotions() const;
    int getNoOfManaPotions() const;
    int getNoOfBuffItems() const;
    int getNoOfShields() const;
    int getNoOfGuilds() const;
    int getMaxGuilds() const;
    
    void RemoveGuild(int index);
    Guild* GetGuild(int index);
    Guild* GetGuildById(std::string id);
    Pet* getPet(int index);
};

