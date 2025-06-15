//In leaderBoard Press Enter to go back to the previous page

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
using namespace std;
using namespace sf;
const int X_RESOLUTION = 1280;
const int Y_RESOLUTION = 720;
const int CELL_SIZE = 64;
const int COLS = X_RESOLUTION / CELL_SIZE;
const int ROWS = Y_RESOLUTION / CELL_SIZE;
SoundBuffer clickBuffer;
Sound clickSound;

int grid[ROWS][COLS];
class Pet
{
protected:
    string name;
    int speed;
    int petID;
    int health;
    int Attackdamage;
    int DefensePower;
    const int MaxLevel = 10;
    int CurrentLevel = 1;
    bool isShield = false;
    bool isStun = false;
    bool isRevive = false;
    bool isFireBall = false;
    bool isSpeed = false;
    bool isClaw = false;
    bool griffinStun = false;
    int TrainingPoints = 0;

public:
    Pet(string name, int speed, int petID, int health, int Attackdamage, int DefensePower)
        : name(name), speed(speed), petID(petID), health(health), Attackdamage(Attackdamage), DefensePower(DefensePower) {}
    // getters and setters
    string getName() const { return name; }
    int getSpeed() const { return speed; }
    int getPetID() const { return petID; }
    int getHealth() const { return health; }
    int getAttackDamage() const { return Attackdamage; }
    int getDefensePower() const { return DefensePower; }
    int getCurrentLevel() const { return CurrentLevel; }
    bool getIsRevive() const { return isRevive; }
    bool getIsShield() const { return isShield; }
    bool getGriffinStun() const { return griffinStun; }
    int getTrainingPoints() const { return TrainingPoints; }
    int getMaxLevel() const { return MaxLevel; }
    bool getFireball() const { return isFireBall; }
    bool getIsSpeed() const { return isSpeed; }
    bool getClaw() const { return isClaw; }
    bool getStun() const { return isStun; }
    void setName(string n) { name = n; }
    void setSpeed(int s) { speed = s; }
    void setPetID(int id) { petID = id; }
    void setHealth(int h) { health = h; }
    void setAttackDamage(int dmg) { Attackdamage = dmg; }
    void setDefensePower(int def) { DefensePower = def; }
    void setCurrentLevel(int lvl) { CurrentLevel = lvl; }
    void setIsRevive(bool alive) { isRevive = alive; }
    void setTrainingPoints(int tp) { TrainingPoints = tp; }
    void setFireball(bool a) { isFireBall = a; }
    void setIsSpeed(bool a) { isSpeed = a; }
    void setClaw(bool a) { isClaw = a; }
    void setStun(bool a) { isStun = a; }
    void setIsShield(bool a) { isShield = a; }
    void setGriffinStun(bool status) { griffinStun = status; }
    // pure virtual functions to be used in derived classes
    virtual void setMove1(int) = 0;
    virtual int getMove1() const = 0;
    virtual void setMove2(int) = 0;
    virtual int getMove2() const = 0;
    virtual Pet *copy() = 0;
    virtual int getType() = 0;
    virtual void executeMove1(RenderWindow &window, Pet *enemy) = 0;
    virtual void executeMove2(RenderWindow &window, Pet *enemy) = 0;

    bool operator<(const int temp)
    {
        return health < temp;
    }

    // pet copy assignment operator
    Pet &operator=(const Pet &other)
    {
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
};
class Dragon : public Pet
{
private:
    int FireballDamage;
    int RoarStunTime;

public:
    Dragon(string name = "", int speed = 0, int petID = 0, int health = 0, int Attackdamage = 0, int DefensePower = 0,
           int FireballDamage = 0, int RoarStunTime = 0)
        : Pet(name, speed, petID, health, Attackdamage, DefensePower),
          FireballDamage(FireballDamage), RoarStunTime(RoarStunTime) {}
    void setMove1(int dmg) override { FireballDamage = dmg; }
    int getMove1() const override { return FireballDamage; }

    void setMove2(int time) override { RoarStunTime = time; }
    int getMove2() const override { return RoarStunTime; }

    // Dragon copy assignment operator
    Dragon &operator=(const Dragon &other)
    {
        Pet::operator=(other);
        FireballDamage = other.FireballDamage;
        RoarStunTime = other.RoarStunTime;
        return *this;
    }

    Pet *copy() override
    {
        return new Dragon(*this);
    }
    int getType()
    {
        return petID;
    }
    void executeMove1(RenderWindow &window, Pet *enemy) override
    {
        isFireBall = true;
    }
    void executeMove2(RenderWindow &window, Pet *enemy) override
    {
        enemy->setStun(true);
    }
};
class Phoenix : public Pet
{
private:
    int HealAmount;
    int didRebirth = 0;

public:
    Phoenix(string name = "", int speed = 0, int petID = 0, int health = 0, int Attackdamage = 0, int DefensePower = 0,
            int HealAmount = 0)
        : Pet(name, speed, petID, health, Attackdamage, DefensePower),
          HealAmount(HealAmount) {}
    void setMove1(int amt) override { HealAmount = amt; }
    int getMove1() const override { return HealAmount; }
    void setMove2(int flag) override { didRebirth = flag; }
    int getMove2() const override { return didRebirth; }
    Pet *copy() override
    {
        return new Phoenix(*this);
    }

    // Phoenix Copy assignment operator
    Phoenix &operator=(const Phoenix &other)
    {

        Pet::operator=(other);
        HealAmount = other.HealAmount;
        didRebirth = other.didRebirth;

        return *this;
    }

    int getType() override
    {
        return petID;
    }
    void executeMove1(RenderWindow &window, Pet *enemy) override
    {
        health += HealAmount;
    }
    void executeMove2(RenderWindow &window, Pet *enemy) override
    {
        if (didRebirth == 0)
            isRevive = true;
        didRebirth = 1;
    }
};
class Unicorn : public Pet
{
private:
    int SpeedBurst;
    int ShieldPower;

public:
    Unicorn(string name = "", int speed = 0, int petID = 0, int health = 0, int Attackdamage = 0, int DefensePower = 0,
            int SpeedBurst = 0, int ShieldPower = 0)
        : Pet(name, speed, petID, health, Attackdamage, DefensePower),
          SpeedBurst(SpeedBurst), ShieldPower(ShieldPower) {}
    void setMove1(int burst) override { SpeedBurst = burst; }
    int getMove1() const override { return SpeedBurst; }

    void setMove2(int power) override { ShieldPower = power; }
    int getMove2() const override { return ShieldPower; }

    // Unicorn copy assignment operator
    Unicorn &operator=(const Unicorn &other)
    {

        Pet::operator=(other);
        SpeedBurst = other.SpeedBurst;
        ShieldPower = other.ShieldPower;

        return *this;
    }

    Pet *copy() override
    {
        return new Unicorn(*this);
    }
    int getType() override
    {
        return petID;
    }
    void executeMove1(RenderWindow &window, Pet *enemy) override
    {
        speed += SpeedBurst;
        isSpeed = true;
    }
    void executeMove2(RenderWindow &window, Pet *enemy) override
    {
        isShield = true;
        enemy->setAttackDamage(enemy->getAttackDamage() - ShieldPower);
    }
};
class Griffin : public Pet
{
private:
    int Clawdamage;
    int BombStunMoves;

public:
    Griffin(string name = "", int speed = 0, int petID = 0, int health = 0, int Attackdamage = 0, int DefensePower = 0,
            int Clawdamage = 0, int BombStunMoves = 0)
        : Pet(name, speed, petID, health, Attackdamage, DefensePower),
          Clawdamage(Clawdamage), BombStunMoves(BombStunMoves) {}
    void setMove1(int dmg) override { Clawdamage = dmg; }
    int getMove1() const override { return Clawdamage; }

    void setMove2(int stun) override { BombStunMoves = stun; }
    int getMove2() const override { return BombStunMoves; }

    // Griffin copy assignment operator
    Griffin &operator=(const Griffin &other)
    {

        Pet::operator=(other);
        Clawdamage = other.Clawdamage;
        BombStunMoves = other.BombStunMoves;

        return *this;
    }

    Pet *copy() override
    {
        return new Griffin(*this);
    }
    int getType() override
    {
        return petID;
    }
    void executeMove1(RenderWindow &window, Pet *enemy) override
    {
        isClaw = true;
    }
    void executeMove2(RenderWindow &window, Pet *enemy) override
    {
        enemy->setGriffinStun(true);
    }
};
class Guild
{
private:
    Pet *Tank;
    Pet *Healer;
    Pet *DamageDealer;
    Pet *Striker;
    string guildName;
    string guildID;
    int GuildScore = 0;

public:
    Guild() : guildName(""), guildID("")
    {
        Tank = nullptr;
        Healer = nullptr;
        DamageDealer = nullptr;
        Striker = nullptr;
    }
    Guild(Pet *P1, Pet *P2, Pet *P3, Pet *P4, string GuildName, string guildID)
        : guildName(GuildName), guildID(guildID)
    {
        Tank = P1;
        Healer = P2;
        DamageDealer = P3;
        Striker = P4;
    }
    void setGuildScore(int a)
    {
        GuildScore = a;
    }
    int getGuildScore()
    {
        return GuildScore;
    }
    void setHealer(Pet *P)
    {
        Healer = P;
    }
    void setTank(Pet *P)
    {
        Tank = P;
    }
    void setDamageDealer(Pet *P)
    {
        DamageDealer = P;
    }
    void setStriker(Pet *P)
    {
        Striker = P;
    }
    void setName(string name)
    {
        guildName = name;
    }
    void setID(string ID)
    {
        guildID = ID;
    }
    string getName()
    {
        return guildName;
    }
    string getId()
    {
        return guildID;
    }
    Pet *getHealer()
    {
        return Healer;
    }
    Pet *getTank()
    {
        return Tank;
    }
    Pet *getDamageDealer()
    {
        return DamageDealer;
    }
    Pet *getStriker()
    {
        return Striker;
    }

    bool operator>(const Guild &g)
    {
        return GuildScore > g.GuildScore;
    }

    // copy constructor
    Guild(const Guild &other)
    {
        Tank = other.Tank->copy();
        Healer = other.Healer->copy();
        DamageDealer = other.DamageDealer->copy();
        Striker = other.Striker->copy();

        GuildScore = other.GuildScore;
        guildName = other.guildName;
        guildID = other.guildID;
    }
    // Guild copy assignment operator
    Guild &operator=(const Guild &other)
    {
        Tank = other.Tank->copy();
        Healer = other.Healer->copy();
        DamageDealer = other.DamageDealer->copy();
        Striker = other.Striker->copy();

        GuildScore = other.GuildScore;
        guildName = other.guildName;
        guildID = other.guildID;

        return *this;
    }
};
class Player
{
private:
    Pet **PlayerPets;
    int Currency = 500;
    int NoOfHealingPoints = 0;
    int NoofManaPotions = 0;
    int NoOfBuffitems = 0;
    int NoOfShields = 0;
    const int MaxGuilds = 5;
    Guild *guilds;
    int NoOfGuilds = 0;
    int ID;
    string name;

public:
    // Player pointing ti
    Player(Pet *P1, Pet *P2, Pet *P3, Pet *P4)
    {
        PlayerPets = new Pet *[4];
        PlayerPets[0] = P1;
        PlayerPets[1] = P2;
        PlayerPets[2] = P3;
        PlayerPets[3] = P4;

        guilds = new Guild[MaxGuilds];
    }
    void setID(int id)
    {
        ID = id;
    }
    int getID() const
    {
        return ID;
    }
    void SortGuilds()
    {
        for (int i = 0; i < NoOfGuilds - 1; ++i)
        {
            for (int j = 0; j < NoOfGuilds - i - 1; ++j)
            {
                if (guilds[j + 1] > guilds[j])
                {
                    Guild temp = guilds[j];
                    guilds[j] = guilds[j + 1];
                    guilds[j + 1] = temp;
                }
            }
        }
    }
    void setName(const string &newName)
    {
        name = newName;
    }

    string getName() const
    {
        return name;
    }
    void setCurrency(int amount) { Currency = amount; }
    void setNoOfHealingPotions(int points) { NoOfHealingPoints = points; }
    void setNoOfManaPotions(int potions) { NoofManaPotions = potions; }
    void setNoOfBuffItems(int items) { NoOfBuffitems = items; }
    void setNoOfShields(int shields) { NoOfShields = shields; }
    void setNoOfGuilds(int count) { NoOfGuilds = count; }

    int getCurrency() const { return Currency; }
    int getNoOfHealingPotions() const { return NoOfHealingPoints; }
    int getNoOfManaPotions() const { return NoofManaPotions; }
    int getNoOfBuffItems() const { return NoOfBuffitems; }
    int getNoOfShields() const { return NoOfShields; }
    int getNoOfGuilds() const { return NoOfGuilds; }
    int getMaxGuilds() const { return MaxGuilds; }

    // removes guild by shifting back the other guilds one index back and decreasing the no of guids by 1
    void RemoveGuild(int index)
    {
        for (int j = index; j < NoOfGuilds - 1; j++)
        {
            guilds[j] = guilds[j + 1];
        }
        NoOfGuilds--;
    }
    Guild *GetGuild(int index)
    {
        return &guilds[index];
    }
    Guild *GetGuildById(string id)
    {
        for (int i = 0; i < NoOfGuilds; i++)
        {
            if (guilds[i].getId() == id)
                return &guilds[i];
        }
        Guild *temp;
        return temp;
    }
    Pet *getPet(int index)
    {
        return PlayerPets[index];
    }
    ~Player()
    {
        delete[] PlayerPets;
        delete[] guilds;
    }
};
float AskLevel(RenderWindow &window)
{
    Texture LevelBg;
    if (!LevelBg.loadFromFile("Level.png"))
    {
        cout << "Image load Failure";
        exit(0);
    }
    Sprite bg(LevelBg);
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.key.code == Keyboard::E)
                return 1;
            if (event.key.code == Keyboard::M)
                return 1.5;
            if (event.key.code == Keyboard::H)
                return 2;
        }
        window.draw(bg);
        window.display();
    }
    return 1;
}
class TrainingCamp
{
private:
    int TokensGot;

public:
    void TrainPet(RenderWindow &window, Pet *P, int i, Text &popupText)
    {
        Clock deltaClock;
        float level = AskLevel(window);
        window.clear();
        float StoneSpeed = 7.f * level;
        bool showPopup = false;
        bool hasCollided = false;
        Clock popupClock;
        Time popupDuration = seconds(2);
        Texture BG;
        Texture PetTexture[3];
        Sprite PetSprite;
        Texture stone;
        const int NUM_STONES = 3; // Num of stones that appear at the screen at one time
        Clock timer;
        Sprite stones[NUM_STONES];
        if (!stone.loadFromFile("Stone.png"))
        {
            cout << "Image load Failure";
            exit(0);
        }
        if (!BG.loadFromFile("GuildWallpaper.png"))
        {
            cout << "Image load Failure";
            exit(0);
        }
        Sprite bg(BG);
        // Check which pet to import
        if (i == 1)
        {

            if (!PetTexture[0].loadFromFile("PhoenixTopView(0).png"))
            {
                exit(0);
            }
            if (!PetTexture[1].loadFromFile("PhoenixTopView(1).png"))
            {
                exit(0);
            }
            if (!PetTexture[2].loadFromFile("PhoenixTopView(2).png"))
            {
                exit(0);
            }
        }
        if (i == 2)
        {
            if (!PetTexture[0].loadFromFile("DragonTopView(0).png"))
            {
                exit(0);
            }
            if (!PetTexture[1].loadFromFile("DragonTopView(1).png"))
            {
                exit(0);
            }
            if (!PetTexture[2].loadFromFile("DragonTopView(2).png"))
            {
                exit(0);
            }
        }
        if (i == 3)
        {
            if (!PetTexture[0].loadFromFile("GriffinTopView(0).png"))
            {
                exit(0);
            }
            if (!PetTexture[1].loadFromFile("GriffinTopView(1).png"))
            {
                exit(0);
            }
            if (!PetTexture[2].loadFromFile("GriffinTopView(2).png"))
            {
                exit(0);
            }
        }
        if (i == 4)
        {
            if (!PetTexture[0].loadFromFile("UnicornTopView(0).png"))
            {
                exit(0);
            }
            if (!PetTexture[1].loadFromFile("UnicornTopView(1).png"))
            {
                exit(0);
            }
            if (!PetTexture[2].loadFromFile("UnicornTopView(2).png"))
            {
                exit(0);
            }
        }
        // setting the texture of each sprite of stone
        for (int i = 0; i < NUM_STONES; i++)
        {
            stones[i].setTexture(stone);
        }
        // fall the stones from random X position
        for (int i = 0; i < NUM_STONES; i++)
        {
            stones[i].setPosition(rand() % 1280, -100.f);
        }
        PetSprite.setPosition(10 * CELL_SIZE, 9 * CELL_SIZE);
        int currentFrame = 0;
        float frameTime = 0.2f;
        Clock frameClock;
        while (window.isOpen())
        {
            if (frameClock.getElapsedTime().asSeconds() > frameTime)
            {
                currentFrame++;
                if (currentFrame > 2)
                    currentFrame = 0;

                if (currentFrame == 0)
                {
                    PetSprite.setTexture(PetTexture[0]);
                }
                if (currentFrame == 1)
                {
                    PetSprite.setTexture(PetTexture[1]);
                }
                if (currentFrame == 2)
                {
                    PetSprite.setTexture(PetTexture[2]);
                }

                frameClock.restart();
            }
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
                // Control movement of pet (no movement on showpopup as popup is shown when game ends)
                if (event.key.code == Keyboard::Left && !showPopup)
                {
                    if (PetSprite.getPosition().x > 1.f)
                        PetSprite.move(-P->getSpeed(), 0);
                }
                if (event.key.code == Keyboard::Right && !showPopup)
                {
                    if (PetSprite.getPosition().x < 1100.f)
                        PetSprite.move(P->getSpeed(), 0);
                }
                if (event.key.code == Keyboard::Up && !showPopup)
                {
                    if (PetSprite.getPosition().y > 30.f)
                        PetSprite.move(0, -P->getSpeed());
                }
                if (event.key.code == Keyboard::Down && !showPopup)
                {
                    if (PetSprite.getPosition().y < 650.f)
                        PetSprite.move(0, P->getSpeed());
                }
            }
            for (int i = 0; i < NUM_STONES; i++)
            {
                if (!showPopup)
                    stones[i].move(0, StoneSpeed);

                // after stone falling completes reset its x position to a random x position and y position to the top so it can fall again
                if (stones[i].getPosition().y > 720)
                {
                    stones[i].setPosition(rand() % 1280, -100);
                }
            }
            if (!showPopup)
            {
                // checking collision of stones with pet
                for (int j = 0; j < NUM_STONES; j++)
                    if (stones[j].getGlobalBounds().intersects(PetSprite.getGlobalBounds()))
                    {
                        popupClock.restart();
                        showPopup = true;
                        P->setTrainingPoints(P->getTrainingPoints() + timer.getElapsedTime().asSeconds() * 10);
                        popupText.setString("Game Over! No Of Tokens U Got : " + to_string(int(timer.getElapsedTime().asSeconds() * 10)));
                    }
            }

            // Training Time is 20 sec,after 20 sec training ends
            if (timer.getElapsedTime().asSeconds() > 20)
            {
                popupClock.restart();
                showPopup = true;
                P->setTrainingPoints(P->getTrainingPoints() + timer.getElapsedTime().asSeconds() * 10 * level);
                popupText.setString("Game Over! No Of Tokens U Got : " + to_string(int(timer.getElapsedTime().asSeconds() * 10 * level)));
            }
            window.draw(bg);
            // draw stones
            for (int i = 0; i < NUM_STONES; i++)
            {
                window.draw(stones[i]);
            }

            // if showpopup then means game ended , display the game end msg and return
            if (showPopup)
            {
                window.draw(popupText);
                window.display();
                sleep(popupDuration);
                return;
            }

            window.draw(PetSprite);
            window.display();
        }
    }
};
class Shop
{
private:
    int PriceHeal;
    int PriceMana;
    int PriceBuff;
    int PriceShield;

public:
    Shop(int PriceHeal, int PriceMana, int PriceBuff, int PriceShield) : PriceHeal(PriceHeal), PriceBuff(PriceBuff), PriceMana(PriceMana), PriceShield(PriceShield) {}

    int getPriceHeal() const { return PriceHeal; }
    int getPriceMana() const { return PriceMana; }
    int getPriceBuff() const { return PriceBuff; }
    int getPriceShield() const { return PriceShield; }

    void setPriceHeal(int price) { PriceHeal = price; }
    void setPriceMana(int price) { PriceMana = price; }
    void setPriceBuff(int price) { PriceBuff = price; }
    void setPriceShield(int price) { PriceShield = price; }
};
class Obstacles
{
protected:
    float x_Position;
    float y_Position;

public:
    Obstacles(float x, float y)
        : x_Position(x), y_Position(y) {}
    float getXPosition() const { return x_Position; }
    float getYPosition() const { return y_Position; }

    void setXPosition(float x) { x_Position = x; }
    void setYPosition(float y) { y_Position = y; }
};
class Stone : public Obstacles
{
private:
public:
    Stone(float x=0, float y=0)
        : Obstacles(x, y) {}
    void display(RenderWindow &window, Texture &S, Sprite &pic) 
    {
        if (!S.loadFromFile("Stone.png"))
        {
            cout << "Failed to load Stone.png\n";
            exit(0);
        }
        pic.setPosition(x_Position, y_Position);
        pic.setTexture(S);
    }
};
class Wall : public Obstacles
{
private:
public:
    Wall(float x=0, float y=0)
        : Obstacles(x, y) {}
    void display(RenderWindow &window, Texture &W, Sprite &pic)
    {
        {
            if (!W.loadFromFile("Wall.png"))
            {
                cout << "Failed to load Wall.png\n";
                exit(0);
            }
            pic.setPosition(x_Position, y_Position);
            pic.setTexture(W);
        }
    }
};
bool checkCollision(Sprite &pet, Sprite &W1, Sprite &W2, Sprite &S1, Sprite &S2)
{
    // check collision of a sprite with the obstacles
    return pet.getGlobalBounds().intersects(W1.getGlobalBounds()) ||
           pet.getGlobalBounds().intersects(W2.getGlobalBounds()) ||
           pet.getGlobalBounds().intersects(S1.getGlobalBounds()) ||
           pet.getGlobalBounds().intersects(S2.getGlobalBounds());
}
class Arena
{
protected:
    Wall W1;
    Wall W2;
    Stone S1;
    Stone S2;
    int Prize = 200;
    float TimeLimit = 60.f;
    SoundBuffer hitBuffer;
    Sound hitSound;

public:
    Arena(Wall &w1, Wall &w2, Stone &s1, Stone &s2)
    {
        W1 = w1;
        W2 = w2;
        S1 = s1;
        S2 = s2;
        if (!hitBuffer.loadFromFile("hit.wav"))
        {
            cout << "Failed to load sound\n";
            exit(1);
        }
        hitSound.setBuffer(hitBuffer);
    }
};
class oneVone : public Arena
{
private:
    Pet *userPet = nullptr;
    Pet *AiPet = nullptr;

public:
    void setUserPet(Pet *temp)
    {
        userPet = temp;
    }
    void setAiPet(Pet *temp)
    {
        AiPet = temp;
    }
    Pet *getAiPet()
    {
        return AiPet;
    }
    Pet *getUserPet()
    {
        return userPet;
    }
    oneVone(Wall &w1, Wall &w2, Stone &s1, Stone &s2) : Arena(w1, w2, s1, s2) {}

    void Battle(RenderWindow &window, Font &font, Player &user)
    {

        float level = AskLevel(window);
        Text popupText;
        popupText.setFont(font);
        popupText.setCharacterSize(28);
        popupText.setFillColor(Color::White);
        popupText.setStyle(Text::Bold);
        popupText.setPosition(X_RESOLUTION / 2.5, Y_RESOLUTION / 3);
        bool showPopup = false;
        Clock popupClock;
        Clock GameClock;
        Clock aiMoveClock;
        float aiMoveInterval = 1.5f;
        Vector2f aiDirection(0, 0);
        Clock SpeedReset;
        Text userHealth("", font, 24), AiHealth("", font, 24), clock("", font, 24);
        clock.setPosition(10 * CELL_SIZE, 0.5 * CELL_SIZE);
        userHealth.setPosition(0.5 * CELL_SIZE, 0.5 * CELL_SIZE);
        AiHealth.setPosition(18 * CELL_SIZE, 0.5 * CELL_SIZE);
        Clock frameClock;
        Clock Move1Cooldown;
        Clock Move2Cooldown;
        int currentFrame = 0;
        float frameTime = 0.2f;
        Texture BG;
        Texture Fireball;
        Texture Claw;
        int MaxbulletCount = 10;
        bool activeBullets[10] = {0};
        Texture userTex1, userTex2, userTex3, Bullet;
        Texture aiTex1, aiTex2, aiTex3;
        Texture Aibullet;
        const int MaxAIBullets = 10;
        Sprite aiBullet[MaxAIBullets];
        bool activeAIBullets[MaxAIBullets] = {false};
        Clock aiFireClock;
        float aiFireInterval = 0.5f;
        Texture potionTex;
        // loading random arena bg
        int bgNum = rand() % 4 + 1;
        if (bgNum == 1)
            if (!BG.loadFromFile("BattleBG.png"))
            {
                cout << "Image load Failure";
                exit(0);
            }
        if (bgNum == 2)
            if (!BG.loadFromFile("BattleBG(1).png"))
            {
                cout << "Image load Failure";
                exit(0);
            }
        if (bgNum == 3)
            if (!BG.loadFromFile("BattleBG(2).png"))
            {
                cout << "Image load Failure";
                exit(0);
            }
        if (bgNum == 4)
            if (!BG.loadFromFile("BattleBG(3).png"))
            {
                cout << "Image load Failure";
                exit(0);
            }
        if (!potionTex.loadFromFile("Potion.png"))
        {
            cout << "Failed to load Potion.png\n";
            exit(0);
        }
        if (!Aibullet.loadFromFile("Bullet.png"))
        {
            cout << "Image load Failure";
            exit(0);
        }

        // loading other sprites
        if (!Claw.loadFromFile("Claw.png"))
        {
            cout << "Image load Failure";
            exit(0);
        }
        if (!Fireball.loadFromFile("FireBall.png"))
        {
            cout << "Image load Failure";
            exit(0);
        }
        if (!Bullet.loadFromFile("Bullet.png"))
        {
            cout << "Image load Failure";
            exit(0);
        }
        if (AiPet->getType() == 1)
        {
            if (!aiTex1.loadFromFile("DragonSide2.png"))
            {
                cout << "Failed to load DragonSide1.png\n";
                exit(0);
            }
            if (!aiTex2.loadFromFile("DragonSide2(0).png"))
            {
                cout << "Failed to load DragonSide1(0).png\n";
                exit(0);
            }
            if (!aiTex3.loadFromFile("DragonSide2(1).png"))
            {
                cout << "Failed to load DragonSide1(1).png\n";
                exit(0);
            }
        }
        if (AiPet->getType() == 2)
        {
            if (!aiTex1.loadFromFile("PhoenixSide2.png"))
            {
                cout << "Failed to load DragonSide1.png\n";
                exit(0);
            }
            if (!aiTex2.loadFromFile("PhoenixSide2(0).png"))
            {
                cout << "Failed to load DragonSide1(0).png\n";
                exit(0);
            }
            if (!aiTex3.loadFromFile("PhoenixSide2(1).png"))
            {
                cout << "Failed to load DragonSide1(1).png\n";
                exit(0);
            }
        }
        if (AiPet->getType() == 3)
        {
            if (!aiTex1.loadFromFile("UnicornSide2.png"))
            {
                cout << "Failed to load DragonSide1.png\n";
                exit(0);
            }
            if (!aiTex2.loadFromFile("UnicornSide2(0).png"))
            {
                cout << "Failed to load DragonSide1(0).png\n";
                exit(0);
            }
            if (!aiTex3.loadFromFile("UnicornSide2(1).png"))
            {
                cout << "Failed to load DragonSide1(1).png\n";
                exit(0);
            }
        }
        if (AiPet->getType() == 4)
        {
            if (!aiTex1.loadFromFile("GriffinSide2.png"))
            {
                cout << "Failed to load DragonSide1.png\n";
                exit(0);
            }
            if (!aiTex2.loadFromFile("GriffinSide2(0).png"))
            {
                cout << "Failed to load DragonSide1(0).png\n";
                exit(0);
            }
            if (!aiTex3.loadFromFile("GriffinSide2(1).png"))
            {
                cout << "Failed to load DragonSide1(1).png\n";
                exit(0);
            }
        }

        if (userPet->getType() == 1)
        {
            if (!userTex1.loadFromFile("DragonSide1.png"))
            {
                cout << "Failed to load DragonSide1.png\n";
                exit(0);
            }
            if (!userTex2.loadFromFile("DragonSide1(0).png"))
            {
                cout << "Failed to load DragonSide1(0).png\n";
                exit(0);
            }
            if (!userTex3.loadFromFile("DragonSide1(1).png"))
            {
                cout << "Failed to load DragonSide1(1).png\n";
                exit(0);
            }
        }
        if (userPet->getType() == 2)
        {
            if (!userTex1.loadFromFile("PhoenixSide1.png"))
            {
                cout << "Failed to load DragonSide1.png\n";
                exit(0);
            }
            if (!userTex2.loadFromFile("PhoenixSide1(0).png"))
            {
                cout << "Failed to load DragonSide1(0).png\n";
                exit(0);
            }
            if (!userTex3.loadFromFile("PhoenixSide1(1).png"))
            {
                cout << "Failed to load DragonSide1(1).png\n";
                exit(0);
            }
        }
        if (userPet->getType() == 3)
        {
            if (!userTex1.loadFromFile("UnicornSide1.png"))
            {
                cout << "Failed to load DragonSide1.png\n";
                exit(0);
            }
            if (!userTex2.loadFromFile("UnicornSide1(0).png"))
            {
                cout << "Failed to load DragonSide1(0).png\n";
                exit(0);
            }
            if (!userTex3.loadFromFile("UnicornSide1(1).png"))
            {
                cout << "Failed to load DragonSide1(1).png\n";
                exit(0);
            }
        }
        if (userPet->getType() == 4)
        {
            if (!userTex1.loadFromFile("GriffinSide1.png"))
            {
                cout << "Failed to load DragonSide1.png\n";
                exit(0);
            }
            if (!userTex2.loadFromFile("GriffinSide1(0).png"))
            {
                cout << "Failed to load DragonSide1(0).png\n";
                exit(0);
            }
            if (!userTex3.loadFromFile("GriffinSide1(1).png"))
            {
                cout << "Failed to load DragonSide1(1).png\n";
                exit(0);
            }
        }
        int StartHealth = userPet->getHealth();
        Clock ClawTimer;
        Clock StunTimer;
        Clock shieldTimer;
        Clock griffinStunTimer;
        Clock BuffTimer;
        bool isBuff = false;
        Sprite aiSprite;
        Sprite userSprite;
        Sprite fireball(Fireball);
        Sprite claw(Claw);
        bool ManaPotion = false;
        bool ShieldPotion = false;
        Clock ShieldPotionClock;
        aiSprite.setPosition(17 * CELL_SIZE, 5 * CELL_SIZE);
        userSprite.setPosition(1 * CELL_SIZE, 5 * CELL_SIZE);
        Texture stone1, stone2, wall1, wall2;
        Sprite sprite_stone1, sprite_stone2, sprite_wall1, sprite_wall2;
        Sprite bullet[MaxbulletCount];
        // setting bullet sprites
        for (int i = 0; i < MaxbulletCount; i++)
        {
            bullet[i].setTexture(Bullet);
            aiBullet[i].setTexture(Aibullet);
        }
        Sprite bg(BG);
        Sprite potion(potionTex);
        Clock potionTimer;
        bool showPotion = false;
        while (window.isOpen())
        {
            window.clear();
            userHealth.setString("HP : " + to_string(userPet->getHealth()));
            AiHealth.setString("HP : " + to_string(AiPet->getHealth()));
            W1.display(window, wall1, sprite_wall1);
            W2.display(window, wall2, sprite_wall2);
            S1.display(window, stone1, sprite_stone1);
            S2.display(window, stone2, sprite_stone2);

            // animation of pet movement
            if (frameClock.getElapsedTime().asSeconds() > frameTime)
            {
                currentFrame++;
                if (currentFrame > 2)
                    currentFrame = 0;

                if (currentFrame == 0)
                {
                    userSprite.setTexture(userTex1);
                    aiSprite.setTexture(aiTex1);
                }
                if (currentFrame == 1)
                {
                    userSprite.setTexture(userTex2);
                    aiSprite.setTexture(aiTex2);
                }
                if (currentFrame == 2)
                {
                    userSprite.setTexture(userTex3);
                    aiSprite.setTexture(aiTex3);
                }

                frameClock.restart();
            }
            Event event;
            while (window.pollEvent(event))
            {

                if (event.type == Event::Closed)
                    window.close();
                // When space key is released, fire a bullet if one is available
                if (event.type == Event::KeyReleased)
                    if (event.key.code == Keyboard::Space)
                    {

                        for (int i = 0; i < MaxbulletCount; ++i)
                        {
                            if (!activeBullets[i])
                            {
                                clickSound.play();
                                activeBullets[i] = true;
                                bullet[i].setPosition(userSprite.getPosition().x + 50, userSprite.getPosition().y + 40);
                                break;
                            }
                        }
                    }
                // Mana Potion on M
                if (event.key.code == Keyboard::M)
                {
                    if (user.getNoOfManaPotions() > 0)
                    {
                        clickSound.play();
                        user.setNoOfManaPotions(user.getNoOfManaPotions() - 1);
                        popupClock.restart();
                        popupText.setString("Mana Potion Used");
                        showPopup = true;
                        ManaPotion = true;
                    }
                }
                // Heal Potion on H
                if (event.key.code == Keyboard::H)
                {
                    if (user.getNoOfHealingPotions() > 0)
                    {
                        clickSound.play();
                        user.setNoOfHealingPotions(user.getNoOfHealingPotions() - 1);
                        popupClock.restart();
                        popupText.setString("Healing Potion Used");
                        showPopup = true;
                        if (userPet->getHealth() < StartHealth)
                            userPet->setHealth(StartHealth);
                    }
                }
                // Buff Potion on B
                if (event.key.code == Keyboard::B)
                {
                    if (user.getNoOfBuffItems() > 0)
                    {
                        clickSound.play();
                        user.setNoOfBuffItems(user.getNoOfBuffItems() - 1);
                        popupClock.restart();
                        popupText.setString("Buff Potion Used");
                        showPopup = true;
                        userPet->setAttackDamage(userPet->getAttackDamage() + 20);
                        userPet->setSpeed(userPet->getSpeed() + 5);
                        BuffTimer.restart();
                        isBuff = true;
                    }
                }
                // Shield on S
                if (event.key.code == Keyboard::S)
                {
                    if (user.getNoOfShields() > 0)
                    {
                        clickSound.play();
                        user.setNoOfShields(user.getNoOfShields() - 1);
                        popupClock.restart();
                        popupText.setString("Shield Potion Used");
                        showPopup = true;
                        AiPet->setAttackDamage(AiPet->getAttackDamage() * 0.5);
                        ShieldPotionClock.restart();
                        ShieldPotion = true;
                    }
                }
                // Second special Move on X
                if (event.key.code == Keyboard::X)
                {
                    // ALlow only if cooldown is over or Mana potion is used
                    if (Move2Cooldown.getElapsedTime().asSeconds() > 10.f || ManaPotion)
                    {
                        clickSound.play();
                        popupClock.restart();
                        popupText.setString("Ability 2 Used");
                        showPopup = true;
                        Move2Cooldown.restart();
                        userPet->executeMove2(window, AiPet);
                        StunTimer.restart();
                        griffinStunTimer.restart();
                        shieldTimer.restart();
                        ManaPotion = false;
                    }
                }
                // First special move on Z
                if (event.key.code == Keyboard::Z)
                {
                    // ALlow only if cooldown is over or Mana potion is used
                    if (Move1Cooldown.getElapsedTime().asSeconds() > 10.f || ManaPotion)
                    {
                        clickSound.play();
                        popupClock.restart();
                        popupText.setString("Ability 1 Used");
                        showPopup = true;
                        Move1Cooldown.restart();
                        userPet->executeMove1(window, AiPet);
                        SpeedReset.restart();
                        ClawTimer.restart();
                        if (userPet->getFireball())
                            fireball.setPosition(userSprite.getPosition().x + 50, userSprite.getPosition().y + 40);
                        if (userPet->getClaw())
                        {
                            claw.setPosition(userSprite.getPosition().x + 120, userSprite.getPosition().y + 40);
                            if (aiSprite.getPosition().x <= userSprite.getPosition().x + 150 && aiSprite.getPosition().x >= userSprite.getPosition().x)
                            {
                                AiPet->setHealth(AiPet->getHealth() - userPet->getMove1());
                            }
                        }
                        ManaPotion = false;
                    }
                }
                // movement of user by input
                Vector2f direction;
                if (event.key.code == Keyboard::Left)
                    direction = Vector2f(-userPet->getSpeed(), 0);
                if (event.key.code == Keyboard::Right)
                    direction = Vector2f(userPet->getSpeed(), 0);
                if (event.key.code == Keyboard::Up)
                    direction = Vector2f(0, -userPet->getSpeed());
                if (event.key.code == Keyboard::Down)
                    direction = Vector2f(0, userPet->getSpeed());

                // checking collision with obstacles
                Sprite tempSprite = userSprite;
                tempSprite.move(direction);

                if (tempSprite.getPosition().x >= 0 && tempSprite.getPosition().x <= 1100 &&
                    tempSprite.getPosition().y >= 0 && tempSprite.getPosition().y <= 580 &&
                    !checkCollision(tempSprite, sprite_wall1, sprite_wall2, sprite_stone1, sprite_stone2))
                    userSprite.move(direction);
            }
            // random ai movement after some time
            if (aiMoveClock.getElapsedTime().asSeconds() > aiMoveInterval)
            {
                int dir = rand() % 4;

                switch (dir)
                {
                case 0:
                    aiDirection = Vector2f(-AiPet->getSpeed(), 0);
                    break;
                case 1:
                    aiDirection = Vector2f(AiPet->getSpeed(), 0);
                    break;
                case 2:
                    aiDirection = Vector2f(0, -AiPet->getSpeed());
                    break;
                case 3:
                    aiDirection = Vector2f(0, AiPet->getSpeed());
                    break;
                }

                aiMoveClock.restart();
            }
            // check ai collision with obstacles before movement
            Sprite tempAI = aiSprite;
            tempAI.move(aiDirection);
            if (tempAI.getPosition().x >= 0 && tempAI.getPosition().x <= 1100 &&
                tempAI.getPosition().y >= 0 && tempAI.getPosition().y <= 580 &&
                !checkCollision(tempAI, sprite_wall1, sprite_wall2, sprite_stone1, sprite_stone2))
            {
                aiSprite.move(aiDirection);
            }
            // check collision of user bullet with obstacles
            for (int i = 0; i < MaxbulletCount; i++)
                if (activeBullets[i] == true)
                    if (checkCollision(bullet[i], sprite_wall1, sprite_wall2, sprite_stone1, sprite_stone2) || bullet[i].getPosition().x > 1270)
                    {
                        activeBullets[i] = false;
                    }

            // check collision of user bullet with ai pet
            for (int i = 0; i < MaxbulletCount; i++)
                if (activeBullets[i] == true)
                    if (aiSprite.getGlobalBounds().intersects(bullet[i].getGlobalBounds()))
                    {
                        hitSound.play();
                        if (userPet->getAttackDamage() > AiPet->getDefensePower())
                            AiPet->setHealth(AiPet->getHealth() - userPet->getAttackDamage() + AiPet->getDefensePower());
                        activeBullets[i] = false;
                    }
            // move bullet on arena
            for (int i = 0; i < MaxbulletCount; i++)
            {
                if (activeBullets[i] == true)
                {
                    bullet[i].move(5, 0);
                }
            }
            // check collision of dragon special ability fireball with obstacles
            if (userPet->getFireball())
                if (checkCollision(fireball, sprite_wall1, sprite_wall2, sprite_stone1, sprite_stone2))
                {
                    userPet->setFireball(false);
                }
            // check collision of dragon special ability fireball with ai pet
            if (userPet->getFireball())
                if (aiSprite.getGlobalBounds().intersects(fireball.getGlobalBounds()))
                {
                    hitSound.play();
                    AiPet->setHealth(AiPet->getHealth() - userPet->getMove1());
                    userPet->setFireball(false);
                }
            // fire ai bullets when its not stunned by any user pet special ability
            if (!AiPet->getStun() && !AiPet->getGriffinStun())
                if (aiFireClock.getElapsedTime().asSeconds() > aiFireInterval)
                {
                    for (int i = 0; i < MaxAIBullets; ++i)
                    {
                        if (!activeAIBullets[i])
                        {
                            activeAIBullets[i] = true;
                            aiBullet[i].setPosition(aiSprite.getPosition().x - 20, aiSprite.getPosition().y + 40);
                            break;
                        }
                    }
                    aiFireClock.restart();
                }
            // move ai bullets,check collision with obstacles and userpet

            for (int i = 0; i < MaxAIBullets; ++i)
            {
                if (activeAIBullets[i])
                {
                    aiBullet[i].move(-5, 0);
                    if (checkCollision(aiBullet[i], sprite_wall1, sprite_wall2, sprite_stone1, sprite_stone2) ||
                        aiBullet[i].getPosition().x < 0)
                    {
                        activeAIBullets[i] = false;
                    }
                    if (userSprite.getGlobalBounds().intersects(aiBullet[i].getGlobalBounds()))
                    {
                        hitSound.play();
                        if (AiPet->getAttackDamage() * level > userPet->getDefensePower())
                            userPet->setHealth(userPet->getHealth() - AiPet->getAttackDamage() * level + userPet->getDefensePower());
                        activeAIBullets[i] = false;
                    }
                }
            }

            window.draw(bg);
            // shield potion timer
            if (ShieldPotionClock.getElapsedTime().asSeconds() > 10.f && ShieldPotion)
            {
                ShieldPotion = false;
                AiPet->setAttackDamage(AiPet->getAttackDamage() * 2);
            }
            // drawing active bullets
            for (int i = 0; i < MaxbulletCount; i++)
            {
                if (activeBullets[i])
                    window.draw(bullet[i]);
            }
            // moving fireball if exists
            if (userPet->getFireball())
            {
                fireball.move(5, 0);
            }
            // claw ability timer
            if (ClawTimer.getElapsedTime().asSeconds() > 1.f)
                userPet->setClaw(false);
            // speed ability timer
            if (userPet->getIsSpeed())
            {
                if (SpeedReset.getElapsedTime().asSeconds() > 2.f)
                {
                    userPet->setSpeed(userPet->getSpeed() - userPet->getMove1());
                    userPet->setIsSpeed(false);
                }
            }
            // stun timer
            if (AiPet->getStun())
            {
                if (StunTimer.getElapsedTime().asSeconds() > userPet->getMove2())
                {
                    AiPet->setStun(false);
                }
            }
            // griffin stun timer
            if (AiPet->getGriffinStun())
            {
                if (griffinStunTimer.getElapsedTime().asSeconds() > userPet->getMove2())
                {
                    AiPet->setGriffinStun(false);
                }
            }
            // phoenix revive ability use
            if (userPet->getIsRevive() && userPet->getHealth() < 0)
            {
                userPet->setHealth(StartHealth);
                userPet->setIsRevive(false);
            }
            // game end when any of the pet dies
            if (!userPet->getIsRevive())
            {
                if (*userPet < 0)
                {
                    window.clear();
                    Texture losingScreen;
                    if (!losingScreen.loadFromFile("LosePage.png"))
                    {
                        cout << "Image load failure";
                        exit(0);
                    }
                    Sprite loss(losingScreen);
                    window.draw(loss);
                    window.display();
                    sleep(seconds(5));
                    return;
                }
            }
            if (*AiPet < 0)
            {
                window.clear();
                Texture WinScreen;
                if (!WinScreen.loadFromFile("WinPage.png"))
                {
                    cout << "Image load failure";
                    exit(0);
                }
                Sprite Win(WinScreen);
                Text popupText;
                popupText.setFont(font);
                popupText.setCharacterSize(28);
                popupText.setFillColor(Color::White);
                popupText.setStyle(Text::Bold);
                popupText.setPosition(X_RESOLUTION / 2.4, Y_RESOLUTION / 1.3);
                user.setCurrency(user.getCurrency() + int(Prize * level));
                popupText.setString("You Got " + to_string(int(Prize * level)) + " Game Currency");
                window.draw(Win);
                window.draw(popupText);
                window.display();
                sleep(seconds(5));
                return;
            }

            // game ends if time exceeds
            if (GameClock.getElapsedTime().asSeconds() > TimeLimit)
            {
                if (userPet->getHealth() < AiPet->getHealth())
                {
                    window.clear();
                    Texture losingScreen;
                    if (!losingScreen.loadFromFile("LosePage.png"))
                    {
                        cout << "Image load failure";
                        exit(0);
                    }
                    Sprite loss(losingScreen);
                    window.draw(loss);
                    window.display();
                    sleep(seconds(5));
                    return;
                }
                if (userPet->getHealth() >= AiPet->getHealth())
                {
                    window.clear();
                    Texture WinScreen;
                    if (!WinScreen.loadFromFile("WinPage.png"))
                    {
                        cout << "Image load failure";
                        exit(0);
                    }
                    Sprite Win(WinScreen);
                    Text popupText;
                    popupText.setFont(font);
                    popupText.setCharacterSize(28);
                    popupText.setFillColor(Color::White);
                    popupText.setStyle(Text::Bold);
                    popupText.setPosition(X_RESOLUTION / 2.4, Y_RESOLUTION / 1.3);
                    user.setCurrency(user.getCurrency() + int(Prize * level));
                    popupText.setString("You Got " + to_string(int(Prize * level)) + " Game Currency");
                    window.draw(Win);
                    window.draw(popupText);
                    window.display();
                    sleep(seconds(5));
                    return;
                }
            }

            // unicorn shield ability timer
            if (userPet->getIsShield() && shieldTimer.getElapsedTime().asSeconds() > 5.f)
            {
                AiPet->setAttackDamage(AiPet->getAttackDamage() + userPet->getMove2());
                userPet->setIsShield(false);
            }
            // buff potion timer
            if (isBuff)
                if (BuffTimer.getElapsedTime().asSeconds() > 5.f)
                {
                    userPet->setAttackDamage(userPet->getAttackDamage() - 20);
                    userPet->setSpeed(userPet->getSpeed() - 5);
                    isBuff = false;
                }
            // spawn random potion after every 10 sec
            if (potionTimer.getElapsedTime().asSeconds() > 10.f)
            {
                do
                {
                    float x = rand() % (1280 - 64);
                    float y = rand() % (720 - 64);
                    potion.setPosition(x, y);
                } while (checkCollision(potion, sprite_wall1, sprite_wall2, sprite_stone1, sprite_stone2));

                showPotion = true;
                potionTimer.restart();
            }
            // collect potion and do task of any random potion
            if (potion.getGlobalBounds().intersects(userSprite.getGlobalBounds()) && showPotion)
            {
                showPotion = false;
                int num = rand() % 4 + 1;
                if (num == 1)
                {
                    popupClock.restart();
                    popupText.setString("Mana Potion Collected");
                    showPopup = true;
                    ManaPotion = true;
                }
                if (num == 2)
                {
                    popupClock.restart();
                    popupText.setString("Heal Potion Collected");
                    showPopup = true;
                    if (userPet->getHealth() < StartHealth)
                        userPet->setHealth(StartHealth);
                }
                if (num == 3)
                {
                    popupClock.restart();
                    popupText.setString("Buff Potion Collected");
                    showPopup = true;
                    userPet->setAttackDamage(userPet->getAttackDamage() + 20);
                    userPet->setSpeed(userPet->getSpeed() + 5);
                    BuffTimer.restart();
                    isBuff = true;
                }
                if (num == 4)
                {
                    popupClock.restart();
                    popupText.setString("Shield Potion Collected");
                    showPopup = true;
                    AiPet->setAttackDamage(AiPet->getAttackDamage() * 0.5);
                    ShieldPotionClock.restart();
                    ShieldPotion = true;
                }
                potionTimer.restart();
            }

            clock.setString(to_string(int(TimeLimit - GameClock.getElapsedTime().asSeconds())));
            if (userPet->getClaw())
                window.draw(claw);
            if (userPet->getFireball())
                window.draw(fireball);
            window.draw(sprite_stone1);
            window.draw(sprite_stone2);
            window.draw(sprite_wall1);
            window.draw(sprite_wall2);
            window.draw(clock);
            for (int i = 0; i < MaxAIBullets; ++i)
            {
                if (activeAIBullets[i])
                    window.draw(aiBullet[i]);
            }
            if (showPotion)
                window.draw(potion);

            window.draw(aiSprite);
            window.draw(userSprite);
            window.draw(AiHealth);
            window.draw(userHealth);
            if (showPopup && popupClock.getElapsedTime() > seconds(2))
            {
                showPopup = false;
            }
            if (showPopup)
                window.draw(popupText);

            window.display();
        }
    }
};
class twoVtwo : public Arena
{
private:
    Pet *userPet[2] = {nullptr, nullptr};
    Pet *AiPet[2] = {nullptr, nullptr};

public:
    void setUserPet(Pet *temp, int index)
    {
        userPet[index] = temp;
    }
    void setAiPet(Pet *temp, int index)
    {
        AiPet[index] = temp;
    }
    Pet *getAiPet(int index)
    {
        return AiPet[index];
    }
    Pet *getUserPet(int index)
    {
        return userPet[index];
    }
    twoVtwo(Wall &w1, Wall &w2, Stone &s1, Stone &s2) : Arena(w1, w2, s1, s2) {}
    // same logics as onevone
    void Battle(RenderWindow &window, Font &font, Player &user)
    {
        int petNo = 0;
        int AiPetNo = 0;
        float level = AskLevel(window);
        Text popupText;
        popupText.setFont(font);
        popupText.setCharacterSize(28);
        popupText.setFillColor(Color::White);
        popupText.setStyle(Text::Bold);
        popupText.setPosition(X_RESOLUTION / 2.5, Y_RESOLUTION / 3);
        bool showPopup = false;
        Clock popupClock;
        Clock GameClock;
        Clock aiMoveClock;
        float aiMoveInterval = 1.5f;
        Vector2f aiDirection(0, 0);
        Clock SpeedReset;
        Text userHealth("", font, 24), AiHealth("", font, 24), clock("", font, 24);
        clock.setPosition(10 * CELL_SIZE, 0.5 * CELL_SIZE);
        userHealth.setPosition(0.5 * CELL_SIZE, 0.5 * CELL_SIZE);
        AiHealth.setPosition(18 * CELL_SIZE, 0.5 * CELL_SIZE);
        Clock frameClock;
        Clock Move1Cooldown;
        Clock Move2Cooldown;
        int currentFrame = 0;
        float frameTime = 0.2f;
        Texture BG;
        Texture Fireball;
        Texture Claw;
        int MaxbulletCount = 10;
        bool activeBullets[10] = {0};
        Texture userTex1[2], userTex2[2], userTex3[2], Bullet;
        Texture aiTex1[2], aiTex2[2], aiTex3[2];
        Texture Aibullet;
        const int MaxAIBullets = 10;
        Sprite aiBullet[MaxAIBullets];
        bool activeAIBullets[MaxAIBullets] = {false};
        Clock aiFireClock;
        float aiFireInterval = 0.5f;
        Texture potionTex;
        int bgNum = rand() % 4 + 1;
        if (bgNum == 1)
            if (!BG.loadFromFile("BattleBG.png"))
            {
                cout << "Image load Failure";
                exit(0);
            }
        if (bgNum == 2)
            if (!BG.loadFromFile("BattleBG(1).png"))
            {
                cout << "Image load Failure";
                exit(0);
            }
        if (bgNum == 3)
            if (!BG.loadFromFile("BattleBG(2).png"))
            {
                cout << "Image load Failure";
                exit(0);
            }
        if (bgNum == 4)
            if (!BG.loadFromFile("BattleBG(3).png"))
            {
                cout << "Image load Failure";
                exit(0);
            }
        if (!potionTex.loadFromFile("Potion.png"))
        {
            cout << "Failed to load Potion.png\n";
            exit(0);
        }
        if (!Aibullet.loadFromFile("Bullet.png"))
        {
            cout << "Image load Failure";
            exit(0);
        }

        if (!Claw.loadFromFile("Claw.png"))
        {
            cout << "Image load Failure";
            exit(0);
        }
        if (!Fireball.loadFromFile("FireBall.png"))
        {
            cout << "Image load Failure";
            exit(0);
        }
        if (!Bullet.loadFromFile("Bullet.png"))
        {
            cout << "Image load Failure";
            exit(0);
        }
        for (int i = 0; i < 2; i++)
        {
            if (AiPet[i]->getType() == 1)
            {
                if (!aiTex1[i].loadFromFile("DragonSide2.png"))
                {
                    cout << "Failed to load DragonSide1.png\n";
                    exit(0);
                }
                if (!aiTex2[i].loadFromFile("DragonSide2(0).png"))
                {
                    cout << "Failed to load DragonSide1(0).png\n";
                    exit(0);
                }
                if (!aiTex3[i].loadFromFile("DragonSide2(1).png"))
                {
                    cout << "Failed to load DragonSide1(1).png\n";
                    exit(0);
                }
            }
            if (AiPet[i]->getType() == 2)
            {
                if (!aiTex1[i].loadFromFile("PhoenixSide2.png"))
                {
                    cout << "Failed to load DragonSide1.png\n";
                    exit(0);
                }
                if (!aiTex2[i].loadFromFile("PhoenixSide2(0).png"))
                {
                    cout << "Failed to load DragonSide1(0).png\n";
                    exit(0);
                }
                if (!aiTex3[i].loadFromFile("PhoenixSide2(1).png"))
                {
                    cout << "Failed to load DragonSide1(1).png\n";
                    exit(0);
                }
            }
            if (AiPet[i]->getType() == 3)
            {
                if (!aiTex1[i].loadFromFile("UnicornSide2.png"))
                {
                    cout << "Failed to load DragonSide1.png\n";
                    exit(0);
                }
                if (!aiTex2[i].loadFromFile("UnicornSide2(0).png"))
                {
                    cout << "Failed to load DragonSide1(0).png\n";
                    exit(0);
                }
                if (!aiTex3[i].loadFromFile("UnicornSide2(1).png"))
                {
                    cout << "Failed to load DragonSide1(1).png\n";
                    exit(0);
                }
            }
            if (AiPet[i]->getType() == 4)
            {
                if (!aiTex1[i].loadFromFile("GriffinSide2.png"))
                {
                    cout << "Failed to load DragonSide1.png\n";
                    exit(0);
                }
                if (!aiTex2[i].loadFromFile("GriffinSide2(0).png"))
                {
                    cout << "Failed to load DragonSide1(0).png\n";
                    exit(0);
                }
                if (!aiTex3[i].loadFromFile("GriffinSide2(1).png"))
                {
                    cout << "Failed to load DragonSide1(1).png\n";
                    exit(0);
                }
            }

            if (userPet[i]->getType() == 1)
            {
                if (!userTex1[i].loadFromFile("DragonSide1.png"))
                {
                    cout << "Failed to load DragonSide1.png\n";
                    exit(0);
                }
                if (!userTex2[i].loadFromFile("DragonSide1(0).png"))
                {
                    cout << "Failed to load DragonSide1(0).png\n";
                    exit(0);
                }
                if (!userTex3[i].loadFromFile("DragonSide1(1).png"))
                {
                    cout << "Failed to load DragonSide1(1).png\n";
                    exit(0);
                }
            }
            if (userPet[i]->getType() == 2)
            {
                if (!userTex1[i].loadFromFile("PhoenixSide1.png"))
                {
                    cout << "Failed to load DragonSide1.png\n";
                    exit(0);
                }
                if (!userTex2[i].loadFromFile("PhoenixSide1(0).png"))
                {
                    cout << "Failed to load DragonSide1(0).png\n";
                    exit(0);
                }
                if (!userTex3[i].loadFromFile("PhoenixSide1(1).png"))
                {
                    cout << "Failed to load DragonSide1(1).png\n";
                    exit(0);
                }
            }
            if (userPet[i]->getType() == 3)
            {
                if (!userTex1[i].loadFromFile("UnicornSide1.png"))
                {
                    cout << "Failed to load DragonSide1.png\n";
                    exit(0);
                }
                if (!userTex2[i].loadFromFile("UnicornSide1(0).png"))
                {
                    cout << "Failed to load DragonSide1(0).png\n";
                    exit(0);
                }
                if (!userTex3[i].loadFromFile("UnicornSide1(1).png"))
                {
                    cout << "Failed to load DragonSide1(1).png\n";
                    exit(0);
                }
            }
            if (userPet[i]->getType() == 4)
            {
                if (!userTex1[i].loadFromFile("GriffinSide1.png"))
                {
                    cout << "Failed to load DragonSide1.png\n";
                    exit(0);
                }
                if (!userTex2[i].loadFromFile("GriffinSide1(0).png"))
                {
                    cout << "Failed to load DragonSide1(0).png\n";
                    exit(0);
                }
                if (!userTex3[i].loadFromFile("GriffinSide1(1).png"))
                {
                    cout << "Failed to load DragonSide1(1).png\n";
                    exit(0);
                }
            }
        }
        Sprite userSprite[2];
        Sprite aiSprite[2];
        int StartHealth[2] = {userPet[0]->getHealth(), userPet[1]->getHealth()};
        Clock ClawTimer;
        Clock StunTimer;
        Clock shieldTimer;
        Clock griffinStunTimer;
        Clock BuffTimer;
        bool isBuff = false;
        Sprite fireball(Fireball);
        Sprite claw(Claw);
        bool ManaPotion = false;
        bool ShieldPotion = false;
        Clock ShieldPotionClock;
        aiSprite[petNo].setPosition(17 * CELL_SIZE, 5 * CELL_SIZE);
        userSprite[petNo].setPosition(1 * CELL_SIZE, 5 * CELL_SIZE);
        Texture stone1, stone2, wall1, wall2;
        Sprite sprite_stone1, sprite_stone2, sprite_wall1, sprite_wall2;
        Sprite bullet[MaxbulletCount];
        for (int i = 0; i < MaxbulletCount; i++)
        {
            bullet[i].setTexture(Bullet);
            aiBullet[i].setTexture(Aibullet);
        }
        Sprite bg(BG);
        Sprite potion(potionTex);
        Clock potionTimer;
        bool showPotion = false;
        while (window.isOpen())
        {
            userSprite[!petNo].setPosition(userSprite[petNo].getPosition());
            aiSprite[!AiPetNo].setPosition(aiSprite[petNo].getPosition());
            window.clear();
            userHealth.setString("HP : " + to_string(userPet[petNo]->getHealth()));
            AiHealth.setString("HP : " + to_string(AiPet[AiPetNo]->getHealth()));
            W1.display(window, wall1, sprite_wall1);
            W2.display(window, wall2, sprite_wall2);
            S1.display(window, stone1, sprite_stone1);
            S2.display(window, stone2, sprite_stone2);
            if (frameClock.getElapsedTime().asSeconds() > frameTime)
            {
                currentFrame++;
                if (currentFrame > 2)
                    currentFrame = 0;

                if (currentFrame == 0)
                {
                    userSprite[petNo].setTexture(userTex1[petNo]);
                    aiSprite[AiPetNo].setTexture(aiTex1[AiPetNo]);
                }
                if (currentFrame == 1)
                {
                    userSprite[petNo].setTexture(userTex2[petNo]);
                    aiSprite[AiPetNo].setTexture(aiTex2[AiPetNo]);
                }
                if (currentFrame == 2)
                {
                    userSprite[petNo].setTexture(userTex3[petNo]);
                    aiSprite[AiPetNo].setTexture(aiTex3[AiPetNo]);
                }

                frameClock.restart();
            }
            Event event;
            while (window.pollEvent(event))
            {

                if (event.type == Event::Closed)
                    window.close();
                if (event.type == Event::KeyReleased)
                    if (event.key.code == Keyboard::Tab)
                    {
                        {
                            if (userPet[!petNo]->getHealth() > 0)
                                petNo = !petNo;
                        }
                    }

                if (event.key.code == Keyboard::M)
                {
                    if (user.getNoOfManaPotions() > 0)
                    {
                        clickSound.play();
                        user.setNoOfManaPotions(user.getNoOfManaPotions() - 1);
                        popupClock.restart();
                        popupText.setString("Mana Potion Used");
                        showPopup = true;
                        ManaPotion = true;
                    }
                }
                if (event.key.code == Keyboard::H)
                {
                    if (user.getNoOfHealingPotions() > 0)
                    {
                        clickSound.play();
                        user.setNoOfHealingPotions(user.getNoOfHealingPotions() - 1);
                        popupClock.restart();
                        popupText.setString("Healing Potion Used");
                        showPopup = true;
                        if (userPet[petNo]->getHealth() < StartHealth[petNo])
                            userPet[petNo]->setHealth(StartHealth[petNo]);
                    }
                }
                if (event.key.code == Keyboard::B)
                {
                    if (user.getNoOfBuffItems() > 0)
                    {
                        clickSound.play();
                        user.setNoOfBuffItems(user.getNoOfBuffItems() - 1);
                        popupClock.restart();
                        popupText.setString("Buff Potion Used");
                        showPopup = true;
                        userPet[petNo]->setAttackDamage(userPet[petNo]->getAttackDamage() + 20);
                        userPet[petNo]->setSpeed(userPet[petNo]->getSpeed() + 5);
                        BuffTimer.restart();
                        isBuff = true;
                    }
                }
                if (event.key.code == Keyboard::S)
                {
                    if (user.getNoOfShields() > 0)
                    {
                        clickSound.play();
                        user.setNoOfShields(user.getNoOfShields() - 1);
                        popupClock.restart();
                        popupText.setString("Shield Potion Used");
                        showPopup = true;
                        AiPet[AiPetNo]->setAttackDamage(AiPet[AiPetNo]->getAttackDamage() * 0.5);
                        ShieldPotionClock.restart();
                        ShieldPotion = true;
                    }
                }

                if (event.key.code == Keyboard::X)
                {
                    if (Move2Cooldown.getElapsedTime().asSeconds() > 10.f || ManaPotion)
                    {
                        clickSound.play();
                        popupClock.restart();
                        popupText.setString("Ability 2 Used");
                        showPopup = true;
                        Move2Cooldown.restart();
                        userPet[petNo]->executeMove2(window, AiPet[AiPetNo]);
                        StunTimer.restart();
                        griffinStunTimer.restart();
                        shieldTimer.restart();
                        ManaPotion = false;
                    }
                }
                if (event.key.code == Keyboard::Z)
                {
                    if (Move1Cooldown.getElapsedTime().asSeconds() > 10.f || ManaPotion)
                    {
                        clickSound.play();
                        popupClock.restart();
                        popupText.setString("Ability 1 Used");
                        showPopup = true;
                        Move1Cooldown.restart();
                        userPet[petNo]->executeMove1(window, AiPet[AiPetNo]);
                        SpeedReset.restart();
                        ClawTimer.restart();
                        if (userPet[petNo]->getFireball())
                            fireball.setPosition(userSprite[petNo].getPosition().x + 50, userSprite[petNo].getPosition().y + 40);
                        if (userPet[petNo]->getClaw())
                        {
                            claw.setPosition(userSprite[petNo].getPosition().x + 120, userSprite[petNo].getPosition().y + 40);
                            if (aiSprite[AiPetNo].getPosition().x <= userSprite[petNo].getPosition().x + 150 && aiSprite[AiPetNo].getPosition().x >= userSprite[petNo].getPosition().x)
                            {
                                AiPet[AiPetNo]->setHealth(AiPet[AiPetNo]->getHealth() - userPet[petNo]->getMove1());
                            }
                        }
                        ManaPotion = false;
                    }
                }
                if (event.type == Event::KeyReleased)
                    if (event.key.code == Keyboard::Space)
                    {
                        for (int i = 0; i < MaxbulletCount; ++i)
                        {
                            if (!activeBullets[i])
                            {
                                clickSound.play();
                                activeBullets[i] = true;
                                bullet[i].setPosition(userSprite[petNo].getPosition().x + 50, userSprite[petNo].getPosition().y + 40);
                                break;
                            }
                        }
                    }
                Vector2f direction;
                if (event.key.code == Keyboard::Left)
                    direction = Vector2f(-userPet[petNo]->getSpeed(), 0);
                if (event.key.code == Keyboard::Right)
                    direction = Vector2f(userPet[petNo]->getSpeed(), 0);
                if (event.key.code == Keyboard::Up)
                    direction = Vector2f(0, -userPet[petNo]->getSpeed());
                if (event.key.code == Keyboard::Down)
                    direction = Vector2f(0, userPet[petNo]->getSpeed());

                Sprite tempSprite = userSprite[petNo];
                tempSprite.move(direction);

                if (tempSprite.getPosition().x >= 0 && tempSprite.getPosition().x <= 1100 &&
                    tempSprite.getPosition().y >= 0 && tempSprite.getPosition().y <= 580 &&
                    !checkCollision(tempSprite, sprite_wall1, sprite_wall2, sprite_stone1, sprite_stone2))
                    userSprite[petNo].move(direction);
            }
            if (aiMoveClock.getElapsedTime().asSeconds() > aiMoveInterval)
            {
                int dir = rand() % 4;

                switch (dir)
                {
                case 0:
                    aiDirection = Vector2f(-AiPet[AiPetNo]->getSpeed(), 0);
                    break;
                case 1:
                    aiDirection = Vector2f(AiPet[AiPetNo]->getSpeed(), 0);
                    break;
                case 2:
                    aiDirection = Vector2f(0, -AiPet[AiPetNo]->getSpeed());
                    break;
                case 3:
                    aiDirection = Vector2f(0, AiPet[AiPetNo]->getSpeed());
                    break;
                }

                aiMoveClock.restart();
            }
            window.draw(bg);
            Sprite tempAI = aiSprite[AiPetNo];
            tempAI.move(aiDirection);
            if (tempAI.getPosition().x >= 0 && tempAI.getPosition().x <= 1100 &&
                tempAI.getPosition().y >= 0 && tempAI.getPosition().y <= 580 &&
                !checkCollision(tempAI, sprite_wall1, sprite_wall2, sprite_stone1, sprite_stone2))
            {
                aiSprite[AiPetNo].move(aiDirection);
            }
            if (!AiPet[AiPetNo]->getStun() && !AiPet[AiPetNo]->getGriffinStun())
                if (aiFireClock.getElapsedTime().asSeconds() > aiFireInterval)
                {
                    for (int i = 0; i < MaxAIBullets; ++i)
                    {
                        if (!activeAIBullets[i])
                        {
                            activeAIBullets[i] = true;
                            aiBullet[i].setPosition(aiSprite[AiPetNo].getPosition().x - 20, aiSprite[AiPetNo].getPosition().y + 40);
                            break;
                        }
                    }
                    aiFireClock.restart();
                }
            for (int i = 0; i < MaxAIBullets; ++i)
            {
                if (activeAIBullets[i])
                {
                    aiBullet[i].move(-5, 0);
                    if (checkCollision(aiBullet[i], sprite_wall1, sprite_wall2, sprite_stone1, sprite_stone2) ||
                        aiBullet[i].getPosition().x < 0)
                    {
                        activeAIBullets[i] = false;
                    }
                    if (userSprite[petNo].getGlobalBounds().intersects(aiBullet[i].getGlobalBounds()))
                    {
                        hitSound.play();
                        if (AiPet[AiPetNo]->getAttackDamage() * level > userPet[petNo]->getDefensePower())
                            userPet[petNo]->setHealth(userPet[petNo]->getHealth() - AiPet[AiPetNo]->getAttackDamage() * level + userPet[petNo]->getDefensePower());
                        activeAIBullets[i] = false;
                    }
                }
            }
            for (int i = 0; i < MaxbulletCount; i++)
                if (activeBullets[i] == true)
                    if (checkCollision(bullet[i], sprite_wall1, sprite_wall2, sprite_stone1, sprite_stone2) || bullet[i].getPosition().x > 1270)
                    {
                        activeBullets[i] = false;
                    }
            for (int i = 0; i < MaxbulletCount; i++)
                if (activeBullets[i] == true)
                    if (aiSprite[AiPetNo].getGlobalBounds().intersects(bullet[i].getGlobalBounds()))
                    {
                        hitSound.play();
                        if (userPet[petNo]->getAttackDamage() > AiPet[AiPetNo]->getDefensePower())
                            AiPet[AiPetNo]->setHealth(AiPet[AiPetNo]->getHealth() - userPet[petNo]->getAttackDamage() + AiPet[AiPetNo]->getDefensePower());
                        activeBullets[i] = false;
                    }
            for (int i = 0; i < MaxbulletCount; i++)
            {
                if (activeBullets[i] == true)
                {
                    bullet[i].move(5, 0);
                }
            }
            for (int i = 0; i < MaxbulletCount; i++)
            {
                if (activeBullets[i])
                    window.draw(bullet[i]);
            }
            if (userPet[petNo]->getFireball())
                if (checkCollision(fireball, sprite_wall1, sprite_wall2, sprite_stone1, sprite_stone2))
                {
                    userPet[petNo]->setFireball(false);
                }
            if (userPet[petNo]->getFireball())
                if (aiSprite[AiPetNo].getGlobalBounds().intersects(fireball.getGlobalBounds()))
                {
                    hitSound.play();
                    AiPet[AiPetNo]->setHealth(AiPet[AiPetNo]->getHealth() - userPet[petNo]->getMove1());
                    userPet[petNo]->setFireball(false);
                }

            if (ShieldPotionClock.getElapsedTime().asSeconds() > 10.f && ShieldPotion)
            {
                ShieldPotion = false;
                AiPet[AiPetNo]->setAttackDamage(AiPet[AiPetNo]->getAttackDamage() * 2);
                ShieldPotionClock.restart();
            }

            if (userPet[petNo]->getFireball())
            {
                fireball.move(5, 0);
            }
            if (userPet[petNo]->getClaw())
                if (ClawTimer.getElapsedTime().asSeconds() > 1.f)
                    userPet[petNo]->setClaw(false);
            if (userPet[petNo]->getIsSpeed())
            {
                if (SpeedReset.getElapsedTime().asSeconds() > 2.f)
                {
                    userPet[petNo]->setSpeed(userPet[petNo]->getSpeed() - userPet[petNo]->getMove1());
                    userPet[petNo]->setIsSpeed(false);
                }
            }
            if (AiPet[AiPetNo]->getStun())
            {
                if (StunTimer.getElapsedTime().asSeconds() > userPet[petNo]->getMove2())
                {
                    AiPet[AiPetNo]->setStun(false);
                }
            }
            if (AiPet[AiPetNo]->getGriffinStun())
            {
                if (griffinStunTimer.getElapsedTime().asSeconds() > userPet[petNo]->getMove2())
                {
                    AiPet[AiPetNo]->setGriffinStun(false);
                }
            }
            if (userPet[petNo]->getIsRevive() && userPet[petNo]->getHealth() < 0)
            {
                userPet[petNo]->setHealth(StartHealth[petNo]);
                userPet[petNo]->setIsRevive(false);
            }

            if (!userPet[petNo]->getIsRevive())
            {
                if (userPet[0]->getHealth() < 0 && userPet[1]->getHealth() < 0)
                {
                    window.clear();
                    Texture losingScreen;
                    if (!losingScreen.loadFromFile("LosePage.png"))
                    {
                        cout << "Image load failure";
                        exit(0);
                    }
                    Sprite loss(losingScreen);
                    window.draw(loss);
                    window.display();
                    sleep(seconds(5));
                    return;
                }
            }
            if (userPet[petNo]->getHealth() < 0 && !userPet[petNo]->getIsRevive())
            {
                petNo = !petNo;
            }
            if (AiPet[AiPetNo]->getHealth() < 0)
            {
                if (AiPetNo == 0)
                    AiPetNo++;
            }
            if (AiPet[1]->getHealth() < 0)
            {
                window.clear();
                Texture WinScreen;
                if (!WinScreen.loadFromFile("WinPage.png"))
                {
                    cout << "Image load failure";
                    exit(0);
                }
                Sprite Win(WinScreen);
                Text popupText;
                popupText.setFont(font);
                popupText.setCharacterSize(28);
                popupText.setFillColor(Color::White);
                popupText.setStyle(Text::Bold);
                popupText.setPosition(X_RESOLUTION / 2.4, Y_RESOLUTION / 1.3);
                user.setCurrency(user.getCurrency() + int(Prize * level));
                popupText.setString("You Got " + to_string(int(Prize * level)) + " Game Currency");
                window.draw(Win);
                window.draw(popupText);
                window.display();
                sleep(seconds(5));
                return;
            }

            if (GameClock.getElapsedTime().asSeconds() > TimeLimit)
            {
                int pet1Health = (userPet[0]->getHealth() < 0) ? 0 : userPet[0]->getHealth();
                int pet2Health = (userPet[1]->getHealth() < 0) ? 0 : userPet[1]->getHealth();
                int Ai1Health = (AiPet[0]->getHealth() < 0) ? 0 : AiPet[0]->getHealth();
                int Ai2Health = (AiPet[1]->getHealth() < 0) ? 0 : AiPet[1]->getHealth();
                if ((pet1Health + pet2Health) < (Ai1Health + Ai2Health))
                {
                    window.clear();
                    Texture losingScreen;
                    if (!losingScreen.loadFromFile("LosePage.png"))
                    {
                        cout << "Image load failure";
                        exit(0);
                    }
                    Sprite loss(losingScreen);
                    window.draw(loss);
                    window.display();
                    sleep(seconds(5));
                    return;
                }
                if ((pet1Health + pet2Health) >= (Ai1Health + Ai2Health))
                {
                    window.clear();
                    Texture WinScreen;
                    if (!WinScreen.loadFromFile("WinPage.png"))
                    {
                        cout << "Image load failure";
                        exit(0);
                    }
                    Sprite Win(WinScreen);
                    Text popupText;
                    popupText.setFont(font);
                    popupText.setCharacterSize(28);
                    popupText.setFillColor(Color::White);
                    popupText.setStyle(Text::Bold);
                    popupText.setPosition(X_RESOLUTION / 2.4, Y_RESOLUTION / 1.3);
                    user.setCurrency(user.getCurrency() + int(Prize * level));
                    popupText.setString("You Got " + to_string(int(Prize * level)) + " Game Currency");
                    window.draw(Win);
                    window.draw(popupText);
                    window.display();
                    sleep(seconds(5));
                    return;
                }
            }
            if (userPet[petNo]->getIsShield() && shieldTimer.getElapsedTime().asSeconds() > 5.f)
            {
                AiPet[AiPetNo]->setAttackDamage(AiPet[AiPetNo]->getAttackDamage() + userPet[petNo]->getMove2());
                userPet[petNo]->setIsShield(false);
                shieldTimer.restart();
            }
            if (isBuff)
                if (BuffTimer.getElapsedTime().asSeconds() > 5.f)
                {
                    userPet[petNo]->setAttackDamage(userPet[petNo]->getAttackDamage() - 20);
                    userPet[petNo]->setSpeed(userPet[petNo]->getSpeed() - 5);
                    isBuff = false;
                }
            if (potionTimer.getElapsedTime().asSeconds() > 10.f)
            {
                do
                {
                    float x = rand() % (1280 - 64);
                    float y = rand() % (720 - 64);
                    potion.setPosition(x, y);
                } while (checkCollision(potion, sprite_wall1, sprite_wall2, sprite_stone1, sprite_stone2));

                showPotion = true;
                potionTimer.restart();
            }
            if (potion.getGlobalBounds().intersects(userSprite[petNo].getGlobalBounds()) && showPotion)
            {
                showPotion = false;
                int num = rand() % 4 + 1;
                if (num == 1)
                {
                    popupClock.restart();
                    popupText.setString("Mana Potion Collected");
                    showPopup = true;
                    ManaPotion = true;
                }
                if (num == 2)
                {
                    popupClock.restart();
                    popupText.setString("Heal Potion Collected");
                    showPopup = true;
                    if (userPet[petNo]->getHealth() < StartHealth[petNo])
                        userPet[petNo]->setHealth(StartHealth[petNo]);
                }
                if (num == 3)
                {
                    popupClock.restart();
                    popupText.setString("Buff Potion Collected");
                    showPopup = true;
                    userPet[petNo]->setAttackDamage(userPet[petNo]->getAttackDamage() + 20);
                    userPet[petNo]->setSpeed(userPet[petNo]->getSpeed() + 5);
                    BuffTimer.restart();
                    isBuff = true;
                }
                if (num == 4)
                {
                    popupClock.restart();
                    popupText.setString("Shield Potion Collected");
                    showPopup = true;
                    AiPet[AiPetNo]->setAttackDamage(AiPet[AiPetNo]->getAttackDamage() * 0.5);
                    ShieldPotionClock.restart();
                    ShieldPotion = true;
                }
                potionTimer.restart();
            }
            clock.setString(to_string(int(TimeLimit - GameClock.getElapsedTime().asSeconds())));
            window.draw(sprite_stone1);
            window.draw(sprite_stone2);
            window.draw(sprite_wall1);
            window.draw(sprite_wall2);
            window.draw(clock);
            for (int i = 0; i < MaxAIBullets; ++i)
            {
                if (activeAIBullets[i])
                    window.draw(aiBullet[i]);
            }
            for (int i = 0; i < MaxAIBullets; ++i)
            {
                if (activeAIBullets[i])
                    window.draw(aiBullet[i]);
            }
            if (showPotion)
                window.draw(potion);
            if (showPopup && popupClock.getElapsedTime() > seconds(2))
            {
                showPopup = false;
            }
            if (showPopup)
                window.draw(popupText);
            window.draw(aiSprite[AiPetNo]);
            window.draw(userSprite[petNo]);
            if (userPet[petNo]->getClaw())
                window.draw(claw);
            if (userPet[petNo]->getFireball())
                window.draw(fireball);
            window.draw(AiHealth);
            window.draw(userHealth);
            window.display();
        }
    }
};
class guildVguild : public Arena
{
private:
    Guild userGuild;
    Guild AiGuild;

public:
    void setUserGuild(Guild G)
    {
        userGuild = G;
    }
    void setAiGuild(Guild G)
    {
        AiGuild = G;
    }
    guildVguild(Wall &w1, Wall &w2, Stone &s1, Stone &s2) : Arena(w1, w2, s1, s2) {}
    // same logics as onevone
    void Battle(RenderWindow &window, Font &font, Player &user)
    {
        float level = AskLevel(window);
        Pet *userPet[4];
        Pet *AiPet[4];
        userPet[0] = userGuild.getHealer();
        userPet[1] = userGuild.getDamageDealer();
        userPet[2] = userGuild.getTank();
        userPet[3] = userGuild.getStriker();
        AiPet[0] = AiGuild.getHealer();
        AiPet[1] = AiGuild.getDamageDealer();
        AiPet[2] = AiGuild.getTank();
        AiPet[3] = AiGuild.getStriker();
        int petNo = 0;
        int AiPetNo = 0;
        Text popupText;
        popupText.setFont(font);
        popupText.setCharacterSize(28);
        popupText.setFillColor(Color::White);
        popupText.setStyle(Text::Bold);
        popupText.setPosition(X_RESOLUTION / 2.5, Y_RESOLUTION / 3);
        bool showPopup = false;
        Clock popupClock;
        Clock GameClock;
        Clock aiMoveClock;
        float aiMoveInterval = 1.5f;
        Vector2f aiDirection(0, 0);
        Clock SpeedReset;
        Text userHealth("", font, 24), AiHealth("", font, 24), clock("", font, 24);
        clock.setPosition(10 * CELL_SIZE, 0.5 * CELL_SIZE);
        userHealth.setPosition(0.5 * CELL_SIZE, 0.5 * CELL_SIZE);
        AiHealth.setPosition(18 * CELL_SIZE, 0.5 * CELL_SIZE);
        Clock frameClock;
        Clock Move1Cooldown;
        Clock Move2Cooldown;
        int currentFrame = 0;
        float frameTime = 0.2f;
        Texture BG;
        Texture Fireball;
        Texture Claw;
        int MaxbulletCount = 10;
        bool activeBullets[10] = {0};
        Texture userTex1[4], userTex2[4], userTex3[4], Bullet;
        Texture aiTex1[4], aiTex2[4], aiTex3[4];
        Texture Aibullet;
        const int MaxAIBullets = 10;
        Sprite aiBullet[MaxAIBullets];
        bool activeAIBullets[MaxAIBullets] = {false};
        Clock aiFireClock;
        float aiFireInterval = 0.5f;
        Texture potionTex;
        int bgNum = rand() % 4 + 1;
        if (bgNum == 1)
            if (!BG.loadFromFile("BattleBG.png"))
            {
                cout << "Image load Failure";
                exit(0);
            }
        if (bgNum == 2)
            if (!BG.loadFromFile("BattleBG(1).png"))
            {
                cout << "Image load Failure";
                exit(0);
            }
        if (bgNum == 3)
            if (!BG.loadFromFile("BattleBG(2).png"))
            {
                cout << "Image load Failure";
                exit(0);
            }
        if (bgNum == 4)
            if (!BG.loadFromFile("BattleBG(3).png"))
            {
                cout << "Image load Failure";
                exit(0);
            }
        if (!potionTex.loadFromFile("Potion.png"))
        {
            cout << "Failed to load Potion.png\n";
            exit(0);
        }
        if (!Aibullet.loadFromFile("Bullet.png"))
        {
            cout << "Image load Failure";
            exit(0);
        }
        if (!Claw.loadFromFile("Claw.png"))
        {
            cout << "Image load Failure";
            exit(0);
        }
        if (!Fireball.loadFromFile("FireBall.png"))
        {
            cout << "Image load Failure";
            exit(0);
        }
        if (!Bullet.loadFromFile("Bullet.png"))
        {
            cout << "Image load Failure";
            exit(0);
        }
        for (int i = 0; i < 4; i++)
        {
            if (AiPet[i]->getType() == 1)
            {
                if (!aiTex1[i].loadFromFile("DragonSide2.png"))
                {
                    cout << "Failed to load DragonSide1.png\n";
                    exit(0);
                }
                if (!aiTex2[i].loadFromFile("DragonSide2(0).png"))
                {
                    cout << "Failed to load DragonSide1(0).png\n";
                    exit(0);
                }
                if (!aiTex3[i].loadFromFile("DragonSide2(1).png"))
                {
                    cout << "Failed to load DragonSide1(1).png\n";
                    exit(0);
                }
            }
            if (AiPet[i]->getType() == 2)
            {
                if (!aiTex1[i].loadFromFile("PhoenixSide2.png"))
                {
                    cout << "Failed to load DragonSide1.png\n";
                    exit(0);
                }
                if (!aiTex2[i].loadFromFile("PhoenixSide2(0).png"))
                {
                    cout << "Failed to load DragonSide1(0).png\n";
                    exit(0);
                }
                if (!aiTex3[i].loadFromFile("PhoenixSide2(1).png"))
                {
                    cout << "Failed to load DragonSide1(1).png\n";
                    exit(0);
                }
            }
            if (AiPet[i]->getType() == 3)
            {
                if (!aiTex1[i].loadFromFile("UnicornSide2.png"))
                {
                    cout << "Failed to load DragonSide1.png\n";
                    exit(0);
                }
                if (!aiTex2[i].loadFromFile("UnicornSide2(0).png"))
                {
                    cout << "Failed to load DragonSide1(0).png\n";
                    exit(0);
                }
                if (!aiTex3[i].loadFromFile("UnicornSide2(1).png"))
                {
                    cout << "Failed to load DragonSide1(1).png\n";
                    exit(0);
                }
            }
            if (AiPet[i]->getType() == 4)
            {
                if (!aiTex1[i].loadFromFile("GriffinSide2.png"))
                {
                    cout << "Failed to load DragonSide1.png\n";
                    exit(0);
                }
                if (!aiTex2[i].loadFromFile("GriffinSide2(0).png"))
                {
                    cout << "Failed to load DragonSide1(0).png\n";
                    exit(0);
                }
                if (!aiTex3[i].loadFromFile("GriffinSide2(1).png"))
                {
                    cout << "Failed to load DragonSide1(1).png\n";
                    exit(0);
                }
            }

            if (userPet[i]->getType() == 1)
            {
                if (!userTex1[i].loadFromFile("DragonSide1.png"))
                {
                    cout << "Failed to load DragonSide1.png\n";
                    exit(0);
                }
                if (!userTex2[i].loadFromFile("DragonSide1(0).png"))
                {
                    cout << "Failed to load DragonSide1(0).png\n";
                    exit(0);
                }
                if (!userTex3[i].loadFromFile("DragonSide1(1).png"))
                {
                    cout << "Failed to load DragonSide1(1).png\n";
                    exit(0);
                }
            }
            if (userPet[i]->getType() == 2)
            {
                if (!userTex1[i].loadFromFile("PhoenixSide1.png"))
                {
                    cout << "Failed to load DragonSide1.png\n";
                    exit(0);
                }
                if (!userTex2[i].loadFromFile("PhoenixSide1(0).png"))
                {
                    cout << "Failed to load DragonSide1(0).png\n";
                    exit(0);
                }
                if (!userTex3[i].loadFromFile("PhoenixSide1(1).png"))
                {
                    cout << "Failed to load DragonSide1(1).png\n";
                    exit(0);
                }
            }
            if (userPet[i]->getType() == 3)
            {
                if (!userTex1[i].loadFromFile("UnicornSide1.png"))
                {
                    cout << "Failed to load DragonSide1.png\n";
                    exit(0);
                }
                if (!userTex2[i].loadFromFile("UnicornSide1(0).png"))
                {
                    cout << "Failed to load DragonSide1(0).png\n";
                    exit(0);
                }
                if (!userTex3[i].loadFromFile("UnicornSide1(1).png"))
                {
                    cout << "Failed to load DragonSide1(1).png\n";
                    exit(0);
                }
            }
            if (userPet[i]->getType() == 4)
            {
                if (!userTex1[i].loadFromFile("GriffinSide1.png"))
                {
                    cout << "Failed to load DragonSide1.png\n";
                    exit(0);
                }
                if (!userTex2[i].loadFromFile("GriffinSide1(0).png"))
                {
                    cout << "Failed to load DragonSide1(0).png\n";
                    exit(0);
                }
                if (!userTex3[i].loadFromFile("GriffinSide1(1).png"))
                {
                    cout << "Failed to load DragonSide1(1).png\n";
                    exit(0);
                }
            }
        }
        Sprite userSprite[4];
        Sprite aiSprite[4];
        int StartHealth[4] = {userPet[0]->getHealth(), userPet[1]->getHealth(), userPet[2]->getHealth(), userPet[3]->getHealth()};
        Clock ClawTimer;
        Clock StunTimer;
        Clock shieldTimer;
        Clock griffinStunTimer;
        Clock BuffTimer;
        bool isBuff = false;
        Sprite fireball(Fireball);
        Sprite claw(Claw);
        bool ManaPotion = false;
        bool ShieldPotion = false;
        Clock ShieldPotionClock;
        aiSprite[petNo].setPosition(17 * CELL_SIZE, 5 * CELL_SIZE);
        userSprite[petNo].setPosition(1 * CELL_SIZE, 5 * CELL_SIZE);
        Texture stone1, stone2, wall1, wall2;
        Sprite sprite_stone1, sprite_stone2, sprite_wall1, sprite_wall2;
        Sprite bullet[MaxbulletCount];
        for (int i = 0; i < MaxbulletCount; i++)
        {
            bullet[i].setTexture(Bullet);
            aiBullet[i].setTexture(Aibullet);
        }
        Sprite bg(BG);
        Sprite potion(potionTex);
        Clock potionTimer;
        bool showPotion = false;
        while (window.isOpen())
        {
            for (int i = 0; i < 4; i++)
            {
                if (i != petNo)
                    userSprite[i].setPosition(userSprite[petNo].getPosition());
                if (i != AiPetNo)
                    aiSprite[i].setPosition(aiSprite[petNo].getPosition());
            }
            window.clear();
            userHealth.setString("HP : " + to_string(userPet[petNo]->getHealth()));
            AiHealth.setString("HP : " + to_string(AiPet[AiPetNo]->getHealth()));
            W1.display(window, wall1, sprite_wall1);
            W2.display(window, wall2, sprite_wall2);
            S1.display(window, stone1, sprite_stone1);
            S2.display(window, stone2, sprite_stone2);
            if (frameClock.getElapsedTime().asSeconds() > frameTime)
            {
                currentFrame++;
                if (currentFrame > 2)
                    currentFrame = 0;

                if (currentFrame == 0)
                {
                    userSprite[petNo].setTexture(userTex1[petNo]);
                    aiSprite[AiPetNo].setTexture(aiTex1[AiPetNo]);
                }
                if (currentFrame == 1)
                {
                    userSprite[petNo].setTexture(userTex2[petNo]);
                    aiSprite[AiPetNo].setTexture(aiTex2[AiPetNo]);
                }
                if (currentFrame == 2)
                {
                    userSprite[petNo].setTexture(userTex3[petNo]);
                    aiSprite[AiPetNo].setTexture(aiTex3[AiPetNo]);
                }

                frameClock.restart();
            }
            Event event;
            while (window.pollEvent(event))
            {

                if (event.type == Event::Closed)
                    window.close();
                if (event.type == Event::KeyReleased)
                    if (event.key.code == Keyboard::Tab)
                    {
                        int tries;
                        do
                        {
                            if (petNo != 3)
                                petNo++;
                            else
                                petNo = 0;

                            tries++;
                        } while (userPet[petNo]->getHealth() < 0 && tries < 4);
                    }
                if (event.key.code == Keyboard::M)
                {
                    if (user.getNoOfManaPotions() > 0)
                    {
                        clickSound.play();
                        user.setNoOfManaPotions(user.getNoOfManaPotions() - 1);
                        popupClock.restart();
                        popupText.setString("Mana Potion Used");
                        showPopup = true;
                        ManaPotion = true;
                    }
                }
                if (event.key.code == Keyboard::H)
                {
                    if (user.getNoOfHealingPotions() > 0)
                    {
                        clickSound.play();
                        user.setNoOfHealingPotions(user.getNoOfHealingPotions() - 1);
                        popupClock.restart();
                        popupText.setString("Healing Potion Used");
                        showPopup = true;
                        if (userPet[petNo]->getHealth() < StartHealth[petNo])
                            userPet[petNo]->setHealth(StartHealth[petNo]);
                    }
                }
                if (event.key.code == Keyboard::B)
                {
                    if (user.getNoOfBuffItems() > 0)
                    {
                        clickSound.play();
                        user.setNoOfBuffItems(user.getNoOfBuffItems() - 1);
                        popupClock.restart();
                        popupText.setString("Buff Potion Used");
                        showPopup = true;
                        userPet[petNo]->setAttackDamage(userPet[petNo]->getAttackDamage() + 20);
                        userPet[petNo]->setSpeed(userPet[petNo]->getSpeed() + 5);
                        BuffTimer.restart();
                        isBuff = true;
                    }
                }
                if (event.key.code == Keyboard::S)
                {
                    if (user.getNoOfShields() > 0)
                    {
                        clickSound.play();
                        user.setNoOfShields(user.getNoOfShields() - 1);
                        popupClock.restart();
                        popupText.setString("Shield Potion Used");
                        showPopup = true;
                        AiPet[AiPetNo]->setAttackDamage(AiPet[AiPetNo]->getAttackDamage() * 0.5);
                        ShieldPotionClock.restart();
                        ShieldPotion = true;
                    }
                }

                if (event.key.code == Keyboard::X)
                {
                    if (Move2Cooldown.getElapsedTime().asSeconds() > 10.f || ManaPotion)
                    {
                        clickSound.play();
                        popupClock.restart();
                        popupText.setString("Ability 2 Used");
                        showPopup = true;
                        Move2Cooldown.restart();
                        userPet[petNo]->executeMove2(window, AiPet[AiPetNo]);
                        StunTimer.restart();
                        griffinStunTimer.restart();
                        shieldTimer.restart();
                        ManaPotion = false;
                    }
                }
                if (event.key.code == Keyboard::Z)
                {
                    if (Move1Cooldown.getElapsedTime().asSeconds() > 10.f || ManaPotion)
                    {
                        clickSound.play();
                        popupClock.restart();
                        popupText.setString("Ability 1 Used");
                        showPopup = true;
                        Move1Cooldown.restart();
                        userPet[petNo]->executeMove1(window, AiPet[AiPetNo]);
                        SpeedReset.restart();
                        ClawTimer.restart();
                        if (userPet[petNo]->getFireball())
                            fireball.setPosition(userSprite[petNo].getPosition().x + 50, userSprite[petNo].getPosition().y + 40);
                        if (userPet[petNo]->getClaw())
                        {
                            claw.setPosition(userSprite[petNo].getPosition().x + 120, userSprite[petNo].getPosition().y + 40);
                            if (aiSprite[AiPetNo].getPosition().x <= userSprite[petNo].getPosition().x + 150 && aiSprite[AiPetNo].getPosition().x >= userSprite[petNo].getPosition().x)
                            {
                                AiPet[AiPetNo]->setHealth(AiPet[AiPetNo]->getHealth() - userPet[petNo]->getMove1());
                            }
                        }
                        ManaPotion = false;
                    }
                }
                if (event.type == Event::KeyReleased)
                    if (event.key.code == Keyboard::Space)
                    {
                        for (int i = 0; i < MaxbulletCount; ++i)
                        {
                            if (!activeBullets[i])
                            {
                                clickSound.play();
                                activeBullets[i] = true;
                                bullet[i].setPosition(userSprite[petNo].getPosition().x + 50, userSprite[petNo].getPosition().y + 40);
                                break;
                            }
                        }
                    }
                Vector2f direction;
                if (event.key.code == Keyboard::Left)
                    direction = Vector2f(-userPet[petNo]->getSpeed(), 0);
                if (event.key.code == Keyboard::Right)
                    direction = Vector2f(userPet[petNo]->getSpeed(), 0);
                if (event.key.code == Keyboard::Up)
                    direction = Vector2f(0, -userPet[petNo]->getSpeed());
                if (event.key.code == Keyboard::Down)
                    direction = Vector2f(0, userPet[petNo]->getSpeed());

                Sprite tempSprite = userSprite[petNo];
                tempSprite.move(direction);

                if (tempSprite.getPosition().x >= 0 && tempSprite.getPosition().x <= 1100 &&
                    tempSprite.getPosition().y >= 0 && tempSprite.getPosition().y <= 580 &&
                    !checkCollision(tempSprite, sprite_wall1, sprite_wall2, sprite_stone1, sprite_stone2))
                    userSprite[petNo].move(direction);
            }
            if (aiMoveClock.getElapsedTime().asSeconds() > aiMoveInterval)
            {
                int dir = rand() % 4;

                switch (dir)
                {
                case 0:
                    aiDirection = Vector2f(-AiPet[AiPetNo]->getSpeed(), 0);
                    break;
                case 1:
                    aiDirection = Vector2f(AiPet[AiPetNo]->getSpeed(), 0);
                    break;
                case 2:
                    aiDirection = Vector2f(0, -AiPet[AiPetNo]->getSpeed());
                    break;
                case 3:
                    aiDirection = Vector2f(0, AiPet[AiPetNo]->getSpeed());
                    break;
                }

                aiMoveClock.restart();
            }
            window.draw(bg);
            Sprite tempAI = aiSprite[AiPetNo];
            tempAI.move(aiDirection);
            if (tempAI.getPosition().x >= 0 && tempAI.getPosition().x <= 1100 &&
                tempAI.getPosition().y >= 0 && tempAI.getPosition().y <= 580 &&
                !checkCollision(tempAI, sprite_wall1, sprite_wall2, sprite_stone1, sprite_stone2))
            {
                aiSprite[AiPetNo].move(aiDirection);
            }
            if (!AiPet[AiPetNo]->getStun() && !AiPet[AiPetNo]->getGriffinStun())
                if (aiFireClock.getElapsedTime().asSeconds() > aiFireInterval)
                {
                    for (int i = 0; i < MaxAIBullets; ++i)
                    {
                        if (!activeAIBullets[i])
                        {
                            activeAIBullets[i] = true;
                            aiBullet[i].setPosition(aiSprite[AiPetNo].getPosition().x - 20, aiSprite[AiPetNo].getPosition().y + 40);
                            break;
                        }
                    }
                    aiFireClock.restart();
                }
            for (int i = 0; i < MaxAIBullets; ++i)
            {
                if (activeAIBullets[i])
                {
                    aiBullet[i].move(-5, 0);
                    if (checkCollision(aiBullet[i], sprite_wall1, sprite_wall2, sprite_stone1, sprite_stone2) ||
                        aiBullet[i].getPosition().x < 0)
                    {
                        activeAIBullets[i] = false;
                    }
                    if (userSprite[petNo].getGlobalBounds().intersects(aiBullet[i].getGlobalBounds()))
                    {
                        hitSound.play();
                        if (AiPet[AiPetNo]->getAttackDamage() * level > userPet[petNo]->getDefensePower())
                            userPet[petNo]->setHealth(userPet[petNo]->getHealth() - AiPet[AiPetNo]->getAttackDamage() * level + userPet[petNo]->getDefensePower());
                        activeAIBullets[i] = false;
                    }
                }
            }
            for (int i = 0; i < MaxbulletCount; i++)
                if (activeBullets[i] == true)
                    if (checkCollision(bullet[i], sprite_wall1, sprite_wall2, sprite_stone1, sprite_stone2) || bullet[i].getPosition().x > 1270)
                    {
                        activeBullets[i] = false;
                    }
            for (int i = 0; i < MaxbulletCount; i++)
                if (activeBullets[i] == true)
                    if (aiSprite[AiPetNo].getGlobalBounds().intersects(bullet[i].getGlobalBounds()))
                    {
                        hitSound.play();
                        if (userPet[petNo]->getAttackDamage() > AiPet[AiPetNo]->getDefensePower())
                            AiPet[AiPetNo]->setHealth(AiPet[AiPetNo]->getHealth() - userPet[petNo]->getAttackDamage() + AiPet[AiPetNo]->getDefensePower());
                        activeBullets[i] = false;
                    }
            for (int i = 0; i < MaxbulletCount; i++)
            {
                if (activeBullets[i] == true)
                {
                    bullet[i].move(5, 0);
                }
            }
            for (int i = 0; i < MaxbulletCount; i++)
            {
                if (activeBullets[i])
                    window.draw(bullet[i]);
            }
            if (userPet[petNo]->getFireball())
                if (checkCollision(fireball, sprite_wall1, sprite_wall2, sprite_stone1, sprite_stone2))
                {
                    userPet[petNo]->setFireball(false);
                }
            if (userPet[petNo]->getFireball())
                if (aiSprite[AiPetNo].getGlobalBounds().intersects(fireball.getGlobalBounds()))
                {
                    hitSound.play();
                    AiPet[AiPetNo]->setHealth(AiPet[AiPetNo]->getHealth() - userPet[petNo]->getMove1());
                    userPet[petNo]->setFireball(false);
                }

            if (ShieldPotionClock.getElapsedTime().asSeconds() > 10.f && ShieldPotion)
            {
                ShieldPotion = false;
                AiPet[AiPetNo]->setAttackDamage(AiPet[AiPetNo]->getAttackDamage() * 2);
                ShieldPotionClock.restart();
            }

            if (userPet[petNo]->getFireball())
            {
                fireball.move(5, 0);
            }
            if (userPet[petNo]->getClaw())
                if (ClawTimer.getElapsedTime().asSeconds() > 1.f)
                    userPet[petNo]->setClaw(false);
            if (userPet[petNo]->getIsSpeed())
            {
                if (SpeedReset.getElapsedTime().asSeconds() > 2.f)
                {
                    userPet[petNo]->setSpeed(userPet[petNo]->getSpeed() - userPet[petNo]->getMove1());
                    userPet[petNo]->setIsSpeed(false);
                }
            }
            if (AiPet[AiPetNo]->getStun())
            {
                if (StunTimer.getElapsedTime().asSeconds() > userPet[petNo]->getMove2())
                {
                    AiPet[AiPetNo]->setStun(false);
                }
            }
            if (AiPet[AiPetNo]->getGriffinStun())
            {
                if (griffinStunTimer.getElapsedTime().asSeconds() > userPet[petNo]->getMove2())
                {
                    AiPet[AiPetNo]->setGriffinStun(false);
                }
            }
            if (userPet[petNo]->getIsRevive() && userPet[petNo]->getHealth() < 0)
            {
                userPet[petNo]->setHealth(StartHealth[petNo]);
                userPet[petNo]->setIsRevive(false);
            }
            if (!userPet[petNo]->getIsRevive())
            {
                if (userPet[0]->getHealth() < 0 && userPet[1]->getHealth() < 0 && userPet[2]->getHealth() < 0 && userPet[3]->getHealth() < 0)
                {
                    window.clear();
                    Texture losingScreen;
                    if (!losingScreen.loadFromFile("LosePage.png"))
                    {
                        cout << "Image load failure";
                        exit(0);
                    }
                    Sprite loss(losingScreen);
                    window.draw(loss);
                    window.display();
                    sleep(seconds(5));
                    return;
                }
            }
            if (userPet[petNo]->getHealth() < 0 && !userPet[petNo]->getIsRevive())
            {
                if (petNo != 3)
                    petNo++;
                else
                    petNo = 0;
            }
            if (AiPet[AiPetNo]->getHealth() < 0)
            {
                if (AiPetNo != 3)
                    AiPetNo++;
            }
            if (AiPet[3]->getHealth() < 0)
            {
                window.clear();
                Texture WinScreen;
                if (!WinScreen.loadFromFile("WinPage.png"))
                {
                    cout << "Image load failure";
                    exit(0);
                }
                Sprite Win(WinScreen);
                Text popupText;
                popupText.setFont(font);
                popupText.setCharacterSize(28);
                popupText.setFillColor(Color::White);
                popupText.setStyle(Text::Bold);
                popupText.setPosition(X_RESOLUTION / 2.4, Y_RESOLUTION / 1.3);
                user.setCurrency(user.getCurrency() + int(Prize * level));
                popupText.setString("You Got " + to_string(int(Prize * level)) + " Game Currency");
                user.GetGuildById(userGuild.getId())->setGuildScore(user.GetGuildById(userGuild.getId())->getGuildScore() + 50);
                window.draw(Win);
                window.draw(popupText);
                window.display();
                sleep(seconds(5));
                return;
            }
            if (GameClock.getElapsedTime().asSeconds() > TimeLimit)
            {
                int pet1Health = (userPet[0]->getHealth() < 0) ? 0 : userPet[0]->getHealth();
                int pet2Health = (userPet[1]->getHealth() < 0) ? 0 : userPet[1]->getHealth();
                int pet3Health = (userPet[2]->getHealth() < 0) ? 0 : userPet[2]->getHealth();
                int pet4Health = (userPet[3]->getHealth() < 0) ? 0 : userPet[3]->getHealth();
                int Ai1Health = (AiPet[0]->getHealth() < 0) ? 0 : AiPet[0]->getHealth();
                int Ai2Health = (AiPet[1]->getHealth() < 0) ? 0 : AiPet[1]->getHealth();
                int Ai3Health = (AiPet[2]->getHealth() < 0) ? 0 : AiPet[2]->getHealth();
                int Ai4Health = (AiPet[3]->getHealth() < 0) ? 0 : AiPet[3]->getHealth();
                if ((pet1Health + pet2Health + pet3Health + pet4Health) < (Ai1Health + Ai2Health + Ai3Health + Ai4Health))
                {
                    window.clear();
                    Texture losingScreen;
                    if (!losingScreen.loadFromFile("LosePage.png"))
                    {
                        cout << "Image load failure";
                        exit(0);
                    }
                    Sprite loss(losingScreen);
                    window.draw(loss);
                    window.display();
                    sleep(seconds(5));
                    return;
                }
                if ((pet1Health + pet2Health + pet3Health + pet4Health) >= (Ai1Health + Ai2Health + Ai3Health + Ai4Health))
                {
                    window.clear();
                    Texture WinScreen;
                    if (!WinScreen.loadFromFile("WinPage.png"))
                    {
                        cout << "Image load failure";
                        exit(0);
                    }
                    Sprite Win(WinScreen);
                    Text popupText;
                    popupText.setFont(font);
                    popupText.setCharacterSize(28);
                    popupText.setFillColor(Color::White);
                    popupText.setStyle(Text::Bold);
                    popupText.setPosition(X_RESOLUTION / 2.4, Y_RESOLUTION / 1.3);
                    user.setCurrency(user.getCurrency() + int(Prize * level));
                    popupText.setString("You Got " + to_string(int(Prize * level)) + " Game Currency");
                    user.GetGuildById(userGuild.getId())->setGuildScore(user.GetGuildById(userGuild.getId())->getGuildScore() + 50);
                    window.draw(Win);
                    window.draw(popupText);
                    window.display();
                    sleep(seconds(5));
                    return;
                }
            }
            if (userPet[petNo]->getIsShield() && shieldTimer.getElapsedTime().asSeconds() > 5.f)
            {
                AiPet[AiPetNo]->setAttackDamage(AiPet[AiPetNo]->getAttackDamage() + userPet[petNo]->getMove2());
                userPet[petNo]->setIsShield(false);
                shieldTimer.restart();
            }
            if (isBuff)
                if (BuffTimer.getElapsedTime().asSeconds() > 5.f)
                {
                    userPet[petNo]->setAttackDamage(userPet[petNo]->getAttackDamage() - 20);
                    userPet[petNo]->setSpeed(userPet[petNo]->getSpeed() - 5);
                    isBuff = false;
                }
            if (potionTimer.getElapsedTime().asSeconds() > 10.f)
            {
                do
                {
                    float x = rand() % (1280 - 64);
                    float y = rand() % (720 - 64);
                    potion.setPosition(x, y);
                } while (checkCollision(potion, sprite_wall1, sprite_wall2, sprite_stone1, sprite_stone2));

                showPotion = true;
                potionTimer.restart();
            }
            if (potion.getGlobalBounds().intersects(userSprite[petNo].getGlobalBounds()) && showPotion)
            {
                showPotion = false;
                int num = rand() % 4 + 1;
                if (num == 1)
                {
                    popupClock.restart();
                    popupText.setString("Mana Potion Collected");
                    showPopup = true;
                    ManaPotion = true;
                }
                if (num == 2)
                {
                    popupClock.restart();
                    popupText.setString("Heal Potion Collected");
                    showPopup = true;
                    if (userPet[petNo]->getHealth() < StartHealth[petNo])
                        userPet[petNo]->setHealth(StartHealth[petNo]);
                }
                if (num == 3)
                {
                    popupClock.restart();
                    popupText.setString("Buff Potion Collected");
                    showPopup = true;
                    userPet[petNo]->setAttackDamage(userPet[petNo]->getAttackDamage() + 20);
                    userPet[petNo]->setSpeed(userPet[petNo]->getSpeed() + 5);
                    BuffTimer.restart();
                    isBuff = true;
                }
                if (num == 4)
                {
                    popupClock.restart();
                    popupText.setString("Shield Potion Collected");
                    showPopup = true;
                    AiPet[AiPetNo]->setAttackDamage(AiPet[AiPetNo]->getAttackDamage() * 0.5);
                    ShieldPotionClock.restart();
                    ShieldPotion = true;
                }
                potionTimer.restart();
            }
            clock.setString(to_string(int(TimeLimit - GameClock.getElapsedTime().asSeconds())));
            window.draw(sprite_stone1);
            window.draw(sprite_stone2);
            window.draw(sprite_wall1);
            window.draw(sprite_wall2);
            window.draw(clock);
            for (int i = 0; i < MaxAIBullets; ++i)
            {
                if (activeAIBullets[i])
                    window.draw(aiBullet[i]);
            }
            for (int i = 0; i < MaxAIBullets; ++i)
            {
                if (activeAIBullets[i])
                    window.draw(aiBullet[i]);
            }
            if (showPotion)
                window.draw(potion);
            if (showPopup && popupClock.getElapsedTime() > seconds(2))
            {
                showPopup = false;
            }
            if (showPopup)
                window.draw(popupText);
            window.draw(aiSprite[AiPetNo]);
            window.draw(userSprite[petNo]);
            if (userPet[petNo]->getClaw())
                window.draw(claw);
            if (userPet[petNo]->getFireball())
                window.draw(fireball);
            window.draw(AiHealth);
            window.draw(userHealth);
            window.display();
        }
    }
};

// creates a button with the passed attributes
void createButtonWithText(RectangleShape *&btn, Text *&txt, Font &font, const string &label,
                          double row, double col, float width, Color fillColor, Color outlineColor)
{
    btn = new RectangleShape(Vector2f(width, 50));
    btn->setFillColor(fillColor);
    btn->setOutlineThickness(3);
    btn->setOutlineColor(outlineColor);
    btn->setPosition(col * CELL_SIZE, row * CELL_SIZE);

    txt = new Text();
    txt->setFont(font);
    txt->setString(label);
    txt->setCharacterSize(24);
    txt->setFillColor(Color::White);

    FloatRect textRect = txt->getLocalBounds();
    float textX = btn->getPosition().x + (width - textRect.width) / 2;
    float textY = btn->getPosition().y + (50 - textRect.height) / 2 - 5;
    txt->setPosition(textX, textY);
}
// Creates button without text
void CreateButton(RectangleShape *&btn, double row, double col, float width, Color fillColor, Color outlineColor)
{
    btn = new RectangleShape(Vector2f(width, 50));
    btn->setFillColor(fillColor);
    btn->setOutlineThickness(3);
    btn->setOutlineColor(outlineColor);
    btn->setPosition(col * CELL_SIZE, row * CELL_SIZE);
}
class Game
{
public:
    void UpgradePet(RenderWindow &window, Player &user, Text popupText, Font &font)
    {
        bool showPopup = false;
        popupText.setPosition(popupText.getPosition().x, popupText.getPosition().y - 80);
        RectangleShape *ReturnBtn = nullptr;
        Text *ReturnTxt = nullptr;
        RectangleShape *PhoenixBtn = nullptr;
        RectangleShape *DragonBtn = nullptr;
        RectangleShape *UnicornBtn = nullptr;
        RectangleShape *GriffinBtn = nullptr;
        Text *PhoenixTxt = nullptr;
        Text *DragonTxt = nullptr;
        Text *UnicornTxt = nullptr;
        Text *GriffinTxt = nullptr;
        while (window.isOpen())
        {
            window.clear();
            Texture GuildBG;
            if (!GuildBG.loadFromFile("GuildWallpaper.png"))
            {
                cout << "Image load Failure";
                exit(0);
            }
            Clock popupClock;
            Time popupDuration = seconds(2);
            Sprite guildBG(GuildBG);
            Text PhoenixPrice("Training Tokens Cost :" + to_string(user.getPet(1)->getCurrentLevel() * 100), font, 24);
            Text UnicornPrice("Training Tokens Cost :" + to_string(user.getPet(2)->getCurrentLevel() * 100), font, 24);
            Text DragonPrice("Training Tokens Cost :" + to_string(user.getPet(0)->getCurrentLevel() * 100), font, 24);
            Text GriffinPrice("Training Tokens Cost :" + to_string(user.getPet(3)->getCurrentLevel() * 100), font, 24);
            Text PhoenixTokens("Current Tokens :" + to_string(user.getPet(1)->getTrainingPoints()), font, 24);
            Text UnicornTokens("Current Tokens :" + to_string(user.getPet(2)->getTrainingPoints()), font, 24);
            Text DragonTokens("Current Tokens :" + to_string(user.getPet(0)->getTrainingPoints()), font, 24);
            Text GriffinTokens("Current Tokens :" + to_string(user.getPet(3)->getTrainingPoints()), font, 24);

            Text PhoenixLevel("Level :" + to_string(user.getPet(1)->getCurrentLevel()), font, 24);
            Text UnicornLevel("Level: :" + to_string(user.getPet(2)->getCurrentLevel()), font, 24);
            Text DragonLevel("Level: :" + to_string(user.getPet(0)->getCurrentLevel()), font, 24);
            Text GriffinLevel("Level: :" + to_string(user.getPet(3)->getCurrentLevel()), font, 24);
            createButtonWithText(ReturnBtn, ReturnTxt, font, "Esc", 0.2, 0.5, 80, Color(30, 30, 30), Color::Black);
            createButtonWithText(DragonBtn, DragonTxt, font, "Dragon(D)", 4, 6, 150, Color(30, 30, 30), Color::Black);
            createButtonWithText(PhoenixBtn, PhoenixTxt, font, "Phoenix(P)", 8, 6, 150, Color(30, 30, 30), Color::Black);
            createButtonWithText(UnicornBtn, UnicornTxt, font, "Unicorn(C)", 4, 12, 150, Color(30, 30, 30), Color::Black);
            createButtonWithText(GriffinBtn, GriffinTxt, font, "Griffin(G)", 8, 12, 150, Color(30, 30, 30), Color::Black);
            PhoenixPrice.setPosition(PhoenixBtn->getPosition().x, PhoenixBtn->getPosition().y + 90);
            UnicornPrice.setPosition(UnicornBtn->getPosition().x, UnicornBtn->getPosition().y + 90);
            DragonPrice.setPosition(DragonBtn->getPosition().x, DragonBtn->getPosition().y + 90);
            GriffinPrice.setPosition(GriffinBtn->getPosition().x, GriffinBtn->getPosition().y + 90);

            PhoenixTokens.setPosition(PhoenixBtn->getPosition().x, PhoenixBtn->getPosition().y + 50);
            UnicornTokens.setPosition(UnicornBtn->getPosition().x, UnicornBtn->getPosition().y + 50);
            DragonTokens.setPosition(DragonBtn->getPosition().x, DragonBtn->getPosition().y + 50);
            GriffinTokens.setPosition(GriffinBtn->getPosition().x, GriffinBtn->getPosition().y + 50);

            PhoenixLevel.setPosition(PhoenixBtn->getPosition().x, PhoenixBtn->getPosition().y - 70);
            UnicornLevel.setPosition(UnicornBtn->getPosition().x, UnicornBtn->getPosition().y - 70);
            DragonLevel.setPosition(DragonBtn->getPosition().x, DragonBtn->getPosition().y - 70);
            GriffinLevel.setPosition(GriffinBtn->getPosition().x, GriffinBtn->getPosition().y - 70);

            Text T("Choose Pet For Upgrade", font, 24);
            T.setPosition(9 * CELL_SIZE, 1 * CELL_SIZE);
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
                if (event.type == Event::KeyPressed)
                {
                    if (event.key.code == Keyboard::Escape)
                    {
                        clickSound.play();
                        goto DeleteData;
                    }

                    if (event.key.code == Keyboard::D)
                    {
                        clickSound.play();
                        if (user.getPet(0)->getCurrentLevel() >= user.getPet(0)->getMaxLevel())
                        {
                            popupText.setString("Max Level Reached");
                            showPopup = true;
                            popupClock.restart();
                        }
                        else if (user.getPet(0)->getTrainingPoints() < user.getPet(0)->getCurrentLevel() * 100)
                        {
                            popupText.setString("Not Enough Training Tokens");
                            showPopup = true;
                            popupClock.restart();
                        }
                        else
                        {
                            user.getPet(0)->setTrainingPoints(user.getPet(0)->getTrainingPoints() - user.getPet(0)->getCurrentLevel() * 100);
                            user.getPet(0)->setCurrentLevel(user.getPet(0)->getCurrentLevel() + 1);
                            user.getPet(0)->setAttackDamage(user.getPet(0)->getAttackDamage() + 10);
                            user.getPet(0)->setDefensePower(user.getPet(0)->getDefensePower() + 5);
                            user.getPet(0)->setHealth(user.getPet(0)->getHealth() + 50);
                            user.getPet(0)->setMove1(user.getPet(0)->getMove1() + 30);
                            user.getPet(0)->setMove2(user.getPet(0)->getMove2() + 1);
                            popupText.setString("Upgraded");
                            showPopup = true;
                            popupClock.restart();
                        }
                    }
                    if (event.key.code == Keyboard::P)
                    {
                        clickSound.play();
                        if (user.getPet(1)->getCurrentLevel() >= user.getPet(1)->getMaxLevel())
                        {
                            popupText.setString("Max Level Reached");
                            showPopup = true;
                            popupClock.restart();
                        }
                        else if (user.getPet(1)->getTrainingPoints() < user.getPet(1)->getCurrentLevel() * 100)
                        {
                            popupText.setString("Not Enough Training Tokens");
                            showPopup = true;
                            popupClock.restart();
                        }
                        else
                        {
                            user.getPet(1)->setTrainingPoints(user.getPet(1)->getTrainingPoints() - user.getPet(1)->getCurrentLevel() * 100);
                            user.getPet(1)->setCurrentLevel(user.getPet(1)->getCurrentLevel() + 1);
                            user.getPet(1)->setAttackDamage(user.getPet(1)->getAttackDamage() + 10);
                            user.getPet(1)->setDefensePower(user.getPet(1)->getDefensePower() + 5);
                            user.getPet(1)->setHealth(user.getPet(1)->getHealth() + 50);
                            user.getPet(1)->setMove1(user.getPet(1)->getMove1() + 20);
                            popupText.setString("Upgraded");
                            showPopup = true;
                            popupClock.restart();
                        }
                    }
                    if (event.key.code == Keyboard::C)
                    {
                        clickSound.play();
                        if (user.getPet(2)->getCurrentLevel() >= user.getPet(2)->getMaxLevel())
                        {
                            popupText.setString("Max Level Reached");
                            showPopup = true;
                            popupClock.restart();
                        }
                        else if (user.getPet(2)->getTrainingPoints() < user.getPet(2)->getCurrentLevel() * 100)
                        {
                            popupText.setString("Not Enough Training Tokens");
                            showPopup = true;
                            popupClock.restart();
                        }
                        else
                        {
                            user.getPet(2)->setTrainingPoints(user.getPet(2)->getTrainingPoints() - user.getPet(2)->getCurrentLevel() * 100);
                            user.getPet(2)->setCurrentLevel(user.getPet(2)->getCurrentLevel() + 1);
                            user.getPet(2)->setAttackDamage(user.getPet(2)->getAttackDamage() + 10);
                            user.getPet(2)->setDefensePower(user.getPet(2)->getDefensePower() + 5);
                            user.getPet(2)->setHealth(user.getPet(2)->getHealth() + 50);
                            user.getPet(2)->setMove1(user.getPet(2)->getMove1() + 2);
                            user.getPet(2)->setMove2(user.getPet(2)->getMove2() + 8);

                            popupText.setString("Upgraded");
                            showPopup = true;
                            popupClock.restart();
                        }
                    }
                    if (event.key.code == Keyboard::G)
                    {
                        clickSound.play();
                        if (user.getPet(3)->getCurrentLevel() >= user.getPet(3)->getMaxLevel())
                        {
                            popupText.setString("Max Level Reached");
                            showPopup = true;
                            popupClock.restart();
                        }
                        else if (user.getPet(3)->getTrainingPoints() < user.getPet(3)->getCurrentLevel() * 100)
                        {
                            popupText.setString("Not Enough Training Tokens");
                            showPopup = true;
                            popupClock.restart();
                        }
                        else
                        {
                            user.getPet(3)->setTrainingPoints(user.getPet(3)->getTrainingPoints() - user.getPet(3)->getCurrentLevel() * 100);
                            user.getPet(3)->setCurrentLevel(user.getPet(3)->getCurrentLevel() + 1);
                            user.getPet(3)->setAttackDamage(user.getPet(3)->getAttackDamage() + 10);
                            user.getPet(3)->setDefensePower(user.getPet(3)->getDefensePower() + 5);
                            user.getPet(3)->setHealth(user.getPet(3)->getHealth() + 50);
                            user.getPet(3)->setMove1(user.getPet(3)->getMove1() + 15);
                            user.getPet(3)->setMove2(user.getPet(3)->getMove2() + 1);
                            popupText.setString("Upgraded");
                            showPopup = true;
                            popupClock.restart();
                        }
                    }
                }
            }
            window.draw(guildBG);
            if (showPopup && popupClock.getElapsedTime() > popupDuration)
                showPopup = false;

            if (showPopup)
                window.draw(popupText);

            window.draw(*PhoenixBtn);
            window.draw(*PhoenixTxt);
            window.draw(*UnicornBtn);
            window.draw(*UnicornTxt);
            window.draw(*DragonBtn);
            window.draw(*DragonTxt);
            window.draw(*GriffinBtn);
            window.draw(*GriffinTxt);
            window.draw(T);
            window.draw(*ReturnBtn);
            window.draw(*ReturnTxt);
            window.draw(PhoenixPrice);
            window.draw(UnicornPrice);
            window.draw(GriffinPrice);
            window.draw(DragonPrice);
            window.draw(PhoenixTokens);
            window.draw(UnicornTokens);
            window.draw(GriffinTokens);
            window.draw(DragonTokens);
            window.draw(PhoenixLevel);
            window.draw(UnicornLevel);
            window.draw(GriffinLevel);
            window.draw(DragonLevel);
            window.display();
        }
    DeleteData:
        delete ReturnBtn;
        delete ReturnTxt;
        delete PhoenixBtn;
        delete DragonBtn;
        delete UnicornBtn;
        delete GriffinBtn;
        delete PhoenixTxt;
        delete DragonTxt;
        delete UnicornTxt;
        delete GriffinTxt;
    }
    void showManual(RenderWindow &window)
    {
        window.clear();
        Texture image;
        if (!image.loadFromFile("GameManual.png"))
        {
            cout << "Image load Failure";
            exit(0);
        }
        Sprite Manual(image);
        window.draw(Manual);
        window.display();
        sleep(seconds(5));
    }
    void AskPetfor1V1(RenderWindow &window, Player &user, Text &popupText, Font &font, oneVone &Battle1)
    {
        Texture BG;
        if (!BG.loadFromFile("GuildWallpaper.png"))
        {
            cout << "Image load Failure";
            exit(0);
        }
        Sprite bg(BG);
        RectangleShape *ReturnBtn = nullptr;
        Text *ReturnTxt = nullptr;
        RectangleShape *PhoenixBtn = nullptr;
        RectangleShape *DragonBtn = nullptr;
        RectangleShape *UnicornBtn = nullptr;
        RectangleShape *GriffinBtn = nullptr;
        Text *PhoenixTxt = nullptr;
        Text *DragonTxt = nullptr;
        Text *UnicornTxt = nullptr;
        Text *GriffinTxt = nullptr;
        popupText.setString("Choose Pet For Battle");
        createButtonWithText(DragonBtn, DragonTxt, font, "Dragon(D)", 5, 6, 150, Color(30, 30, 30), Color::Black);
        createButtonWithText(PhoenixBtn, PhoenixTxt, font, "Phoenix(P)", 8, 6, 150, Color(30, 30, 30), Color::Black);
        createButtonWithText(UnicornBtn, UnicornTxt, font, "Unicorn(U)", 5, 12, 150, Color(30, 30, 30), Color::Black);
        createButtonWithText(GriffinBtn, GriffinTxt, font, "Griffin(G)", 8, 12, 150, Color(30, 30, 30), Color::Black);
        createButtonWithText(ReturnBtn, ReturnTxt, font, "Esc", 0.2, 0.5, 80, Color(30, 30, 30), Color::Black);
        int num = rand() % 4;
        Battle1.setAiPet(user.getPet(num)->copy());

        while (window.isOpen())
        {
            window.clear();
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
                if (event.type == Event::KeyPressed)
                {
                    if (event.key.code == Keyboard::Escape)
                    {
                        clickSound.play();
                        goto DeleteData;
                    }
                    if (event.key.code == Keyboard::D)
                    {
                        clickSound.play();
                        Battle1.setUserPet(user.getPet(0)->copy());
                    }
                    if (event.key.code == Keyboard::P)
                    {
                        clickSound.play();
                        Battle1.setUserPet(user.getPet(1)->copy());
                    }
                    if (event.key.code == Keyboard::U)
                    {
                        clickSound.play();
                        Battle1.setUserPet(user.getPet(2)->copy());
                    }
                    if (event.key.code == Keyboard::G)
                    {
                        clickSound.play();
                        Battle1.setUserPet(user.getPet(3)->copy());
                    }
                }
            }
            if (Battle1.getUserPet() != nullptr)
            {
                showManual(window);
                Battle1.Battle(window, font, user);
                Battle1.setAiPet(nullptr);
                Battle1.setUserPet(nullptr);
                goto DeleteData;
            }
            window.draw(bg);
            window.draw(popupText);
            window.draw(*PhoenixBtn);
            window.draw(*PhoenixTxt);
            window.draw(*UnicornBtn);
            window.draw(*UnicornTxt);
            window.draw(*DragonBtn);
            window.draw(*DragonTxt);
            window.draw(*GriffinBtn);
            window.draw(*GriffinTxt);
            window.draw(*ReturnBtn);
            window.draw(*ReturnTxt);
            window.display();
        }
    DeleteData:
        delete ReturnBtn;
        delete ReturnTxt;
        delete PhoenixBtn;
        delete DragonBtn;
        delete UnicornBtn;
        delete GriffinBtn;
        delete PhoenixTxt;
        delete DragonTxt;
        delete UnicornTxt;
        delete GriffinTxt;
    }
    void AskPetfor2V2(RenderWindow &window, Player &user, Text &popupText, Font &font, twoVtwo &Battle2)
    {
        Texture BG;
        if (!BG.loadFromFile("GuildWallpaper.png"))
        {
            cout << "Image load Failure";
            exit(0);
        }
        int petIndex = -1;
        Sprite bg(BG);
        RectangleShape *ReturnBtn = nullptr;
        Text *ReturnTxt = nullptr;
        RectangleShape *PhoenixBtn = nullptr;
        RectangleShape *DragonBtn = nullptr;
        RectangleShape *UnicornBtn = nullptr;
        RectangleShape *GriffinBtn = nullptr;
        Text *PhoenixTxt = nullptr;
        Text *DragonTxt = nullptr;
        Text *UnicornTxt = nullptr;
        Text *GriffinTxt = nullptr;
        int count = 0;
        popupText.setString("Choose first Pet For Battle");
        createButtonWithText(DragonBtn, DragonTxt, font, "Dragon(D)", 5, 6, 150, Color(30, 30, 30), Color::Black);
        createButtonWithText(PhoenixBtn, PhoenixTxt, font, "Phoenix(P)", 8, 6, 150, Color(30, 30, 30), Color::Black);
        createButtonWithText(UnicornBtn, UnicornTxt, font, "Unicorn(U)", 5, 12, 150, Color(30, 30, 30), Color::Black);
        createButtonWithText(GriffinBtn, GriffinTxt, font, "Griffin(G)", 8, 12, 150, Color(30, 30, 30), Color::Black);
        createButtonWithText(ReturnBtn, ReturnTxt, font, "Esc", 0.2, 0.5, 80, Color(30, 30, 30), Color::Black);
        int a = rand() % 4;
        int b;
        do
        {
            b = rand() % 4;
        } while (b == a);
        Battle2.setAiPet(user.getPet(a)->copy(), 0);
        Battle2.setAiPet(user.getPet(b)->copy(), 1);

        while (window.isOpen())
        {
            window.clear();
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
                if (event.type == Event::KeyPressed)
                {
                    if (event.key.code == Keyboard::Escape)
                    {
                        clickSound.play();
                        goto DeleteData;
                    }
                    if (event.key.code == Keyboard::D)
                    {

                        if (count == 0)
                        {
                            clickSound.play();
                            petIndex = 1;
                            Battle2.setUserPet(user.getPet(0)->copy(), count);
                            count++;
                        }
                        if (count == 1)
                            if (petIndex != 1)
                            {
                                clickSound.play();
                                Battle2.setUserPet(user.getPet(0)->copy(), count);
                                count++;
                            }
                    }
                    if (event.key.code == Keyboard::P)
                    {
                        if (count == 0)
                        {
                            clickSound.play();
                            petIndex = 2;
                            Battle2.setUserPet(user.getPet(1)->copy(), count);
                            count++;
                        }
                        if (count == 1)
                            if (petIndex != 2)
                            {
                                clickSound.play();
                                Battle2.setUserPet(user.getPet(1)->copy(), count);
                                count++;
                            }
                    }
                    if (event.key.code == Keyboard::U)
                    {
                        if (count == 0)
                        {
                            clickSound.play();
                            petIndex = 3;
                            Battle2.setUserPet(user.getPet(2)->copy(), count);
                            count++;
                        }
                        if (count == 1)
                            if (petIndex != 3)
                            {
                                clickSound.play();
                                Battle2.setUserPet(user.getPet(2)->copy(), count);
                                count++;
                            }
                    }
                    if (event.key.code == Keyboard::G)
                    {
                        if (count == 0)
                        {
                            clickSound.play();
                            petIndex = 4;
                            Battle2.setUserPet(user.getPet(3)->copy(), count);
                            count++;
                        }
                        if (count == 1)
                            if (petIndex != 4)
                            {
                                clickSound.play();
                                Battle2.setUserPet(user.getPet(3)->copy(), count);
                                count++;
                            }
                    }
                }
            }
            if (count == 1)
                popupText.setString("Choose Second Pet for Battle");
            if (count == 2)
            {
                showManual(window);
                Battle2.Battle(window, font, user);
                Battle2.setAiPet(nullptr, 0);
                Battle2.setAiPet(nullptr, 1);
                Battle2.setUserPet(nullptr, 0);
                Battle2.setUserPet(nullptr, 1);
                goto DeleteData;
            }
            window.draw(bg);
            window.draw(popupText);
            window.draw(*PhoenixBtn);
            window.draw(*PhoenixTxt);
            window.draw(*UnicornBtn);
            window.draw(*UnicornTxt);
            window.draw(*DragonBtn);
            window.draw(*DragonTxt);
            window.draw(*GriffinBtn);
            window.draw(*GriffinTxt);
            window.draw(*ReturnBtn);
            window.draw(*ReturnTxt);
            window.display();
        }
    DeleteData:
        delete ReturnBtn;
        delete ReturnTxt;
        delete PhoenixBtn;
        delete DragonBtn;
        delete UnicornBtn;
        delete GriffinBtn;
        delete PhoenixTxt;
        delete DragonTxt;
        delete UnicornTxt;
        delete GriffinTxt;
    }
    void AskBattleGuild(RenderWindow &window, Player &user, Text &popupText, Font &font, guildVguild &BattleG)
    {
        string GuildID = "";
        bool showPopup = false;
        Clock popupClock;
        RectangleShape *ReturnBtn = nullptr;
        Text *ReturnTxt = nullptr;
        Time popupDuration = seconds(2);
        while (window.isOpen())
        {
            window.clear();
            Texture GuildBG;
            if (!GuildBG.loadFromFile("GuildWallpaper.png"))
            {
                cout << "Image load Failure";
                return;
            }
            Sprite guildBG(GuildBG);
            RectangleShape *IdBox;
            Text Label("Guild ID : ", font, 24);
            Label.setPosition(12 * CELL_SIZE, 4.5 * CELL_SIZE);
            Text Text(GuildID, font, 24);
            Text.setFillColor(Color::Black);
            Text.setPosition(12 * CELL_SIZE, 5.5 * CELL_SIZE);
            createButtonWithText(ReturnBtn, ReturnTxt, font, "Esc", 0.2, 0.5, 80, Color(30, 30, 30), Color::Black);
            CreateButton(IdBox, 5.5, 12, 200, Color::White, Color::Black);
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
                if (event.type == Event::KeyPressed)
                {
                    if (event.key.code == Keyboard::Escape)
                    {
                        clickSound.play();
                        goto DeleteData;
                    }
                    if (event.key.code == Keyboard::BackSpace)
                    {
                        if (GuildID.length() > 0)
                            GuildID.pop_back();
                    }
                    if (event.key.code == Keyboard::Enter)
                    {
                        clickSound.play();
                        bool Exists = false;
                        int index;
                        for (int i = 0; i < user.getNoOfGuilds(); i++)
                        {
                            if (GuildID == user.GetGuild(i)->getId())
                            {
                                Exists = true;
                                index = i;
                            }
                        }
                        if (Exists == false)
                        {
                            popupText.setString("No Guild Exist with Given ID!");
                            popupClock.restart();
                            showPopup = true;
                        }
                        else if (Exists == true)
                        {
                            BattleG.setAiGuild(*user.GetGuild(index));
                            BattleG.setUserGuild(*user.GetGuild(index));
                            showManual(window);
                            BattleG.Battle(window, font, user);
                            goto DeleteData;
                        }
                    }
                }
                if (event.type == Event::TextEntered)
                {
                    if (event.text.unicode < 128 && event.text.unicode != 8 && event.text.unicode != 13)
                        GuildID += static_cast<char>(event.text.unicode);
                }
            }
            window.draw(guildBG);
            window.draw(*IdBox);
            window.draw(*ReturnBtn);
            window.draw(*ReturnTxt);
            window.draw(Label);
            window.draw(Text);
            if (showPopup && popupClock.getElapsedTime() > popupDuration)
            {
                showPopup = false;
            }
            if (showPopup)
                window.draw(popupText);
            window.display();
        }
    DeleteData:
        delete ReturnBtn;
        delete ReturnTxt;
    }
    void AskBattleType(RenderWindow &window, Player &user, Text &popupText, Font &font, oneVone &Battle1, twoVtwo &Battle2, guildVguild &BattleG)
    {
        RectangleShape *oneVoneBtn = nullptr;
        Text *oneVoneTxt = nullptr;
        RectangleShape *twoVtwoBtn = nullptr;
        Text *twoVtwoTxt = nullptr;
        RectangleShape *guildVguildBtn = nullptr;
        Text *guildVguildTxt = nullptr;
        RectangleShape *ReturnBtn = nullptr;
        Text *ReturnTxt = nullptr;
        createButtonWithText(ReturnBtn, ReturnTxt, font, "Esc", 0.2, 0.5, 80, Color(30, 30, 30), Color::Black);
        createButtonWithText(oneVoneBtn, oneVoneTxt, font, "1 V 1 (1)", 5, 12, 200, Color(30, 30, 30), Color::Black);
        createButtonWithText(twoVtwoBtn, twoVtwoTxt, font, "2 V 2 (2)", 7, 12, 200, Color(30, 30, 30), Color::Black);
        createButtonWithText(guildVguildBtn, guildVguildTxt, font, "G V G (G)", 9, 12, 200, Color(30, 30, 30), Color::Black);
        popupText.setString("Choose Mode ");
        while (window.isOpen())
        {
            window.clear();
            Texture BG;
            if (!BG.loadFromFile("GuildWallpaper.png"))
            {
                cout << "Image load Failure";
                exit(0);
            }
            Sprite bg(BG);
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
                if (event.type == Event::KeyPressed)
                {
                    if (event.key.code == Keyboard::Escape)
                    {

                        clickSound.play();
                        goto DeleteData;
                    }
                    if (event.key.code == Keyboard::Num1)
                    {
                        clickSound.play();
                        AskPetfor1V1(window, user, popupText, font, Battle1);
                        goto DeleteData;
                    }
                    if (event.key.code == Keyboard::Num2)
                    {
                        clickSound.play();
                        AskPetfor2V2(window, user, popupText, font, Battle2);
                        goto DeleteData;
                    }
                    if (event.key.code == Keyboard::G)
                    {
                        clickSound.play();
                        AskBattleGuild(window, user, popupText, font, BattleG);
                        goto DeleteData;
                    }
                }
            }
            window.draw(bg);
            window.draw(*ReturnBtn);
            window.draw(*ReturnTxt);
            window.draw(*oneVoneBtn);
            window.draw(*oneVoneTxt);
            window.draw(*twoVtwoBtn);
            window.draw(*twoVtwoTxt);
            window.draw(*guildVguildBtn);
            window.draw(*guildVguildTxt);
            window.draw(popupText);
            window.display();
        }
    DeleteData:
        delete oneVoneBtn;
        delete oneVoneTxt;
        delete twoVtwoBtn;
        delete twoVtwoTxt;
        delete guildVguildBtn;
        delete guildVguildTxt;
        delete ReturnBtn;
        delete ReturnTxt;
    }
    void showShop(RenderWindow &window, Shop &items, Font &font, Player &user, Text &popupText)
    {
        bool showPopup = false;
        Clock popupClock;
        Time popupDuration = seconds(2);
        RectangleShape *ShieldBtn = nullptr;
        Text *ShieldTxt = nullptr;
        RectangleShape *ManaBtn = nullptr;
        RectangleShape *ReturnBtn = nullptr;
        Text *ReturnTxt = nullptr;
        Text *ManaTxt = nullptr;
        RectangleShape *HealBtn = nullptr;
        Text *HealTxt = nullptr;
        RectangleShape *BuffBtn = nullptr;
        Text *BuffTxt = nullptr;
        while (window.isOpen())
        {
            window.clear();
            Texture Shop;
            Texture Diamond;
            if (!Shop.loadFromFile("shop.png"))
            {
                cout << "Image load Failure";
                exit(0);
            }
            if (!Diamond.loadFromFile("Diamond.png"))
            {
                cout << "Image load Failure";
                exit(0);
            }
            Sprite shop(Shop);
            Sprite Currency(Diamond);
            Currency.setPosition(17 * CELL_SIZE, 0.08 * CELL_SIZE);

            Text NoCurrency;
            NoCurrency.setFont(font);
            NoCurrency.setString(to_string(user.getCurrency()));
            NoCurrency.setCharacterSize(24);
            NoCurrency.setFillColor(Color::White);
            NoCurrency.setPosition(Currency.getPosition().x + 60, Currency.getPosition().y + 25);
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
                if (event.type == Event::KeyPressed)
                {
                    if (event.key.code == Keyboard::Escape)
                    {
                        clickSound.play();
                        goto DeleteData;
                    }
                    if (event.key.code == Keyboard::M)
                    {
                        clickSound.play();
                        if (items.getPriceMana() <= user.getCurrency())
                        {

                            user.setNoOfManaPotions(user.getNoOfManaPotions() + 1);
                            user.setCurrency(user.getCurrency() - items.getPriceMana());
                            popupText.setString("Item Purchased!");
                            popupClock.restart();
                            showPopup = true;
                        }
                        else
                        {
                            popupText.setString("Not Enough Currency!");
                            popupClock.restart();
                            showPopup = true;
                        }
                    }
                    if (event.key.code == Keyboard::H)
                    {
                        clickSound.play();
                        if (items.getPriceHeal() <= user.getCurrency())
                        {
                            user.setNoOfHealingPotions(user.getNoOfHealingPotions() + 1);
                            user.setCurrency(user.getCurrency() - items.getPriceHeal());
                            popupText.setString("Item Purchased!");
                            popupClock.restart();
                            showPopup = true;
                        }
                        else
                        {
                            popupText.setString("Not Enough Currency!");
                            popupClock.restart();
                            showPopup = true;
                        }
                    }
                    if (event.key.code == Keyboard::B)
                    {
                        clickSound.play();
                        if (items.getPriceBuff() <= user.getCurrency())
                        {
                            user.setNoOfBuffItems(user.getNoOfBuffItems() + 1);
                            user.setCurrency(user.getCurrency() - items.getPriceBuff());
                            popupText.setString("Item Purchased!");
                            popupClock.restart();
                            showPopup = true;
                        }
                        else
                        {
                            popupText.setString("Not Enough Currency!");
                            popupClock.restart();
                            showPopup = true;
                        }
                    }
                    if (event.key.code == Keyboard::S)
                    {
                        clickSound.play();
                        if (items.getPriceShield() <= user.getCurrency())
                        {
                            user.setNoOfShields(user.getNoOfShields() + 1);
                            user.setCurrency(user.getCurrency() - items.getPriceShield());
                            popupText.setString("Item Purchased!");
                            popupClock.restart();
                            showPopup = true;
                        }
                        else
                        {
                            popupText.setString("Not Enough Currency!");
                            popupClock.restart();
                            showPopup = true;
                        }
                    }
                }
            }
            string shield = "Shield(S)(" + to_string(items.getPriceShield()) + ')';
            string mana = "Mana(M)(" + to_string(items.getPriceMana()) + ')';
            string buff = "Buff(B)(" + to_string(items.getPriceBuff()) + ')';
            string heal = "Heal(H)(" + to_string(items.getPriceHeal()) + ')';
            createButtonWithText(ReturnBtn, ReturnTxt, font, "Esc", 0.2, 0.5, 80, Color(30, 30, 30), Color::Black);
            createButtonWithText(ShieldBtn, ShieldTxt, font, shield, 10, 1, 200, Color(30, 30, 30), Color::Black);
            createButtonWithText(ManaBtn, ManaTxt, font, mana, 10, 5, 200, Color(30, 30, 30), Color::Black);
            createButtonWithText(BuffBtn, BuffTxt, font, buff, 10, 9, 200, Color(30, 30, 30), Color::Black);
            createButtonWithText(HealBtn, HealTxt, font, heal, 10, 12.5, 200, Color(30, 30, 30), Color::Black);
            window.draw(shop);
            window.draw(Currency);
            window.draw(NoCurrency);
            window.draw(*ReturnBtn);
            window.draw(*ReturnTxt);
            window.draw(*HealBtn);
            window.draw(*HealTxt);
            window.draw(*BuffBtn);
            window.draw(*BuffTxt);
            window.draw(*ManaBtn);
            window.draw(*ManaTxt);
            window.draw(*ShieldBtn);
            window.draw(*ShieldTxt);
            if (showPopup && popupClock.getElapsedTime() > popupDuration)
            {
                showPopup = false;
            }
            if (showPopup)
                window.draw(popupText);
            window.display();
        }
    DeleteData:
        delete ShieldBtn;
        delete ShieldTxt;
        delete ManaBtn;
        delete ReturnBtn;
        delete ReturnTxt;
        delete ManaTxt;
        delete HealBtn;
        delete HealTxt;
        delete BuffBtn;
        delete BuffTxt;
    }
    void removeGuild(RenderWindow &window, Font &font, Player &user, Text &popupText, Clock &popupClock, bool &showPopup)
    {
        string RemoveGuildID = "";
        Time popupDuration = seconds(2);
        RectangleShape *ReturnBtn = nullptr;
        Text *ReturnTxt = nullptr;
        RectangleShape *IdBox = nullptr;
        while (window.isOpen())
        {
            window.clear();
            Texture GuildBG;
            if (!GuildBG.loadFromFile("GuildWallpaper.png"))
            {
                cout << "Image load Failure";
                return;
            }
            Sprite guildBG(GuildBG);
            Text Label("Guild ID : ", font, 24);
            Label.setPosition(12 * CELL_SIZE, 4.5 * CELL_SIZE);
            Text Text(RemoveGuildID, font, 24);
            Text.setFillColor(Color::Black);
            Text.setPosition(12 * CELL_SIZE, 5.5 * CELL_SIZE);
            createButtonWithText(ReturnBtn, ReturnTxt, font, "Esc", 0.2, 0.5, 80, Color(30, 30, 30), Color::Black);
            CreateButton(IdBox, 5.5, 12, 200, Color::White, Color::Black);
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
                if (event.type == Event::KeyPressed)
                {
                    if (event.key.code == Keyboard::Escape)
                    {
                        clickSound.play();
                        goto DeleteData;
                    }
                    if (event.key.code == Keyboard::BackSpace)
                    {
                        if (RemoveGuildID.length() > 0)
                            RemoveGuildID.pop_back();
                    }
                    if (event.key.code == Keyboard::Enter)
                    {
                        clickSound.play();
                        bool Exists = false;
                        int index;
                        for (int i = 0; i < user.getNoOfGuilds(); i++)
                        {
                            if (RemoveGuildID == user.GetGuild(i)->getId())
                            {
                                Exists = true;
                                index = i;
                            }
                        }
                        if (Exists == false)
                        {
                            popupText.setString("No Guild Exist with Given ID!");
                            popupClock.restart();
                            showPopup = true;
                        }
                        else if (Exists == true)
                        {
                            user.RemoveGuild(index);
                            RemoveGuildID = "";
                            popupText.setString("Guild Removed!");
                            popupClock.restart();
                            showPopup = true;
                            goto DeleteData;
                        }
                    }
                }
                if (event.type == Event::TextEntered)
                {

                    if (event.text.unicode < 128 && event.text.unicode != 8 && event.text.unicode != 13)
                        RemoveGuildID += static_cast<char>(event.text.unicode);
                }
            }
            window.draw(guildBG);
            window.draw(*IdBox);
            window.draw(*ReturnBtn);
            window.draw(*ReturnTxt);
            window.draw(Label);
            window.draw(Text);
            if (showPopup && popupClock.getElapsedTime() > popupDuration)
            {
                showPopup = false;
            }
            if (showPopup)
                window.draw(popupText);
            window.display();
        }
    DeleteData:
        delete ReturnBtn;
        delete ReturnTxt;
        delete IdBox;
    }
    void Training(RenderWindow &window, Font &font, TrainingCamp &camp, Text &popupText, Dragon &D, Phoenix &P, Unicorn &U, Griffin &G)
    {

        RectangleShape *ReturnBtn = nullptr;
        RectangleShape *PhoenixBtn = nullptr;
        RectangleShape *DragonBtn = nullptr;
        RectangleShape *UnicornBtn = nullptr;
        RectangleShape *GriffinBtn = nullptr;
        Text *ReturnTxt = nullptr;
        Text *PhoenixTxt = nullptr;
        Text *DragonTxt = nullptr;
        Text *UnicornTxt = nullptr;
        Text *GriffinTxt = nullptr;
        while (window.isOpen())
        {
            window.clear();
            Texture GuildBG;
            if (!GuildBG.loadFromFile("GuildWallpaper.png"))
            {
                cout << "Image load Failure";
                return;
            }
            Sprite guildBG(GuildBG);
            createButtonWithText(ReturnBtn, ReturnTxt, font, "Esc", 0.2, 0.5, 80, Color(30, 30, 30), Color::Black);
            createButtonWithText(DragonBtn, DragonTxt, font, "Dragon(D)", 4, 6, 150, Color(30, 30, 30), Color::Black);
            createButtonWithText(PhoenixBtn, PhoenixTxt, font, "Phoenix(P)", 8, 6, 150, Color(30, 30, 30), Color::Black);
            createButtonWithText(UnicornBtn, UnicornTxt, font, "Unicorn(C)", 4, 12, 150, Color(30, 30, 30), Color::Black);
            createButtonWithText(GriffinBtn, GriffinTxt, font, "Griffin(G)", 8, 12, 150, Color(30, 30, 30), Color::Black);
            Text T("Choose Pet For Training", font, 24);
            T.setPosition(9 * CELL_SIZE, 1 * CELL_SIZE);
            window.draw(guildBG);
            window.draw(*PhoenixBtn);
            window.draw(*PhoenixTxt);
            window.draw(*UnicornBtn);
            window.draw(*UnicornTxt);
            window.draw(*DragonBtn);
            window.draw(*DragonTxt);
            window.draw(*GriffinBtn);
            window.draw(*GriffinTxt);
            window.draw(T);
            window.draw(*ReturnBtn);
            window.draw(*ReturnTxt);
            window.display();
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
                if (event.type == Event::KeyPressed)
                {
                    if (event.key.code == Keyboard::Escape)
                    {
                        clickSound.play();
                        goto DeleteData;
                    }
                    if (event.key.code == Keyboard::P)
                    {
                        clickSound.play();
                        camp.TrainPet(window, &P, 1, popupText);
                        goto DeleteData;
                    }
                    if (event.key.code == Keyboard::D)
                    {
                        clickSound.play();
                        camp.TrainPet(window, &D, 2, popupText);
                        goto DeleteData;
                    }
                    if (event.key.code == Keyboard::G)
                    {
                        clickSound.play();
                        camp.TrainPet(window, &G, 3, popupText);
                        goto DeleteData;
                    }
                    if (event.key.code == Keyboard::C)
                    {
                        clickSound.play();
                        camp.TrainPet(window, &U, 4, popupText);
                        goto DeleteData;
                    }
                }
            }
        }
    DeleteData:
        delete ReturnBtn;
        delete PhoenixBtn;
        delete DragonBtn;
        delete UnicornBtn;
        delete GriffinBtn;
        delete ReturnTxt;
        delete PhoenixTxt;
        delete DragonTxt;
        delete UnicornTxt;
        delete GriffinTxt;
    }
    void askGuildRolls(RenderWindow &window, Font &font, Player &user, Text &popupText, Clock &popupClock, bool &showPopup, Dragon &D, Phoenix &P, Unicorn &U, Griffin &G, Guild *tempGuild)
    {
        // ask guild roles from user( ensure no pet is assigned more than one role )
        int count = 1;
        bool phoenix, griffin, unicorn, dragon;
        phoenix = false;
        unicorn = false;
        dragon = false;
        griffin = false;
        RectangleShape *PhoenixBtn = nullptr;
        RectangleShape *DragonBtn = nullptr;
        RectangleShape *UnicornBtn = nullptr;
        RectangleShape *GriffinBtn = nullptr;
        Text *PhoenixTxt = nullptr;
        Text *DragonTxt = nullptr;
        Text *UnicornTxt = nullptr;
        Text *GriffinTxt = nullptr;
        while (window.isOpen())
        {
            window.clear();
            Texture GuildBG;
            if (!GuildBG.loadFromFile("GuildWallpaper.png"))
            {
                cout << "Image load Failure";
                return;
            }
            Text t1("Choose ur Tank", font, 24);
            Text t2("Choose ur Healer", font, 24);
            Text t3("Choose ur DamageDealer", font, 24);
            Text t4("Choose ur Striker", font, 24);
            t1.setPosition(9 * CELL_SIZE, 1 * CELL_SIZE);
            t2.setPosition(9 * CELL_SIZE, 1 * CELL_SIZE);
            t3.setPosition(9 * CELL_SIZE, 1 * CELL_SIZE);
            t4.setPosition(9 * CELL_SIZE, 1 * CELL_SIZE);
            Sprite guildBG(GuildBG);
            createButtonWithText(DragonBtn, DragonTxt, font, "Dragon(D)", 4, 6, 150, Color(30, 30, 30), Color::Black);
            createButtonWithText(PhoenixBtn, PhoenixTxt, font, "Phoenix(P)", 8, 6, 150, Color(30, 30, 30), Color::Black);
            createButtonWithText(UnicornBtn, UnicornTxt, font, "Unicorn(U)", 4, 12, 150, Color(30, 30, 30), Color::Black);
            createButtonWithText(GriffinBtn, GriffinTxt, font, "Griffin(G)", 8, 12, 150, Color(30, 30, 30), Color::Black);
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
                if (event.type == Event::KeyPressed)
                {
                    if (event.key.code == Keyboard::P)
                    {
                        if (count == 1 && phoenix == false)
                        {
                            clickSound.play();
                            tempGuild->setTank(&P);
                            phoenix = true;
                            count++;
                        }
                        if (count == 2 && phoenix == false)
                        {
                            clickSound.play();
                            tempGuild->setHealer(&P);
                            phoenix = true;
                            count++;
                        }
                        if (count == 3 && phoenix == false)
                        {
                            clickSound.play();
                            tempGuild->setDamageDealer(&P);
                            phoenix = true;
                            count++;
                        }
                        if (count == 4 && phoenix == false)
                        {
                            clickSound.play();
                            tempGuild->setStriker(&P);
                            popupClock.restart();
                            popupText.setString("Guild Added");
                            showPopup = true;
                            phoenix = false;
                            griffin = false;
                            dragon = false;
                            unicorn = false;
                            user.setNoOfGuilds(user.getNoOfGuilds() + 1);
                            goto DeleteData;
                        }
                    }
                    if (event.key.code == Keyboard::U)
                    {
                        if (count == 1 && unicorn == false)
                        {
                            clickSound.play();
                            tempGuild->setTank(&U);
                            unicorn = true;
                            count++;
                        }
                        if (count == 2 && unicorn == false)
                        {
                            clickSound.play();
                            tempGuild->setHealer(&U);
                            unicorn = true;
                            count++;
                        }
                        if (count == 3 && unicorn == false)
                        {
                            clickSound.play();
                            tempGuild->setDamageDealer(&U);
                            unicorn = true;
                            count++;
                        }
                        if (count == 4 && unicorn == false)
                        {
                            clickSound.play();
                            tempGuild->setStriker(&U);
                            popupClock.restart();
                            popupText.setString("Guild Added");
                            showPopup = true;
                            phoenix = false;
                            griffin = false;
                            dragon = false;
                            unicorn = false;
                            user.setNoOfGuilds(user.getNoOfGuilds() + 1);
                            goto DeleteData;
                        }
                    }
                    if (event.key.code == Keyboard::G)
                    {
                        if (count == 1 && griffin == false)
                        {
                            clickSound.play();
                            tempGuild->setTank(&G);
                            griffin = true;
                            count++;
                        }
                        if (count == 2 && griffin == false)
                        {
                            clickSound.play();
                            tempGuild->setHealer(&G);
                            griffin = true;
                            count++;
                        }
                        if (count == 3 && griffin == false)
                        {
                            clickSound.play();
                            tempGuild->setDamageDealer(&G);
                            griffin = true;
                            count++;
                        }
                        if (count == 4 && griffin == false)
                        {
                            clickSound.play();
                            tempGuild->setStriker(&G);
                            popupClock.restart();
                            popupText.setString("Guild Added");
                            showPopup = true;
                            phoenix = false;
                            griffin = false;
                            dragon = false;
                            unicorn = false;
                            user.setNoOfGuilds(user.getNoOfGuilds() + 1);
                            goto DeleteData;
                        }
                    }
                    if (event.key.code == Keyboard::D)
                    {
                        if (count == 1 && dragon == false)
                        {
                            clickSound.play();
                            tempGuild->setTank(&D);
                            dragon = true;
                            count++;
                        }
                        if (count == 2 && dragon == false)
                        {
                            clickSound.play();
                            tempGuild->setHealer(&D);
                            dragon = true;
                            count++;
                        }
                        if (count == 3 && dragon == false)
                        {
                            clickSound.play();
                            tempGuild->setDamageDealer(&D);
                            dragon = true;
                            count++;
                        }
                        if (count == 4 && dragon == false)
                        {
                            clickSound.play();
                            tempGuild->setStriker(&D);
                            popupClock.restart();
                            popupText.setString("Guild Added");
                            showPopup = true;
                            phoenix = false;
                            griffin = false;
                            dragon = false;
                            unicorn = false;
                            user.setNoOfGuilds(user.getNoOfGuilds() + 1);
                            goto DeleteData;
                        }
                    }
                }
            }
            window.draw(guildBG);
            window.draw(*PhoenixBtn);
            window.draw(*PhoenixTxt);
            window.draw(*UnicornBtn);
            window.draw(*UnicornTxt);
            window.draw(*DragonBtn);
            window.draw(*DragonTxt);
            window.draw(*GriffinBtn);
            window.draw(*GriffinTxt);
            if (count == 1)
                window.draw(t1);
            if (count == 2)
                window.draw(t2);
            if (count == 3)
                window.draw(t3);
            if (count == 4)
                window.draw(t4);
            window.display();
        }
    DeleteData:
        delete PhoenixBtn;
        delete DragonBtn;
        delete UnicornBtn;
        delete GriffinBtn;
        delete PhoenixTxt;
        delete DragonTxt;
        delete UnicornTxt;
        delete GriffinTxt;
    }

    void AddGuild(RenderWindow &window, Font &font, Player &user, Text &popupText, Clock &popupClock, bool &showPopup, Dragon &D, Phoenix &P, Unicorn &U, Griffin &G)
    {
        // ask the name and id  of the new guild to be added
        string guildName = "", guildID = "";
        bool typingName = true;
        Guild *tempGuild = nullptr;
        RectangleShape *ReturnBtn = nullptr;
        Text *ReturnTxt = nullptr;
        RectangleShape *NameBox = nullptr;
        RectangleShape *IdBox = nullptr;
        Time popupDuration = seconds(2);
        while (window.isOpen())
        {
            window.clear();
            Texture GuildBG;
            if (!GuildBG.loadFromFile("GuildWallpaper.png"))
            {
                cout << "Image load Failure";
                return;
            }
            Sprite guildBG(GuildBG);

            createButtonWithText(ReturnBtn, ReturnTxt, font, "Esc", 0.2, 0.5, 80, Color(30, 30, 30), Color::Black);
            CreateButton(NameBox, 3.5, 12, 200, Color::White, Color::Black);
            CreateButton(IdBox, 6.5, 12, 200, Color::White, Color::Black);

            Text Toggle("Use Arrows To shift ", font, 24);
            Toggle.setPosition(7 * CELL_SIZE, 1 * CELL_SIZE);
            Text NameLabel("Guild Name : ", font, 24);
            NameLabel.setPosition(12 * CELL_SIZE, 2.5 * CELL_SIZE);
            Text NameText(guildName, font, 24);
            NameText.setFillColor(Color::Black);
            NameText.setPosition(12 * CELL_SIZE, 3.5 * CELL_SIZE);
            Text IdLabel("Guild ID : ", font, 24);
            IdLabel.setPosition(12 * CELL_SIZE, 5.5 * CELL_SIZE);
            Text IdText(guildID, font, 24);
            IdText.setPosition(12 * CELL_SIZE, 6.5 * CELL_SIZE);
            IdText.setFillColor(Color::Black);

            // check whether if user is typing name or id of guild
            if (typingName)
                NameBox->setOutlineColor(Color::Green);
            else
                NameBox->setOutlineColor(Color::Black);

            if (!typingName)
                IdBox->setOutlineColor(Color::Green);
            else
                IdBox->setOutlineColor(Color::Black);
            window.draw(guildBG);
            window.draw(*NameBox);
            window.draw(*IdBox);

            window.draw(NameLabel);
            window.draw(IdLabel);
            window.draw(*ReturnBtn);
            window.draw(*ReturnTxt);
            window.draw(NameText);
            window.draw(Toggle);
            window.draw(IdText);
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
                if (event.type == Event::KeyPressed)
                {
                    if (event.key.code == Keyboard::Escape)
                    {
                        clickSound.play();
                        goto DeleteData;
                    }
                    if (event.key.code == Keyboard::Up || event.key.code == Keyboard::Down)
                    {
                        clickSound.play();
                        typingName = !typingName; // switch between name and ID input
                    }
                    if (event.key.code == Keyboard::BackSpace)
                    {
                        if (typingName)
                        {
                            if (guildName.length() > 0)
                            {
                                guildName.pop_back();
                            }
                        }
                        else
                        {
                            if (guildID.length() > 0)
                            {
                                guildID.pop_back();
                            }
                        }
                    }
                    if (event.key.code == Keyboard::Enter)
                    {
                        clickSound.play();
                        // check whether if guild with same id exists or not
                        if (guildID != "" && guildName != "" && guildID[0] != 9 && guildName[0] != 9)
                        {
                            bool isDuplicate = false;
                            for (int i = 0; i < user.getNoOfGuilds(); i++)
                            {
                                if (guildID == user.GetGuild(i)->getId())
                                    isDuplicate = true;
                            }
                            if (isDuplicate == true)
                            {
                                popupText.setString("Guild with Same ID Already Exists");
                                popupClock.restart();
                                showPopup = true;
                            }
                            else if (isDuplicate == false)
                            {
                                tempGuild = user.GetGuild(user.getNoOfGuilds());
                                tempGuild->setID(guildID);
                                tempGuild->setName(guildName);
                                guildID = "";
                                guildName = "";
                                askGuildRolls(window, font, user, popupText, popupClock, showPopup, D, P, U, G, tempGuild);
                                goto DeleteData;
                            }
                        }
                    }
                }
                if (event.type == Event::TextEntered)
                {
                    // adding user entered text into variables ensuring invalid inputs
                    if (event.text.unicode < 128 && event.text.unicode != 8 && event.text.unicode != 13 && event.text.unicode != 45 && event.text.unicode != 9)
                        if (typingName)
                            guildName += static_cast<char>(event.text.unicode);
                        else
                            guildID += static_cast<char>(event.text.unicode);
                }
            }
            if (showPopup && popupClock.getElapsedTime() > popupDuration)
            {
                showPopup = false;
            }
            if (showPopup)
                window.draw(popupText);
            window.display();
        }
    DeleteData:
        delete ReturnBtn;
        delete ReturnTxt;
        delete NameBox;
        delete IdBox;
    }

    string getPetNameFromID(int id)
    {
        if (id == 1)
            return "Dragon";
        if (id == 2)
            return "Phoenix";
        if (id == 3)
            return "Unicorn";
        if (id == 4)
            return "Griffin";
        return "";
    }
    void ShowLeaderboard(RenderWindow &window, Font &font, Player &user)
    {
        RectangleShape *guildIDbtn = nullptr;
        RectangleShape *guildNamebtn = nullptr;
        RectangleShape *healerbtn = nullptr;
        RectangleShape *tankbtn = nullptr;
        RectangleShape *dealerbtn = nullptr;
        RectangleShape *strikerbtn = nullptr;
        RectangleShape *scorebtn = nullptr;
        RectangleShape *Rankbtn = nullptr;

        Text *guildIDtxt = nullptr;
        Text *guildNametxt = nullptr;
        Text *healertxt = nullptr;
        Text *tanktxt = nullptr;
        Text *dealertxt = nullptr;
        Text *strikertxt = nullptr;
        Text *scoretxt = nullptr;
        Text *Ranktxt = nullptr;
        createButtonWithText(Rankbtn, Ranktxt, font, "Rank", 1, 0.5, 130, Color(50, 50, 50), Color::Black);
        createButtonWithText(guildIDbtn, guildIDtxt, font, "Guild ID", 1, 3, 130, Color(50, 50, 50), Color::Black);
        createButtonWithText(guildNamebtn, guildNametxt, font, "Guild Name", 1, 5.4, 140, Color(50, 50, 50), Color::Black);
        createButtonWithText(healerbtn, healertxt, font, "Healer", 1, 8, 130, Color(50, 50, 50), Color::Black);
        createButtonWithText(tankbtn, tanktxt, font, "Tank", 1, 10.5, 130, Color(50, 50, 50), Color::Black);
        createButtonWithText(dealerbtn, dealertxt, font, "Dealer", 1, 13, 130, Color(50, 50, 50), Color::Black);
        createButtonWithText(strikerbtn, strikertxt, font, "Striker", 1, 15.5, 130, Color(50, 50, 50), Color::Black);
        createButtonWithText(scorebtn, scoretxt, font, "Score", 1, 18, 100, Color(50, 50, 50), Color::Black);

        user.SortGuilds();
        Texture BG;
        if (!BG.loadFromFile("BattleBG.png"))
        {
            cout << "Image load Failure";
            exit(0);
        }
        Sprite bg(BG);
        Text Rank[5];
        Text guildIDs[5];
        Text guildNames[5];
        Text healerTexts[5];
        Text tankTexts[5];
        Text dealerTexts[5];
        Text strikerTexts[5];
        Text scores[5];
        user.SortGuilds();
        for (int i = 0; i < user.getNoOfGuilds(); ++i)
        {
            Guild *g = user.GetGuild(i);

            Rank[i].setString(to_string(i + 1));
            Rank[i].setFont(font);
            Rank[i].setPosition(Rankbtn->getPosition().x, Rankbtn->getPosition().y + 50 + i * 60);

            guildIDs[i].setFont(font);
            guildIDs[i].setString(g->getId());
            guildIDs[i].setPosition(guildIDbtn->getPosition().x, guildIDbtn->getPosition().y + 50 + i * 60);

            guildNames[i].setFont(font);
            guildNames[i].setString(g->getName());
            guildNames[i].setPosition(guildNamebtn->getPosition().x, guildNamebtn->getPosition().y + 50 + i * 60);

            scores[i].setFont(font);
            scores[i].setString(to_string(g->getGuildScore()));
            scores[i].setPosition(scorebtn->getPosition().x, scorebtn->getPosition().y + 50 + i * 60);

            healerTexts[i].setFont(font);
            healerTexts[i].setString(getPetNameFromID(g->getHealer()->getPetID()));
            healerTexts[i].setPosition(healerbtn->getPosition().x, healerbtn->getPosition().y + 50 + i * 60);

            tankTexts[i].setFont(font);
            tankTexts[i].setString(getPetNameFromID(g->getTank()->getPetID()));
            tankTexts[i].setPosition(tankbtn->getPosition().x, tankbtn->getPosition().y + 50 + i * 60);

            dealerTexts[i].setFont(font);
            dealerTexts[i].setString(getPetNameFromID(g->getDamageDealer()->getPetID()));
            dealerTexts[i].setPosition(dealerbtn->getPosition().x, dealerbtn->getPosition().y + 50 + i * 60);

            strikerTexts[i].setFont(font);
            strikerTexts[i].setString(getPetNameFromID(g->getStriker()->getPetID()));
            strikerTexts[i].setPosition(strikerbtn->getPosition().x, strikerbtn->getPosition().y + 50 + i * 60);
        }
        while (window.isOpen())
        {
            window.clear();
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.key.code == Keyboard::Enter)
                {
                    clickSound.play();
                    goto DeleteData;
                }
            }

            window.draw(bg);
            window.draw(*guildIDbtn);
            window.draw(*guildIDtxt);
            window.draw(*guildNamebtn);
            window.draw(*guildNametxt);
            window.draw(*healerbtn);
            window.draw(*healertxt);
            window.draw(*tankbtn);
            window.draw(*tanktxt);
            window.draw(*dealerbtn);
            window.draw(*dealertxt);
            window.draw(*strikerbtn);
            window.draw(*strikertxt);
            window.draw(*scorebtn);
            window.draw(*scoretxt);
            window.draw(*Rankbtn);
            window.draw(*Ranktxt);
            for (int i = 0; i < user.getNoOfGuilds(); ++i)
            {
                window.draw(Rank[i]);
                window.draw(guildIDs[i]);
                window.draw(guildNames[i]);
                window.draw(scores[i]);
                window.draw(healerTexts[i]);
                window.draw(tankTexts[i]);
                window.draw(dealerTexts[i]);
                window.draw(strikerTexts[i]);
            }
            window.display();
        }
    DeleteData:
        delete guildIDbtn;
        delete guildIDtxt;
        delete guildNamebtn;
        delete guildNametxt;
        delete healerbtn;
        delete healertxt;
        delete tankbtn;
        delete tanktxt;
        delete dealerbtn;
        delete dealertxt;
        delete strikerbtn;
        delete strikertxt;
        delete scorebtn;
        delete scoretxt;
    }

    // Ask guild operation to perform
    void GuildManage(RenderWindow &window, Font &font, Player &user, Text &popupText, Clock &popupClock, bool showPopup, Dragon &D, Phoenix &P, Unicorn &U, Griffin &G)
    {
        Time popupDuration = seconds(2);
        RectangleShape *ReturnBtn = nullptr;
        Text *ReturnTxt = nullptr;
        RectangleShape *CreateGuildbtn = nullptr;
        Text *CreateGuildTxt = nullptr;
        RectangleShape *RemoveGuildbtn = nullptr;
        Text *RemoveGuildTxt = nullptr;
        RectangleShape *Leaderboardbtn = nullptr;
        Text *LeaderboardTxt = nullptr;
        while (window.isOpen())
        {
            window.clear();
            Texture GuildBG;
            if (!GuildBG.loadFromFile("GuildWallpaper.png"))
            {
                cout << "Image load Failure";
                return;
            }
            Sprite guildBG(GuildBG);

            createButtonWithText(CreateGuildbtn, CreateGuildTxt, font, "Add Guild(A)", 4, 12, 200, Color(30, 30, 30), Color::Black);
            createButtonWithText(RemoveGuildbtn, RemoveGuildTxt, font, "Remove Guild(R)", 6, 12, 200, Color(30, 30, 30), Color::Black);
            createButtonWithText(ReturnBtn, ReturnTxt, font, "Esc", 0.2, 0.5, 80, Color(30, 30, 30), Color::Black);
            createButtonWithText(Leaderboardbtn, LeaderboardTxt, font, "Leaderboard(L)", 8, 12, 200, Color(30, 30, 30), Color::Black);
            window.draw(guildBG);
            window.draw(*CreateGuildbtn);
            window.draw(*CreateGuildTxt);
            window.draw(*RemoveGuildbtn);
            window.draw(*RemoveGuildTxt);
            window.draw(*Leaderboardbtn);
            window.draw(*LeaderboardTxt);
            window.draw(*ReturnBtn);
            window.draw(*ReturnTxt);
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
                if (event.type == Event::KeyPressed)
                {
                    if (event.key.code == Keyboard::Escape)
                    {
                        clickSound.play();
                        goto DeleteData;
                    }
                    if (event.key.code == Keyboard::A)
                    {
                        clickSound.play();
                        if (user.getNoOfGuilds() == user.getMaxGuilds())
                        {
                            popupText.setString("Max No of Guilds Reached ");
                            popupClock.restart();
                            showPopup = true;
                        }
                        else
                        {
                            AddGuild(window, font, user, popupText, popupClock, showPopup, D, P, U, G);
                        }
                    }
                    if (event.key.code == Keyboard::R)
                    {
                        clickSound.play();
                        removeGuild(window, font, user, popupText, popupClock, showPopup);
                    }
                    if (event.key.code == Keyboard::L)
                    {
                        clickSound.play();
                        ShowLeaderboard(window, font, user);
                    }
                }
            }
            if (showPopup && popupClock.getElapsedTime() > popupDuration)
            {
                showPopup = false;
            }
            if (showPopup)
                window.draw(popupText);
            window.display();
        }
    DeleteData:
        delete ReturnBtn;
        delete ReturnTxt;
        delete CreateGuildbtn;
        delete CreateGuildTxt;
        delete RemoveGuildbtn;
        delete RemoveGuildTxt;
    }
    // ask whether if new game or load game
    bool askNewGame(RenderWindow &window)
    {
        Font font;
        Texture MainMenu;
        if (!MainMenu.loadFromFile("MainMenu.png"))
        {
            cout << "Image load Failure";
            exit(0);
        }
        Sprite BackgroundMainMenu(MainMenu);

        if (!font.loadFromFile("OpenSans-VariableFont_wdth,wght.ttf"))
        {
            cout << "Error loading font!" << endl;
            exit(0);
        }
        RectangleShape *NewGameBtn = nullptr;
        Text *NewGametxt = nullptr;
        RectangleShape *LoadGameBtn = nullptr;
        Text *LoadGameTxt = nullptr;
        createButtonWithText(NewGameBtn, NewGametxt, font, "New Game(N)", 5, 12, 200, Color(30, 30, 30), Color::Black);
        createButtonWithText(LoadGameBtn, LoadGameTxt, font, "Load Game(L)", 6, 12, 200, Color(30, 30, 30), Color::Black);
        while (window.isOpen())
        {
            window.draw(BackgroundMainMenu);
            window.draw(*NewGameBtn);
            window.draw(*NewGametxt);
            window.draw(*LoadGameBtn);
            window.draw(*LoadGameTxt);
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
                if (event.type == Event::KeyPressed)
                {
                    if (event.key.code == Keyboard::N)
                    {
                        clickSound.play();
                        delete NewGameBtn;
                        delete NewGametxt;
                        delete LoadGameBtn;
                        delete LoadGameTxt;
                        return true;
                    }
                    if (event.key.code == Keyboard::L)
                    {
                        clickSound.play();
                        delete NewGameBtn;
                        delete NewGametxt;
                        delete LoadGameBtn;
                        delete LoadGameTxt;
                        return false;
                    }
                }
            }
            window.display();
        }
        return true;
    }

    // main loop and handles the game
    void StartGame()
    {
        srand(time(0));
        if (!clickBuffer.loadFromFile("ButtonClickSound.wav"))
        {
            cout << "Failed to load sound\n";
            exit(1);
        }
        clickSound.setBuffer(clickBuffer);
        bool isMainMenu = true;
        bool isTrainingCamp = false;
        bool isBattle = false;
        bool isShop = false;
        bool isUpgradePet = false;
        bool isguildManage = false;
        bool showPopup = false;

        const int wallWidth = 20;
        const int wallHeight = 100;
        const int stoneWidth = 60;
        const int stoneHeight = 60;
        int posX[4];
        int posY[4];
        int width[4];
        int height[4];

        for (int i = 0; i < 4; i++)
        {
            if (i < 2)
            {
                width[i] = wallWidth;
                height[i] = wallHeight;
            }
            else
            {
                width[i] = stoneWidth;
                height[i] = stoneHeight;
            }

            bool validPosition = false;
            while (validPosition == false)
            {
                posX[i] = rand() % (X_RESOLUTION - 800) + 400;
                posY[i] = rand() % Y_RESOLUTION;

                validPosition = true;
                for (int j = 0; j < i; j++)
                {
                    bool noOverlapX;
                    bool noOverlapY;
                    if (posX[i] + width[i] <= posX[j] || posX[j] + width[j] <= posX[i])
                        noOverlapX = true;
                    else
                        noOverlapX = false;
                    if (posY[i] + height[i] <= posY[j] || posY[j] + height[j] <= posY[i])
                        noOverlapY = true;
                    else
                        noOverlapY = false;
                    if (noOverlapX == false && noOverlapY == false)
                    {
                        validPosition = false;
                        break;
                    }
                }
            }
        }

        Wall w1(posX[0], posY[0]);
        Wall w2(posX[1], posY[1]);
        Stone s1(posX[2], posY[2]);
        Stone s2(posX[3], posY[3]);
        oneVone Battle1(w1, w2, s1, s2);
        twoVtwo Battle2(w1, w2, s1, s2);
        guildVguild BattleG(w1, w2, s1, s2);
        Shop items(300, 200, 400, 100);
        Font font;

        Dragon D;
        Phoenix P;
        Unicorn U;
        Griffin G;
        Player user(&D, &P, &U, &G);
        RenderWindow window(sf::VideoMode(X_RESOLUTION, Y_RESOLUTION), "Magical Pets Kingdom");
        bool isNewGame = askNewGame(window);
        ifstream inFile("data.txt");
        if (inFile && !isNewGame)
        {
            if (inFile.peek() == ifstream::traits_type::eof())
            goto MakeData;
            string petName[4];
            int petSpeed[4], petID[4], petHealth[4], petAttack[4], petDefense[4];
            int petLevel[4], petTrainingPoints[4], petMove1[4], petMove2[4];
            int userID, userCurrency, healPotion, manaPotion, buffPotion, Shields, NoGuilds;
            string username, line;

            getline(inFile, line);
            stringstream sStream(line);
            string value;

            for (int i = 0; i < 4; i++)
            {
                getline(sStream, petName[i], ',');
                getline(sStream, value, ',');
                petSpeed[i] = stoi(value);
                getline(sStream, value, ',');
                petID[i] = stoi(value);
                getline(sStream, value, ',');
                petHealth[i] = stoi(value);
                getline(sStream, value, ',');
                petAttack[i] = stoi(value);
                getline(sStream, value, ',');
                petDefense[i] = stoi(value);
                getline(sStream, value, ',');
                petLevel[i] = stoi(value);
                getline(sStream, value, ',');
                petTrainingPoints[i] = stoi(value);
                getline(sStream, value, ',');
                petMove1[i] = stoi(value);
                getline(sStream, value, ',');
                petMove2[i] = stoi(value);
            }

            getline(sStream, value, ',');
            userID = stoi(value);
            getline(sStream, username, ',');
            getline(sStream, value, ',');
            userCurrency = stoi(value);
            getline(sStream, value, ',');
            healPotion = stoi(value);
            getline(sStream, value, ',');
            manaPotion = stoi(value);
            getline(sStream, value, ',');
            buffPotion = stoi(value);
            getline(sStream, value, ',');
            Shields = stoi(value);
            getline(sStream, value, ',');
            NoGuilds = stoi(value);

            D = Dragon(petName[0], petSpeed[0], petID[0], petHealth[0], petAttack[0], petDefense[0], petMove1[0], petMove2[0]);
            D.setTrainingPoints(petTrainingPoints[0]);
            D.setCurrentLevel(petLevel[0]);

            P = Phoenix(petName[1], petSpeed[1], petID[1], petHealth[1], petAttack[1], petDefense[1], petMove1[1]);
            P.setTrainingPoints(petTrainingPoints[1]);
            P.setCurrentLevel(petLevel[1]);

            U = Unicorn(petName[2], petSpeed[2], petID[2], petHealth[2], petAttack[2], petDefense[2], petMove1[2], petMove2[2]);
            U.setTrainingPoints(petTrainingPoints[2]);
            U.setCurrentLevel(petLevel[2]);

            G = Griffin(petName[3], petSpeed[3], petID[3], petHealth[3], petAttack[3], petDefense[3], petMove1[3], petMove2[3]);
            G.setTrainingPoints(petTrainingPoints[3]);
            G.setCurrentLevel(petLevel[3]);

            user.setCurrency(userCurrency);
            user.setID(userID);
            user.setName(username);
            user.setNoOfHealingPotions(healPotion);
            user.setNoOfManaPotions(manaPotion);
            user.setNoOfBuffItems(buffPotion);
            user.setNoOfShields(Shields);
            user.setNoOfGuilds(NoGuilds);

            for (int i = 0; i < user.getNoOfGuilds(); i++)
            {
                string gid, gname;
                int healerID, dealerID, tankID, strikerID;
                int guildPoints;
                getline(sStream, gid, ',');
                getline(sStream, gname, ',');
                getline(sStream, value, ',');
                healerID = stoi(value);
                getline(sStream, value, ',');
                dealerID = stoi(value);
                getline(sStream, value, ',');
                tankID = stoi(value);
                getline(sStream, value, ',');
                strikerID = stoi(value);
                getline(sStream, value, ',');
                guildPoints = stoi(value);

                user.GetGuild(i)->setGuildScore(guildPoints);
                user.GetGuild(i)->setID(gid);
                user.GetGuild(i)->setName(gname);

                if (healerID == 1)
                    user.GetGuild(i)->setHealer(&D);
                else if (healerID == 2)
                    user.GetGuild(i)->setHealer(&P);
                else if (healerID == 3)
                    user.GetGuild(i)->setHealer(&U);
                else if (healerID == 4)
                    user.GetGuild(i)->setHealer(&G);

                if (dealerID == 1)
                    user.GetGuild(i)->setDamageDealer(&D);
                else if (dealerID == 2)
                    user.GetGuild(i)->setDamageDealer(&P);
                else if (dealerID == 3)
                    user.GetGuild(i)->setDamageDealer(&U);
                else if (dealerID == 4)
                    user.GetGuild(i)->setDamageDealer(&G);

                if (tankID == 1)
                    user.GetGuild(i)->setTank(&D);
                else if (tankID == 2)
                    user.GetGuild(i)->setTank(&P);
                else if (tankID == 3)
                    user.GetGuild(i)->setTank(&U);
                else if (tankID == 4)
                    user.GetGuild(i)->setTank(&G);

                if (strikerID == 1)
                    user.GetGuild(i)->setStriker(&D);
                else if (strikerID == 2)
                    user.GetGuild(i)->setStriker(&P);
                else if (strikerID == 3)
                    user.GetGuild(i)->setStriker(&U);
                else if (strikerID == 4)
                    user.GetGuild(i)->setStriker(&G);
            }
            inFile.close();
        }
        else
        {
            MakeData:
            D = Dragon("Dragon", 15, 1, 800, 80, 10, 300, 2);
            P = Phoenix("Phoenix", 10, 2, 500, 50, 15, 200);
            U = Unicorn("Unicorn", 20, 3, 400, 60, 10, 5, 20);
            G = Griffin("Griffin", 15, 4, 500, 50, 15, 150, 3);
            user.setName("Bilal");
            user.setID(3166);
        }
        RectangleShape *ReturnBtn = nullptr;
        Text *ReturnTxt = nullptr;
        RectangleShape *CreateGuildbtn = nullptr;
        Text *CreateGuildTxt = nullptr;
        RectangleShape *RemoveGuildbtn = nullptr;
        Text *RemoveGuildTxt = nullptr;
        window.setFramerateLimit(60);
        TrainingCamp camp;
        Text popupText;
        popupText.setFont(font);
        popupText.setCharacterSize(28);
        popupText.setFillColor(Color(162, 162, 162));
        popupText.setStyle(Text::Bold);
        popupText.setPosition(X_RESOLUTION / 2.5, Y_RESOLUTION / 3);
        Clock popupClock;
        Time popupDuration = seconds(2);
        Music bgMusic;
        if (!bgMusic.openFromFile("magical_journey.ogg"))
        {
            cout << "Error: Could not load music file!" << endl;
        }
        bgMusic.setVolume(50);
        bgMusic.setLoop(true);
        bgMusic.play();
        RectangleShape *BattleBtn = nullptr;
        Text *BattleTxt = nullptr;
        RectangleShape *GuildBtn = nullptr;
        Text *Guildtxt = nullptr;
        RectangleShape *TrainingCampBtn = nullptr;
        Text *TrainingCampTxt = nullptr;
        RectangleShape *ShopBtn = nullptr;
        Text *ShopTxt = nullptr;
        RectangleShape *UpgradeBtn = nullptr;
        Text *UpgradeTxt = nullptr;
        RectangleShape *ExitBtn = nullptr;
        Text *ExitTxt = nullptr;
        while (window.isOpen())
        {

            if (isMainMenu)
            {
                window.clear();
                Texture MainMenu;
                if (!MainMenu.loadFromFile("MainMenu.png"))
                {
                    cout << "Image load Failure";
                    return;
                }
                Sprite BackgroundMainMenu(MainMenu);

                if (!font.loadFromFile("OpenSans-VariableFont_wdth,wght.ttf"))
                {
                    cout << "Error loading font!" << endl;
                    exit(0);
                }
                createButtonWithText(BattleBtn, BattleTxt, font, "Battle(B)", 5, 12, 200, Color(30, 30, 30), Color::Black);
                createButtonWithText(GuildBtn, Guildtxt, font, "Manage Guild(M)", 6, 12, 200, Color(30, 30, 30), Color::Black);
                createButtonWithText(TrainingCampBtn, TrainingCampTxt, font, "Train Pet(T)", 7, 12, 200, Color(30, 30, 30), Color::Black);
                createButtonWithText(ShopBtn, ShopTxt, font, "Items(I)", 8, 12, 200, Color(30, 30, 30), Color::Black);
                createButtonWithText(UpgradeBtn, UpgradeTxt, font, "Upgrade Pet(U)", 9, 12, 200, Color(30, 30, 30), Color::Black);
                createButtonWithText(ExitBtn, ExitTxt, font, "Exit(E)", 10, 12, 200, Color(30, 30, 30), Color::Black);
                window.draw(BackgroundMainMenu);
                window.draw(*TrainingCampBtn);
                window.draw(*TrainingCampTxt);
                window.draw(*UpgradeBtn);
                window.draw(*UpgradeTxt);
                window.draw(*ShopBtn);
                window.draw(*ShopTxt);
                window.draw(*GuildBtn);
                window.draw(*Guildtxt);
                window.draw(*BattleBtn);
                window.draw(*BattleTxt);
                window.draw(*ExitBtn);
                window.draw(*ExitTxt);
            }
            if (isShop)
            {
                showShop(window, items, font, user, popupText);
                isMainMenu = true;
                isShop = false;
            }
            if (isguildManage)
            {
                GuildManage(window, font, user, popupText, popupClock, showPopup, D, P, U, G);
                isMainMenu = true;
                isguildManage = false;
            }
            if (isBattle)
            {
                AskBattleType(window, user, popupText, font, Battle1, Battle2, BattleG);
                isMainMenu = true;
                isBattle = false;
            }
            if (isUpgradePet)
            {
                UpgradePet(window, user, popupText, font);
                isMainMenu = true;
                isUpgradePet = false;
            }
            if (isTrainingCamp)
            {
                Training(window, font, camp, popupText, D, P, U, G);
                isMainMenu = true;
                isTrainingCamp = false;
            }
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
                if (isMainMenu)
                {
                    if (event.type == Event::KeyPressed)
                    {
                        if (event.key.code == Keyboard::B)
                        {
                            clickSound.play();
                            isMainMenu = false;
                            isBattle = true;
                        }
                        if (event.key.code == Keyboard::U)
                        {
                            clickSound.play();
                            isMainMenu = false;
                            isUpgradePet = true;
                        }
                        if (event.key.code == Keyboard::I)
                        {
                            clickSound.play();
                            isMainMenu = false;
                            isShop = true;
                        }
                        if (event.key.code == Keyboard::T)
                        {
                            clickSound.play();
                            isMainMenu = false;
                            isTrainingCamp = true;
                        }
                        if (event.key.code == Keyboard::M)
                        {
                            clickSound.play();
                            isMainMenu = false;
                            isguildManage = true;
                        }
                        if (event.key.code == Keyboard::E)
                        {
                            goto Savedata;
                        }
                    }
                }
            }
            if (showPopup && popupClock.getElapsedTime() > popupDuration)
            {
                showPopup = false;
            }
            if (showPopup)
                window.draw(popupText);

            window.display();
        }
    Savedata:
        delete BattleBtn;
        delete BattleTxt;
        delete GuildBtn;
        delete Guildtxt;
        delete TrainingCampBtn;
        delete TrainingCampTxt;
        delete ShopBtn;
        delete ShopTxt;
        delete UpgradeBtn;
        delete UpgradeTxt;
        delete ExitBtn;
        delete ExitTxt;
        ofstream File("data.txt");
        if (File.is_open())
        {
            for (int i = 0; i < 4; i++)
            {
                File << user.getPet(i)->getName() << ',';
                File << user.getPet(i)->getSpeed() << ',';
                File << user.getPet(i)->getPetID() << ',';
                File << user.getPet(i)->getHealth() << ',';
                File << user.getPet(i)->getAttackDamage() << ',';
                File << user.getPet(i)->getDefensePower() << ',';
                File << user.getPet(i)->getCurrentLevel() << ',';
                File << user.getPet(i)->getTrainingPoints() << ',';
                File << user.getPet(i)->getMove1() << ',';
                File << user.getPet(i)->getMove2() << ',';
            }
            File << user.getID() << ',';
            File << user.getName() << ',';
            File << user.getCurrency() << ',';
            File << user.getNoOfHealingPotions() << ',';
            File << user.getNoOfManaPotions() << ',';
            File << user.getNoOfBuffItems() << ',';
            File << user.getNoOfShields() << ',';
            File << user.getNoOfGuilds() << ',';
            for (int i = 0; i < user.getNoOfGuilds(); i++)
            {
                File << user.GetGuild(i)->getId() << ',';
                File << user.GetGuild(i)->getName() << ',';
                File << user.GetGuild(i)->getHealer()->getType() << ',';
                File << user.GetGuild(i)->getDamageDealer()->getType() << ',';
                File << user.GetGuild(i)->getTank()->getType() << ',';
                File << user.GetGuild(i)->getStriker()->getType() << ',';
                File << user.GetGuild(i)->getGuildScore() << ',';
            }
            File.close();
        }
    }
};
int main()
{
    Game game;
    game.StartGame();
    return 0;
}