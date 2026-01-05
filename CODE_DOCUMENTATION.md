# Code Documentation - Kingdom Quest

## Table of Contents
1. [Project Overview](#project-overview)
2. [Architecture](#architecture)
3. [Class Structure](#class-structure)
4. [Workflow](#workflow)
5. [Key Components](#key-components)
6. [Data Flow](#data-flow)

## Project Overview

Kingdom Quest is a C++ SFML-based battle arena game that was refactored from a monolithic 6000-line file into a modular, object-oriented architecture. The game features magical pets engaging in strategic battles with multiple game modes and systems.

## Architecture

### High-Level Design

The game follows a **modular architecture** with clear separation of concerns:

`
â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
â”‚           Game (Main Controller)        â”‚
â”‚  - Manages game states and flow         â”‚
â”‚  - Handles user input and rendering     â”‚
â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
               â”‚
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚          â”‚          â”‚
â”Œâ”€â”€â”€â–¼â”€â”€â”€â” â”Œâ”€â”€â”€â–¼â”€â”€â”€â” â”Œâ”€â”€â”€â–¼â”€â”€â”€â”€â”
â”‚Player â”‚ â”‚Battle â”‚ â”‚Systems â”‚
â”‚       â”‚ â”‚Modes  â”‚ â”‚        â”‚
â””â”€â”€â”€â”¬â”€â”€â”€â”˜ â””â”€â”€â”€â”¬â”€â”€â”€â”˜ â””â”€â”€â”€â”¬â”€â”€â”€â”€â”˜
    â”‚         â”‚         â”‚
    â”‚    â”Œâ”€â”€â”€â”€â”´â”€â”€â”€â”€â”    â”‚
    â”‚    â”‚         â”‚    â”‚
â”Œâ”€â”€â”€â–¼â”€â”€â”€â–¼â–¼â”€â”€â” â”Œâ”€â”€â”€â–¼â”€â”€â”€â–¼â–¼â”€â”€â”
â”‚   Pets    â”‚ â”‚  Arena   â”‚
â”‚           â”‚ â”‚          â”‚
â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜ â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
`

### Design Patterns Used

1. **Inheritance**: Pet hierarchy (base Pet class with derived classes)
2. **Polymorphism**: Virtual functions for pet abilities
3. **Composition**: Player contains Pets and Guilds
4. **State Pattern**: Game state management (MainMenu, Battle, Shop, etc.)

## Class Structure

### Core Classes

#### 1. Game Class (include/Game.h, src/Game.cpp)
**Purpose**: Main game controller and state manager

**Key Responsibilities**:
- Initialize game window and resources
- Manage game state transitions
- Handle main game loop
- Coordinate between different game systems

**Key Methods**:
- StartGame(): Entry point, initializes everything and runs main loop
- AskBattleType(): Prompts user to select battle mode
- showShop(): Displays shop interface
- Training(): Handles training camp
- GuildManage(): Manages guild operations
- UpgradePet(): Handles pet upgrades

**State Management**:
`cpp
bool isMainMenu = true;
bool isTrainingCamp = false;
bool isBattle = false;
bool isShop = false;
bool isUpgradePet = false;
bool isguildManage = false;
`

#### 2. Player Class (include/Player.h)
**Purpose**: Represents the player and their resources

**Data Members**:
- Pet** PlayerPets: Array of 4 pets (Dragon, Phoenix, Unicorn, Griffin)
- int Currency: Player's gold/currency
- int NoOfHealingPoints: Healing potions count
- int NoofManaPotions: Mana potions count
- int NoOfBuffitems: Buff items count
- int NoOfShields: Shield items count
- Guild* guilds: Array of up to 5 guilds
- int NoOfGuilds: Current number of guilds

**Key Methods**:
- Getters/Setters for all resources
- GetGuild(int index): Retrieve guild by index
- RemoveGuild(int index): Delete a guild
- SortGuilds(): Sort guilds by score

#### 3. Pet Class (include/Pet.h)
**Purpose**: Base class for all magical pets

**Data Members**:
- std::string name: Pet name
- int health: Current health points
- int Attackdamage: Attack power
- int DefensePower: Defense capability
- int speed: Movement speed
- int CurrentLevel: Current level (max 10)
- int TrainingPoints: Training tokens
- Various status flags (isShield, isStun, isRevive, etc.)

**Virtual Functions** (must be implemented by derived classes):
- executeMove1(): First special ability
- executeMove2(): Second special ability
- getMove1() / getMove2(): Get cooldown/mana for moves
- copy(): Create a copy of the pet
- getType(): Return pet type ID

**Derived Classes**:
- Dragon (include/Pets/Dragon.h)
- Phoenix (include/Pets/Phoenix.h)
- Unicorn (include/Pets/Unicorn.h)
- Griffin (include/Pets/Griffin.h)

#### 4. Arena Class (include/Arena.h)
**Purpose**: Base class for battle arenas

**Data Members**:
- Wall W1, W2: Wall obstacles
- Stone S1, S2: Stone obstacles
- int Prize: Reward for winning
- loat TimeLimit: Battle time limit (60 seconds)
- sf::Sound hitSound: Sound effect for hits

**Derived Classes**:
- oneVone: 1v1 battles
- 	woVtwo: 2v2 battles
- guildVguild: Guild vs Guild battles

#### 5. Battle Modes

##### oneVone (include/BattleModes/oneVone.h)
- Pet* userPet: Player's pet
- Pet* AiPet: AI opponent's pet
- Battle(): Main battle loop

##### twoVtwo (include/BattleModes/twoVtwo.h)
- Similar structure but with 2 pets per side

##### guildVguild (include/BattleModes/guildVguild.h)
- Full guild teams battling

#### 6. Supporting Classes

**Shop** (include/Shop.h):
- Manages item prices
- Items: Healing Potion, Mana Potion, Buff Item, Shield

**Guild** (include/Guild.h):
- Contains 4 pets (Tank, Healer, DamageDealer, Striker)
- Has name, ID, and score
- Can be sorted by score

**TrainingCamp** (include/TrainingCamp.h):
- Handles pet training mini-games
- Awards training tokens

**Obstacles** (include/Obstacles.h):
- Wall: Vertical obstacle
- Stone: Square obstacle
- Used in battle arenas

## Workflow

### Game Initialization Flow

`
main()
  â””â”€> Game::StartGame()
       â”œâ”€> Initialize random seed
       â”œâ”€> Initialize sound system
       â”œâ”€> Create SFML window (1280x720)
       â”œâ”€> Load fonts and textures
       â”œâ”€> Create Player with 4 pets
       â”œâ”€> Create battle arenas (1v1, 2v2, Guild)
       â”œâ”€> Create Shop and TrainingCamp
       â”œâ”€> Generate random obstacle positions
       â””â”€> Enter main game loop
`

### Main Game Loop

`
while (window.isOpen()) {
    1. Process Events (keyboard/mouse input)
    2. Update Game State
       - Check state flags (isMainMenu, isBattle, etc.)
       - Handle state transitions
    3. Render Current State
       - Clear window
       - Draw background
       - Draw UI elements
       - Draw game objects
       - Display window
}
`

### State Transition Flow

`
Main Menu
  â”œâ”€> [B] Battle Mode
  â”‚     â””â”€> AskBattleType()
  â”‚           â”œâ”€> 1v1 Battle
  â”‚           â”œâ”€> 2v2 Battle
  â”‚           â””â”€> Guild Battle
  â”œâ”€> [T] Training Camp
  â”‚     â””â”€> Training()
  â”œâ”€> [S] Shop
  â”‚     â””â”€> showShop()
  â”œâ”€> [G] Guild Management
  â”‚     â””â”€> GuildManage()
  â””â”€> [U] Upgrade Pet
        â””â”€> UpgradePet()
`

### Battle Flow (1v1 Example)

`
AskPetfor1V1()
  â””â”€> oneVone::Battle()
       â”œâ”€> Initialize battle arena
       â”œâ”€> Set up pets (user and AI)
       â”œâ”€> while (battle active) {
       â”‚     â”œâ”€> Process input (movement, attacks)
       â”‚     â”œâ”€> Update AI behavior
       â”‚     â”œâ”€> Update obstacles (falling)
       â”‚     â”œâ”€> Check collisions
       â”‚     â”‚     â”œâ”€> Pet vs Bullet
       â”‚     â”‚     â”œâ”€> Pet vs Obstacle
       â”‚     â”‚     â””â”€> Pet vs Pet
       â”‚     â”œâ”€> Update status effects
       â”‚     â”œâ”€> Check win/loss conditions
       â”‚     â””â”€> Render everything
       â”‚   }
       â””â”€> Award prizes / Update stats
`

## Key Components

### 1. Input Handling

**Keyboard Input**:
- Main Menu: B, T, S, G, U, E (Exit)
- Battle: Arrow keys (movement), Space (shoot), Z/X (special moves), M/H/B/S (potions)

**Mouse Input**:
- Button clicks for UI interactions
- Hover effects on buttons

### 2. Collision Detection

The game uses **bounding box collision detection**:
- Pet sprites have rectangular bounds
- Bullets are point-based
- Obstacles have rectangular bounds
- Collision checks happen every frame

**Collision Types**:
- Pet vs Bullet: Damage calculation
- Pet vs Obstacle: Damage and potential stun
- Pet vs Pet: Close combat (if implemented)

### 3. Status Effects System

Pets can have various status effects:
- isShield: Reduces incoming damage
- isStun: Prevents movement/actions
- isRevive: Auto-revive on death
- isFireBall: Fire-based attack active
- isSpeed: Movement speed boost
- isClaw: Enhanced melee attack
- griffinStun: Griffin-specific stun

### 4. Resource Management

**Player Resources**:
- Currency: Earned from battles, spent in shop
- Potions: Purchased from shop, used in battle
- Training Tokens: Earned from training camp, used for upgrades

**Pet Resources**:
- Health: Reduced by damage, restored by healing
- Mana: Used for special moves
- Training Points: Used for leveling up

### 5. File I/O

**Save System**:
- Player data saved to ssets/data/ directory
- Includes: Currency, potions, pet levels, guilds
- Loaded on game start

**Asset Loading**:
- Images: ssets/images/*.png
- Sounds: ssets/sounds/*.wav or *.ogg
- Fonts: ssets/fonts/*.ttf

## Data Flow

### Pet Selection Flow

`
User selects pet
  â””â”€> Game::AskPetfor1V1()
       â””â”€> Display pet selection UI
            â””â”€> User clicks/keys pet
                 â””â”€> oneVone::setUserPet(selectedPet)
                      â””â”€> Create AI pet (random or based on difficulty)
                           â””â”€> Start battle
`

### Shop Purchase Flow

`
User clicks item in shop
  â””â”€> Check if user has enough currency
       â”œâ”€> Yes: Deduct currency, add item to inventory
       â”‚     â””â”€> Update Player inventory
       â””â”€> No: Show "Insufficient funds" popup
`

### Training Flow

`
User selects pet for training
  â””â”€> TrainingCamp::TrainPet()
       â””â”€> Mini-game (dodge obstacles, collect tokens)
            â””â”€> Award training tokens based on performance
                 â””â”€> Update Pet::TrainingPoints
`

### Battle Update Cycle

`
Every Frame:
  1. Input Processing
     â””â”€> Update pet position/actions
  2. AI Update
     â””â”€> Calculate AI pet actions
  3. Physics Update
     â”œâ”€> Move bullets
     â”œâ”€> Update obstacles (gravity)
     â””â”€> Update status effects (timers)
  4. Collision Detection
     â””â”€> Check all collision pairs
  5. Damage Calculation
     â””â”€> Apply damage based on collisions
  6. Status Updates
     â””â”€> Update health, mana, cooldowns
  7. Win/Loss Check
     â””â”€> Determine battle outcome
  8. Rendering
     â””â”€> Draw all game objects
`

## Constants and Configuration

All game constants are defined in include/Constants.h:

`cpp
namespace GameConstants {
    const int X_RESOLUTION = 1280;
    const int Y_RESOLUTION = 720;
    const int CELL_SIZE = 64;
    const int MAX_LEVEL = 10;
    const int MAX_GUILDS = 5;
    const int MAX_BULLETS = 10;
    // UI Colors
    const sf::Color BUTTON_COLOR(45, 45, 60);
    const sf::Color BUTTON_TEXT_COLOR(220, 220, 230);
    // ... more colors
}
`

## Build System

The project uses a **Makefile** for building:

**Key Targets**:
- make or make all: Build the project
- make clean: Remove build files
- make run: Build and run the game

**Compilation**:
- Compiler: g++ with C++17 standard
- Libraries: SFML (graphics, window, system, audio)
- Output: KingdomQuest (or KingdomQuest.exe on Windows)

## Memory Management

**Dynamic Allocation**:
- Pet pointers in Player class
- Guild array in Player class
- UI buttons (created/deleted each frame to prevent leaks)

**Best Practices**:
- Use smart pointers where possible (future improvement)
- Delete dynamically allocated objects
- Check for null pointers before use

## Extension Points

The modular design allows easy extension:

1. **New Pets**: Inherit from Pet class, implement virtual functions
2. **New Battle Modes**: Inherit from Arena class
3. **New Items**: Extend Shop class
4. **New Status Effects**: Add flags to Pet class
5. **New UI Screens**: Add methods to Game class

## Performance Considerations

- **Rendering**: SFML handles efficient rendering
- **Collision Detection**: Simple bounding box checks (O(nÂ²) for n objects)
- **Asset Loading**: Loaded once at startup, cached in memory
- **State Management**: Boolean flags for simple state machine

## Future Improvements

1. Use smart pointers for memory safety
2. Implement proper state machine pattern
3. Add configuration file for game settings
4. Implement save/load with JSON or binary format
5. Add networking for multiplayer battles
6. Implement particle effects system
7. Add animation system for pets
8. Optimize collision detection (spatial partitioning)

---

**Last Updated**: 2026
**Version**: 1.0
