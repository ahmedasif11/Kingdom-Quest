# How to Run Magical Pets Kingdom

## Prerequisites

1. **C++ Compiler** with C++17 support:
   - Windows: MinGW-w64 or MSVC
   - Linux: g++ (usually pre-installed)
   - macOS: Xcode Command Line Tools

2. **SFML Library** (2.5 or later):
   - Download from: https://www.sfml-dev.org/download.php
   - Make sure SFML is properly installed and linked

3. **Make** (for using Makefile):
   - Windows: Install via MinGW or use WSL
   - Linux/macOS: Usually pre-installed

## Installation Steps

### Windows (MSYS2 UCRT64) ⭐ Recommended for Windows

If you have MSYS2 UCRT64 installed (which you do):

1. **Open UCRT64 terminal** (not MINGW64 or MSYS)

2. **Install SFML (if not already installed):**
   ```bash
   pacman -S mingw-w64-ucrt-x86_64-sfml
   ```

3. **Navigate to project and build:**
   ```bash
   cd /d/C++/Kingdom-Quest
   make
   ```

4. **See [MSYS2_SETUP.md](MSYS2_SETUP.md) for detailed MSYS2 instructions**

### Windows (MinGW - Alternative)

1. **Install SFML:**
   ```powershell
   # Download SFML from official website
   # Extract to C:\SFML or your preferred location
   ```

2. **Set Environment Variables (if needed):**
   ```powershell
   # Add SFML bin directory to PATH
   $env:Path += ";C:\SFML\bin"
   ```

3. **Update Makefile (if SFML is not in default location):**
   ```makefile
   # Edit Makefile and add SFML include/lib paths if needed:
   CXXFLAGS = -std=c++17 -Wall -I./include -IC:/SFML/include
   LDFLAGS = -LC:/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
   ```

### Linux

1. **Install SFML:**
   ```bash
   # Ubuntu/Debian
   sudo apt-get install libsfml-dev

   # Fedora
   sudo dnf install SFML-devel
   ```

### macOS

1. **Install SFML via Homebrew:**
   ```bash
   brew install sfml
   ```

## Building and Running

### Method 1: Using Makefile (Recommended)

```bash
# Navigate to project directory
cd d:\C++\Kingdom-Quest

# Build the project
make

# Run the game
make run

# Or build and run in one command
make && make run

# Clean build files
make clean
```

**Note for Windows:**

- **MSYS2 UCRT64 (Recommended):** Use `make` directly in UCRT64 terminal. See [MSYS2_SETUP.md](MSYS2_SETUP.md) for details.
- **MinGW:** Use `mingw32-make` instead of `make`:
  ```powershell
  mingw32-make
  mingw32-make run
  ```

### Method 2: Manual Compilation

```bash
# Compile all source files
g++ -std=c++17 -Wall -I./include \
    src/*.cpp src/Pets/*.cpp src/BattleModes/*.cpp \
    -o KingdomQuest \
    -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Run the game
./KingdomQuest        # Linux/macOS
.\KingdomQuest.exe    # Windows (if compiled as .exe)
```

### Method 3: Using CMake (Alternative)

If you prefer CMake, you can create a CMakeLists.txt file (not provided by default).

## Troubleshooting

### Common Issues

1. **"SFML not found" error:**
   - Make sure SFML is installed
   - Check that SFML libraries are in your system PATH
   - Verify SFML version is 2.5 or later

2. **"undefined reference to sf::..." errors:**
   - Ensure all SFML libraries are linked: `-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio`
   - Check that SFML lib directory is in your library path

3. **Asset loading errors:**
   - Make sure you run the game from the project root directory
   - Verify `assets/` folder exists with all subdirectories (images/, sounds/, fonts/, data/)

4. **Windows-specific:**
   - Make sure SFML DLLs are in the same directory as the executable
   - Or add SFML bin directory to your PATH

### File Structure Check

Before running, ensure your directory structure looks like:
```
Kingdom-Quest/
├── assets/
│   ├── images/    (all .png files)
│   ├── sounds/    (all .wav, .ogg files)
│   ├── fonts/     (all .ttf files)
│   └── data/      (save files)
├── include/       (header files)
├── src/           (source files)
├── Makefile
└── README.md
```

## Game Controls

Once the game is running:
- **Main Menu:** Use keyboard shortcuts (B for Battle, T for Training, etc.)
- **Battle Controls:**
  - Arrow keys: Move pet
  - Space: Fire bullet
  - Z: Special move 1
  - X: Special move 2
  - M: Use Mana Potion
  - H: Use Healing Potion
  - B: Use Buff Potion
  - S: Use Shield Potion

Enjoy playing!

