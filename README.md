# Snake Game 🐍

A classic Snake game implementation in C++ for Windows console. Control the snake to eat apples, grow longer, and avoid hitting yourself!

## Features

- **Classic Snake Gameplay**: Navigate the snake around the map to collect apples
- **Dynamic Growth**: Snake grows longer with each apple eaten
- **Wraparound Map**: Snake wraps around the edges of the map
- **Score Tracking**: Keep track of your points (number of apples eaten)
- **Time Tracking**: See how long you survived
- **Self-Collision Detection**: Game ends when snake hits itself
- **Smooth Controls**: Responsive WASD keyboard controls

## Requirements

- **Operating System**: Windows (uses Windows-specific libraries)
- **Compiler**: C++ compiler with C++11 support or higher (e.g., MinGW, Visual Studio)
- **Libraries**: 
  - `windows.h` (Windows API)
  - `conio.h` (Console I/O)

## Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/TanLocLouis/snake-game.git
   cd snake-game
   ```

2. Compile the game using your preferred C++ compiler:
   
   **Using g++ (MinGW):**
   ```bash
   g++ snake.cpp -o snake.exe
   ```
   
   **Using Visual Studio Developer Command Prompt:**
   ```bash
   cl snake.cpp
   ```

3. Run the game:
   ```bash
   snake.exe
   ```

## How to Play

### Controls
- **W** - Move Up
- **A** - Move Left
- **S** - Move Down
- **D** - Move Right

### Game Mechanics
- The snake starts in the center of the map moving to the right
- Collect apples (marked with `*`) to grow longer and increase your score
- The snake is represented by `x` characters
- Avoid running into yourself - the game ends if the snake's head hits any part of its body
- The snake wraps around the screen edges (goes through walls)

### Objective
Survive as long as possible while collecting as many apples as you can to achieve the highest score!

## Game Configuration

You can modify these constants in `snake.cpp` to customize the game:

- `MAP_SIZE`: Size of the game map (default: 30)
- `GAME_TICK`: Game speed/refresh rate (default: 30 FPS)

## Result Screen

After the game ends, you'll see:
- Total time played (in seconds)
- Final score (number of apples collected)

## Technical Details

- **Language**: C++
- **Map Size**: 30x30 grid
- **Snake Representation**: Vector of coordinates
- **Collision Detection**: Self-collision check on every move
- **Apple Spawning**: Random position generation

## Author

Created by TanLocLouis

## License

This project is open source and available for educational purposes.
