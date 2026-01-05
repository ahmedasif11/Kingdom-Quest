#pragma once

#include "../Arena.h"
#include "../Guild.h"
#include "../Player.h"
#include "../Obstacles.h"
#include <SFML/Graphics.hpp>

class guildVguild : public Arena {
private:
    Guild userGuild;
    Guild AiGuild;

public:
    guildVguild(Wall& w1, Wall& w2, Stone& s1, Stone& s2);
    
    void setUserGuild(Guild G);
    void setAiGuild(Guild G);
    
    void Battle(sf::RenderWindow& window, sf::Font& font, Player& user);
};

