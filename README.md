<div align="center">

# 🐉 Kingdom Quest - Magical Pets Battle Arena

[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://en.cppreference.com/)
[![SFML](https://img.shields.io/badge/SFML-3.0-green.svg)](https://www.sfml-dev.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)]()

**An epic C++ SFML-based battle arena game featuring magical pets, strategic combat, and dynamic gameplay mechanics.**

[Features](#-features) • [Installation](#-installation) • [Usage](#-usage) • [Documentation](#-documentation) • [Contributing](#-contributing)

</div>

---

## 🎮 Features

### Core Gameplay
- **🎯 Multiple Battle Modes**: 1v1, 2v2, and Guild vs Guild combat
- **🐾 Four Unique Pets**: Dragon, Phoenix, Unicorn, and Griffin - each with distinct abilities
- **⚔️ Real-Time Combat**: Dynamic battles with projectile attacks and special moves
- **🛡️ Strategic Elements**: Shield, buff, stun, and revive mechanics
- **🎲 Obstacle Dodging**: Navigate falling obstacles during intense battles

### Game Systems
- **🏪 Shop System**: Purchase potions and items to enhance your pets
- **🏋️ Training Camp**: Level up your pets and improve their stats
- **👥 Guild Management**: Create and manage up to 5 guilds with different pet combinations
- **📊 Leaderboard**: Track your progress and compete for the top spot
- **💾 Save System**: Persistent game data storage

### Technical Features
- **🎨 Modern UI**: Sleek dark theme with improved contrast and readability
- **🔊 Sound Effects**: Immersive audio feedback for actions
- **🖼️ Rich Graphics**: Custom sprites and animations for all pets
- **⚡ Performance Optimized**: Efficient collision detection and rendering

## 📁 Project Structure

```
Kingdom-Quest/
├── assets/              # Game assets
│   ├── images/         # Sprites and backgrounds (PNG)
│   ├── sounds/         # Audio files (WAV, OGG)
│   ├── fonts/          # Font files (TTF)
│   └── data/           # Save files and game data
├── include/            # Header files
│   ├── Pets/           # Pet class headers (Dragon, Phoenix, Unicorn, Griffin)
│   ├── BattleModes/    # Battle mode implementations
│   ├── Game.h          # Main game controller
│   ├── Player.h        # Player class
│   ├── Guild.h         # Guild management
│   ├── Shop.h          # Shop system
│   ├── TrainingCamp.h  # Training mechanics
│   ├── Arena.h         # Battle arena base class
│   ├── Obstacles.h     # Obstacle system
│   ├── SoundManager.h  # Audio management
│   └── Constants.h     # Game constants
├── src/                # Source files
│   ├── Pets/           # Pet implementations
│   ├── BattleModes/    # Battle mode logic
│   └── *.cpp           # Core game files
├── build/              # Build output (object files)
├── docs/               # Documentation
│   ├── HOW_TO_RUN.md  # Detailed setup instructions
│   └── GameUML.mdj     # UML diagram
├── Makefile            # Build configuration
└── README.md           # This file
```

## 🧱 Requirements

### Essential
- **C++ Compiler** with C++17 support (g++, clang++, or MSVC)
- **SFML 3.0+** (Simple and Fast Multimedia Library)
- **Make** utility (for build automation)

### Platform-Specific
- **Windows**: MSYS2 UCRT64 (recommended) or MinGW-w64
- **Linux**: g++ and libsfml-dev
- **macOS**: Xcode Command Line Tools and Homebrew

## 🚀 Installation

### Windows (MSYS2 UCRT64) ⭐ Recommended

1. **Install MSYS2** from [msys2.org](https://www.msys2.org/)
2. **Open UCRT64 terminal** (not MINGW64)
3. **Install SFML**:
   ```bash
   pacman -S mingw-w64-ucrt-x86_64-sfml
   ```
4. **Clone and build**:
   ```bash
   git clone <repository-url>
   cd Kingdom-Quest
   make
   ```

### Windows (MinGW - Alternative)

1. Install MinGW-w64 and SFML
2. Build using:
   ```powershell
   mingw32-make
   ```

### Linux

```bash
# Install dependencies
sudo apt-get install libsfml-dev g++ make  # Ubuntu/Debian
sudo dnf install SFML-devel gcc-c++ make   # Fedora

# Build
make
```

### macOS

```bash
# Install SFML via Homebrew
brew install sfml

# Build
make
```

## 🎮 Usage

### Running the Game

```bash
# Build and run
make run

# Or run directly
./KingdomQuest        # Linux/macOS
.\KingdomQuest.exe     # Windows
```

### Game Controls

#### Main Menu
- **B** - Enter Battle Mode
- **T** - Training Camp
- **S** - Shop
- **G** - Guild Management
- **M** - View Manual
- **L** - Leaderboard

#### Battle Controls
- **Arrow Keys** - Move pet
- **Space** - Fire bullet
- **Z** - Special Move 1
- **X** - Special Move 2
- **M** - Use Mana Potion
- **H** - Use Healing Potion
- **B** - Use Buff Potion
- **S** - Use Shield Potion
- **Tab** - Switch between pets (in 2v2 mode)

> 📖 **For detailed instructions, see [docs/HOW_TO_RUN.md](docs/HOW_TO_RUN.md)**

## 📚 Documentation

- **[HOW_TO_RUN.md](docs/HOW_TO_RUN.md)** - Detailed setup and installation guide
- **[CODE_DOCUMENTATION.md](CODE_DOCUMENTATION.md)** - Complete code structure and workflow explanation
- **[PRESENTATION.md](PRESENTATION.md)** - Project presentation guide

## 🎨 Game Screenshots

*Add screenshots of your game here*

## 🏗️ Architecture

### Class Hierarchy

```
Game (Main Controller)
├── Player
│   ├── Pet* (Array of 4 pets)
│   └── Guild* (Array of up to 5 guilds)
├── BattleModes
│   ├── oneVone (1v1 battles)
│   ├── twoVtwo (2v2 battles)
│   └── guildVguild (Guild battles)
├── Shop (Item purchasing)
├── TrainingCamp (Pet leveling)
└── Arena (Base battle arena)
    └── Obstacles (Falling blocks)
```

### Pet System

All pets inherit from the base `Pet` class and implement:
- `executeMove1()` - First special ability
- `executeMove2()` - Second special ability
- Unique stats and abilities per pet type

**Available Pets:**
- 🐉 **Dragon**: High damage, fire-based attacks
- 🔥 **Phoenix**: Healing abilities, fire resistance
- 🦄 **Unicorn**: Speed and agility, magical attacks
- 🦅 **Griffin**: Balanced stats, stun abilities

## 🛠️ Development

### Building from Source

```bash
# Clone repository
git clone <repository-url>
cd Kingdom-Quest

# Build
make

# Clean build files
make clean

# Run
make run
```

### Project Structure Benefits

The modular architecture enables:
- ✅ Easy addition of new pets or abilities
- ✅ Simple UI modifications
- ✅ Feature extensions without breaking existing code
- ✅ Collaborative development
- ✅ Maintainable and scalable codebase

## 🐛 Troubleshooting

### Common Issues

**SFML not found:**
- Ensure SFML is properly installed
- Check that SFML libraries are in your PATH
- Verify SFML version is 3.0 or later

**Asset loading errors:**
- Run the game from the project root directory
- Verify `assets/` folder structure is intact

**Compilation errors:**
- Ensure C++17 support is enabled
- Check all SFML libraries are linked correctly

For more help, see [docs/HOW_TO_RUN.md](docs/HOW_TO_RUN.md)

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📝 License

This project is licensed for educational purposes.

## 👤 Author

**Your Name**
- GitHub: [@yourusername](https://github.com/yourusername)

## 🙏 Acknowledgments

- SFML community for the excellent multimedia library
- All contributors and testers
- Open source game development community

---

<div align="center">

**Made with ❤️ using C++ and SFML**

⭐ Star this repo if you find it helpful!

</div>
