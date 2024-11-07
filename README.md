# Data-Structures_A3
Gamers Database Manager

# Game Management System

## Overview

This is a Game Management System built using C++ that allows users to manage a collection of games and track player activities. The system features two main components:

1. **Game Tree**: A binary search tree that holds details of each game, allowing for efficient search, insertion, deletion, and editing of game data.
2. **Player List**: A linked list that tracks players and the number of games they've played. Players can be added, and the top N players can be displayed.

The system supports the following functionalities:
- Add and update games and player data.
- Search for games by their ID.
- Edit game details.
- Delete games from the system.
- Save and load game data to/from a file.
- Track and display the top N players based on the number of games they’ve played.

## Features

### Game Tree Operations:
- **Insert a Game**: Adds a new game with details like ID, name, publisher, developer, price, and rating.
- **Delete a Game**: Removes a game from the system based on its ID.
- **Search for a Game**: Finds a game by its unique ID.
- **Edit Game Details**: Allows you to modify the details of an existing game.
- **Save/Load Data**: Saves the game list to a file and loads it back into the system.

### Player List Operations:
- **Add a Player**: Adds a new player with their details (ID, name, phone, email, password).
- **Update Games Played**: Tracks the number of games each player has interacted with.
- **Display Top N Players**: Shows the top N players based on the number of games they’ve played.

## File Structure

- `DS_C_A3_i232651.cpp` - Main file with the implementation of the game tree, player list, and their associated functions.
- `pre_order_traversal.txt` - Sample data file where game data is saved.
  
## Compilation and Execution

1. Compile the code using any C++ compiler:
   ```bash
   g++ -o game_management_system game_management_system.cpp
