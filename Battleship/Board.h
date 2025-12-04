#pragma once

// -------------------------------------------------- Board Set-Up ---------------------------------------------------
constexpr int Rank = 10;
constexpr int File = 10;

extern char BoardAlpha[Rank][File];
extern char BoardBeta[Rank][File];

extern char TrackerAlpha[Rank][File];
extern char TrackerBeta[Rank][File];

// ------------------------------------------------- Board Functions -------------------------------------------------
void SetBoard(char Board[Rank][File]);
void PrintBoard(char Board[Rank][File]);

// ------------------------------------------------- Input Functions -------------------------------------------------
bool IsValidCoordinate(char Board[Rank][File], int rank, int file);
int LetterConverter();