#include "Board.h"
#include "General.h"
#include <iostream>

// -------------------------------------------------- Board Set-Up ---------------------------------------------------
char BoardAlpha[Rank][File];
char BoardBeta[Rank][File];

char TrackerAlpha[Rank][File];
char TrackerBeta[Rank][File];

// ------------------------------------------------- Board Functions -------------------------------------------------
void SetBoard(char Board[Rank][File])
{
	for (int i = 0; i < Rank; i++)
	{
		for (int j = 0; j < File; j++)
		{
			Board[i][j] = ' ';
		}
	}
}
void PrintBoard(char Board[Rank][File])
{
	// Print column headers (A-J)
	std::cout << "  "; // top-left corner padding
	for (int j = 0; j < File; j++)
	{
		char colHeader = 'A' + j;
		std::cout << colHeader << " ";
	}
	std::cout << "\n";

	for (int i = 0; i < Rank; i++)
	{
		// Print row header (1-10)
		std::cout << i + 1;
		if (i + 1 < 10) std::cout << " "; // align single-digit numbers

		for (int j = 0; j < File; j++)
		{
			std::cout << Board[i][j] << "|";
		}
		std::cout << "\n";

		if (i < Rank - 1)
		{
			// separator row
			std::cout << "  "; // padding under row header
			for (int f = 0; f < File; f++)
			{
				std::cout << "- ";
			}
			std::cout << "\n";
		}
	}
}

// ------------------------------------------------- Input Functions -------------------------------------------------
bool IsValidCoordinate(char Board[Rank][File], int rank, int file)
{
	if (rank < 0 || rank >= Rank || file < 0 || file >= File)
	{
		return false;
	}
	if (Board[rank][file] != ' ')
	{
		return false;
	}
	return true;
}
int LetterConverter()
{
	char Letter = Util::ValidateChar("X (A-J): ", "ABCDEFGHIJabcdefghij");
	Letter = toupper(Letter);
	return Letter - 'A';
}
