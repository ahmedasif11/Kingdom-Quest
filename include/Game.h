#pragma once

#include "Player.h"
#include "Shop.h"
#include "TrainingCamp.h"
#include "BattleModes/oneVone.h"
#include "BattleModes/twoVtwo.h"
#include "BattleModes/guildVguild.h"
#include "Pets/Dragon.h"
#include "Pets/Phoenix.h"
#include "Pets/Unicorn.h"
#include "Pets/Griffin.h"
#include "Obstacles.h"
#include "Utils.h"
#include "Constants.h"
#include "SoundManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>

class Game {
public:
    void StartGame();
    
private:
    void UpgradePet(sf::RenderWindow& window, Player& user, sf::Text popupText, sf::Font& font);
    void showManual(sf::RenderWindow& window);
    void AskPetfor1V1(sf::RenderWindow& window, Player& user, sf::Text& popupText, sf::Font& font, oneVone& Battle1);
    void AskPetfor2V2(sf::RenderWindow& window, Player& user, sf::Text& popupText, sf::Font& font, twoVtwo& Battle2);
    void AskBattleGuild(sf::RenderWindow& window, Player& user, sf::Text& popupText, sf::Font& font, guildVguild& BattleG);
    void GuildManage(sf::RenderWindow& window, sf::Font& font, Player& user, sf::Text& popupText, 
                     sf::Clock& popupClock, bool& showPopup, Dragon& D, Phoenix& P, Unicorn& U, Griffin& G);
    void Training(sf::RenderWindow& window, sf::Font& font, TrainingCamp& camp, sf::Text& popupText, 
                  Dragon& D, Phoenix& P, Unicorn& U, Griffin& G);
    void showShop(sf::RenderWindow& window, Shop& items, sf::Font& font, Player& user, sf::Text& popupText);
    void AskBattleType(sf::RenderWindow& window, Player& user, sf::Text& popupText, sf::Font& font, 
                       oneVone& Battle1, twoVtwo& Battle2, guildVguild& BattleG);
    bool askNewGame(sf::RenderWindow& window);
    void ShowLeaderboard(sf::RenderWindow& window, sf::Font& font, Player& user);
    std::string getPetNameFromID(int id);
};

