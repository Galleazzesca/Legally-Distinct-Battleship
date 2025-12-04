#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <utility>

struct Ships
{
	std::string Type;
	int Length;
	int Hits;
	std::vector<int> RankLocation;
	std::vector<int> FileLocation;
	char Status;
};

struct Player
{
	std::string Name;
	std::vector<Ships> Fleet;
};

// ------------------------------------------------ Factory Functions ------------------------------------------------
Ships SetDestroyer();
Ships SetSubmarine();
Ships SetCruiser();
Ships SetBattleship();
Ships SetCarrier();
std::pair<Ships, char> CreateShip(const std::string Ship = "");

// ----------------------------------------------- Placement Functions -----------------------------------------------
Ships ManualPlacement(char Board[Rank][File], Ships TempShip, char N, const std::string Ship = "");
Ships PlaceShip(char Board[Rank][File], const std::string Ship = "");
void SetupFleet(char Board[Rank][File], Player &Number);

// ----------------------------------------------- Shooting Functions ------------------------------------------------
void ProcessBombardment(Player& Opponent, char Board[Rank][File], char Tracker[Rank][File], int Row, int Col);
void OrderBombardment(Player& Opponent, char Board[Rank][File], char Tracker[Rank][File]);

// ------------------------------------------- Dovie'andi se tovya sagain --------------------------------------------
bool DovieAndi(const Player& Navy);