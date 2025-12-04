# Shipbattles
- Shipbattles is a completely different game to Battleship with no similarities whatsoever.
- In it players take turns placing ships and then attempt to sink their oppenents ships by guessing where they are on a 10x10 grid.
- Again, this is nothing like Battleship.

## Features
- Two-player gameplay
- Five ship types that are must be manually placed.
    - Destroyer (2 spaces).
    - Submarine (3 spaces).
    - Cruiser (3 spaces).
    - Battleship (4 spaces).
    - Carrier (5 spaces).
- Complex input validation that forces you to reinput until you enter valid coordinates.
- A clear, labeled, display of the board.
    - The ships are displayed in numbered order.
    - Hits are marked by Xs.
    - Misses are marked by Os.

## How to Play
1. Enter the player names.
2. Place each ship on the board by inputting coordinates for each point.
    - Ships cannot be placed diagonally or with gaps.
3. Players take turns guessing where their opponents ships are.
    - Whoever sinks all of their opponents ships first wins.

## Files
- main.cpp: Starts the game and initiates the functions.
- Board.h/cpp: Handles board setup and generic coordinate validation.
- Ship.h/cpp: Handles the Ship and Player structs, while also controlling ship placement and bombardments.
- General.h/cpp: Handles generic/miscellanous functions.
    - Input validation
    - Console utilities