# 2048-AI-player-minimax
This is a 2048 AI player using Minimax Algorithm with α-β pruning

## Introduction

This is a C++ implementation of the classic 2048 game designed to run on Unix systems. This game features both manual and AI-controlled gameplay options, allowing players to either control the game using keyboard inputs or let the AI take over.

## System Requirements

- Unix/Linux operating system
- C++ compiler (e.g., g++)
- GNU Make

## Installation and Compilation

To install and compile the game, follow these steps:

```bash
# Clone the repository to your local machine (adjust the URL to your repository)
git clone https://github.com/your-username/2048.git

# Change directory into the game's directory
cd 2048

# Use Makefile to compile the game
make

# To start the game, execute the following command:
./start
```

## Gameplay Options
Upon starting the game, you will be presented with the first choice interface where you can select between:

## Manual Mode: Control the game manually using the keyboard.
Use W, A, S, D keys to move the tiles up, left, down, and right, respectively.

AI Mode: Let the AI control the game. You can choose:

Single Run: Execute the game once automatically.

Multiple Runs: Execute the game multiple times to generate statistical data.
## AI Strategies

### AI1 (Test Mode):
This mode uses a simple strategy where the AI performs moves in a fixed WASD sequence. It's primarily used for testing basic functionality.

### AI2 (Minimax Algorithm):
This is an advanced AI mode using the Minimax search algorithm. Before running, you must input the following parameters:

1. Depth

Heuristic：

2. count of empty spaces

3. Monotonicity

4. Position of the largest tile
 
5. Smoothness coefficient
 
After inputting these parameters, the AI2 will begin running automatically and provide statistics such as the highest, lowest, and average scores, as well as the average running time.
