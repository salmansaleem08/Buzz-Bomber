![Gameplay Screenshot](screenshots/gameplay.png)

# Buzz Bombers

Buzz Bombers is a C++ game developed using the SFML library, recreating the classic 1983 Intellivision game by Mattel Electronics. Players control a spray can to combat swarms of bees, turning them into honeycombs for a hummingbird to collect, while avoiding flowers that restrict movement. The game features three progressively challenging levels and a boss level, a high-score system, power-ups, and a unique infant bee mechanic. With immersive audio-visuals and modular code, it’s ideal for retro arcade fans and C++ game development enthusiasts.

## Table of Contents
- [Features](#features)
- [Installation](#installation)
- [Gameplay](#gameplay)
- [Controls](#controls)
- [Directory Structure](#directory-structure)
- [Dependencies](#dependencies)
- [Building and Running](#building-and-running)
- [Project Requirements](#project-requirements)
- [Contributing](#contributing)

## Features
- **Four Levels**: Three standard levels with increasing difficulty and a boss level with unique mechanics.
- **Enemy Types**:
  - **Worker Bees**: Yellow, turn into yellow honeycombs (100 points).
  - **Killer/Fast Bees**: White, faster, turn into red honeycombs (1000 points).
  - **Infant Bee**: Spawns dynamically from hives in the boss level, matures into a hunter bee or forms a new hive.
  - **Hummingbird**: Collects honeycombs for bonus points (500–2000 points based on tier and bee type).
- **Power-Ups (Boss Level)**:
  - Speed Increase/Decrease: Adjusts spray can movement speed.
  - Height Increase/Decrease: Modifies spray range.
  - Dropped when the hummingbird eats a honeycomb or when shooting red honeycombs from hunter bees.
  - Temporary effects with a timer bar; opposite effects cancel.
- **High-Score System**: Stores top 10 scores with player names in a file, accessible from the main menu and displayed at game end.
- **Game Mechanics**:
  - Bees plant flowers that restrict player movement.
  - Beehives form when worker bees are trapped, yielding bonus points (1000–2000) upon level completion.
  - Spray cans have 56 sprays, with a health bar decreasing every 8 sprays; bonus cans awarded at 20,000, 40,000, 80,000 points, and every 80,000 thereafter.
- **Audio-Visuals**: Unique background music and textures per level, custom font for UI, and sprite-based graphics.

## Installation
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/your-username/buzz-bombers.git
   cd buzz-bombers
   ```

2. **Install SFML**:
   - **Ubuntu**:
     ```bash
     sudo apt-get install libsfml-dev
     ```
   - **macOS (Homebrew)**:
     ```bash
     brew install sfml
     ```
   - **Windows**: Download SFML from [sfml-dev.org](https://www.sfml-dev.org/) and follow setup instructions.

3. **Verify Assets**:
   - Ensure `Textures/`, `Music/`, and `fonts/` directories are in the project root with required files (e.g., `spray.png`, `Music3.ogg`, `Grind_Demolished.ttf`).

## Gameplay
- **Objective**: Spray bees to create honeycombs, avoid being trapped by flowers, and maximize your score. The hummingbird eats honeycombs for bonus points, and beehives add points at level completion.
- **Levels**:
  - **Level 1**: 20 regular bees, 3 pre-generated honeycombs.
  - **Level 2**: 15 regular bees, 5 fast bees, 9 pre-generated honeycombs.
  - **Level 3**: 20 regular bees, 10 fast bees, 15 pre-generated honeycombs.
  - **Boss Level**: 20 regular bees, 15 fast bees, 15 honeycombs, 5 hives (randomly placed); includes power-ups and infant bees.
- **Scoring**:
  - Worker Bee: 100 points.
  - Fast Bee: 1000 points.
  - Hummingbird Eating Yellow Honeycomb: 1000 (top tiers), 800 (mid tiers), 500 (lower tiers).
  - Hummingbird Eating Red Honeycomb: 2000 (top tiers), 1800 (mid tiers), 1500 (lower tiers).
  - Beehive (Level End): 2000 (top tiers), 1600 (mid tiers), 1000 (lower tiers).
  - Infant Bee (Child Form): -500 points penalty.
- **Game Over**: Occurs when all spray cans are depleted or all levels are completed. If the score qualifies, the player enters their name for the high-score list.

## Controls
- **Arrow Keys (Left/Right)**: Move the spray can horizontally.
- **Spacebar**: Shoot spray.
- **Mouse Click (Menu)**: Select level, view high scores, or quit.
- **Escape (High Scores)**: Return to menu.

## Directory Structure
```
buzz-bombers/
├── Textures/
│   ├── spray.png
│   ├── bullet.png
│   ├── Regular_bee.png
│   ├── Fast_bee.png
│   ├── honeycomb.png
│   ├── honeycomb_red.png
│   ├── hive.png
│   ├── bird1.png
│   ├── obstacles.png
│   ├── background1.jpg
│   ├── background2.jpg
│   ├── background3.jpg
├── Music/
│   ├── Music3.ogg
│   ├── risk.ogg
│   ├── magical_journey.ogg
├── fonts/
│   ├── Grind_Demolished.ttf
├── screenshots/
│   ├── gameplay.png
├── highscores.txt
├── main.cpp
├── README.md
```

## Dependencies
- **SFML 2.5+**: Modules: Graphics, Audio, Window, System.
- **C++ Compiler**: C++11 or later (e.g., g++, MSVC).
- **OS**: Windows, macOS, Linux.

## Building and Running
1. **Compile**:
   ```bash
   g++ -c main.cpp -I/path/to/sfml/include
   g++ main.o -o buzz_bombers -L/path/to/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
   ```
   Replace `/path/to/sfml/` with your SFML path.

2. **Run**:
   Ensure asset directories are with the executable.
   ```bash
   ./buzz_bombers
   ```

3. **Windows**:
   - Place SFML DLLs (e.g., `sfml-graphics-2.dll`) with the executable or in PATH.
   - For Visual Studio, link SFML libraries in project settings.

## Project Requirements
Based on the project guidelines (PF PROJECT 24' - Phase 1 and Phase 2):

### Phase 1
- **Game Recreation**: Implements core Buzz Bombers mechanics, including worker bees, killer/fast bees, hummingbird, honeycombs, beehives, and flowers.
- **Three Levels**:
  - Unique backgrounds and music per level.
  - Escalating difficulty with more bees and honeycombs.
- **Game Menu**: Allows level selection, high-score viewing, and quitting.
- **Player Controls**: Arrow keys for movement, spacebar for spraying.
- **Code Organization**:
  - Modular functions for rendering, updates, and collisions.
  - Clear comments and variable names.
  - Constants for fixed values.
- **Testing**: Modular testing for integration.

### Phase 2
- **High-Score System**:
  - Stores top 10 scores with names in `highscores.txt`.
  - Displayed in the main menu and at game end.
  - Prompts for player name when score qualifies.
- **Boss Level (Level 4)**:
  - Accessible from the menu.
  - Includes 20 regular bees, 15 fast bees, 15 honeycombs, 5 hives (randomly placed).
  - Features power-ups and infant bee mechanic.
- **Power-Ups**:
  - Types: Speed Increase/Decrease, Height Increase/Decrease.
  - Dropped by hummingbird eating honeycombs or spraying red honeycombs.
  - Temporary effects with a timer bar; opposite effects cancel.
- **Infant Bee Mechanic**:
  - Dynamically spawns from hive tops after a balanced interval.
  - Moves upward, shifts left/right if blocked, or forms a hive if trapped.
  - Matures into a hunter bee at the top, following standard rules.
  - -500 points for killing in child form.
- **Bonus Features (Not Implemented)**:
  - **View Bonus**: Doubles game grid columns, shifts view with player movement using `sf::View`.
  - **Infant Bee Animation**: Uses sprite sheets for smooth animations.
  - **GitHub Upload**: This README and repository organization fulfill this requirement.

## Contributing
1. Fork the repository.
2. Create a branch (`git checkout -b feature/your-feature`).
3. Commit changes (`git commit -m "Add your feature"`).
4. Push (`git push origin feature/your-feature`).
5. Open a pull request.

Ensure code aligns with existing style and includes comments.