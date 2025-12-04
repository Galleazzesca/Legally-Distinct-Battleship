#include "General.h"
#include "Board.h"
#include "Ship.h"
#include <iostream>
#include <cmath>

// ------------------------------------------------ Factory Functions ------------------------------------------------
Ships SetDestroyer()
{
	Ships TempDestroyer;

	TempDestroyer.Type = "Destroyer";

	TempDestroyer.Length = 2;

	TempDestroyer.Hits = 0;

	TempDestroyer.FileLocation.push_back(0);
	TempDestroyer.RankLocation.push_back(0);

	TempDestroyer.FileLocation.push_back(0);
	TempDestroyer.RankLocation.push_back(1);

	TempDestroyer.Status = '0'; // Intact
	return TempDestroyer;
}
Ships SetSubmarine()
{
	Ships TempSubmarine;

	TempSubmarine.Type = "Submarine";

	TempSubmarine.Length = 3;

	TempSubmarine.Hits = 0;

	TempSubmarine.FileLocation.push_back(1);
	TempSubmarine.RankLocation.push_back(0);

	TempSubmarine.FileLocation.push_back(1);
	TempSubmarine.RankLocation.push_back(1);

	TempSubmarine.FileLocation.push_back(1);
	TempSubmarine.RankLocation.push_back(2);

	TempSubmarine.Status = '0'; // Intact
	return TempSubmarine;
}
Ships SetCruiser()
{
	Ships TempCruiser;

	TempCruiser.Type = "Cruiser";

	TempCruiser.Length = 3;

	TempCruiser.Hits = 0;

	TempCruiser.FileLocation.push_back(2);
	TempCruiser.RankLocation.push_back(0);

	TempCruiser.FileLocation.push_back(2);
	TempCruiser.RankLocation.push_back(1);

	TempCruiser.FileLocation.push_back(2);
	TempCruiser.RankLocation.push_back(2);

	TempCruiser.Status = '0'; // Intact
	return TempCruiser;
}
Ships SetBattleship()
{
	Ships TempBattleship;

	TempBattleship.Type = "Battleship";

	TempBattleship.Length = 4;

	TempBattleship.Hits = 0;

	TempBattleship.FileLocation.push_back(3);
	TempBattleship.RankLocation.push_back(0);

	TempBattleship.FileLocation.push_back(3);
	TempBattleship.RankLocation.push_back(1);

	TempBattleship.FileLocation.push_back(3);
	TempBattleship.RankLocation.push_back(2);

	TempBattleship.FileLocation.push_back(3);
	TempBattleship.RankLocation.push_back(3);

	TempBattleship.Status = '0'; // Intact
	return TempBattleship;
}
Ships SetCarrier()
{
	Ships TempCarrier;

	TempCarrier.Type = "Carrier";

	TempCarrier.Length = 5;

	TempCarrier.Hits = 0;

	TempCarrier.FileLocation.push_back(4);
	TempCarrier.RankLocation.push_back(0);

	TempCarrier.FileLocation.push_back(4);
	TempCarrier.RankLocation.push_back(1);

	TempCarrier.FileLocation.push_back(4);
	TempCarrier.RankLocation.push_back(2);

	TempCarrier.FileLocation.push_back(4);
	TempCarrier.RankLocation.push_back(3);

	TempCarrier.FileLocation.push_back(4);
	TempCarrier.RankLocation.push_back(4);

	TempCarrier.Status = '0'; // Intact
	return TempCarrier;
}
std::pair<Ships, char> CreateShip(const std::string Ship)
{
	Ships TempShip;
	char N;

	if (Ship == "Destroyer")
	{
		TempShip = SetDestroyer();
		N = '1';
	}
	else if (Ship == "Submarine")
	{
		TempShip = SetSubmarine();
		N = '2';
	}
	else if (Ship == "Cruiser")
	{
		TempShip = SetCruiser();
		N = '3';
	}
	else if (Ship == "Battleship")
	{
		TempShip = SetBattleship();
		N = '4';
	}
	else
	{
		TempShip = SetCarrier();
		N = '5';
	}

	return { TempShip, N };
}

// ----------------------------------------------- Placement Functions -----------------------------------------------
Ships ManualPlacement(char Board[Rank][File], Ships TempShip, char N, const std::string Ship)
{
	std::cout << "Where should the " << Ship << " (" << TempShip.Length << " points)" << " be placed?\n";
	std::cout << "Point 1:\n";
	while (true)
	{
		int tmpFile = LetterConverter();
		int tmpRank = Util::ValidateInt("Y (1-10): ", '+') - 1;

		if (!IsValidCoordinate(Board, tmpRank, tmpFile))
		{
			std::cout << "Invalid coordinate or space occupied. Try again.\n";
			continue;
		}

		TempShip.FileLocation[0] = tmpFile;
		TempShip.RankLocation[0] = tmpRank;
		break;
	}

	Util::Clear();
	Board[TempShip.RankLocation[0]][TempShip.FileLocation[0]] = N;
	PrintBoard(Board);
	char Orientation = 'N';
	char End = 'N';
	int Head = 0;

	for (int i = 1; i < TempShip.Length; i++)
	{
		std::cout << "Where should the " << Ship << " be placed?\n";
		std::cout << "Point " << i + 1 << ":\n";

		int tmpFile, tmpRank;
		while (true)
		{
			// Read both coordinates for the point
			tmpFile = LetterConverter();
			tmpRank = Util::ValidateInt("Y (1-10): ", '+') - 1;

			if (!IsValidCoordinate(Board, tmpRank, tmpFile))
			{
				std::cout << "Invalid coordinate or space occupied. Try again.\n";
				continue;
			}

			int HeadFile = TempShip.FileLocation[Head];
			int HeadRank = TempShip.RankLocation[Head];

			int TailFile = TempShip.FileLocation[i - 1];
			int TailRank = TempShip.RankLocation[i - 1];

			if (std::abs(tmpRank - TailRank) == 1 || std::abs(tmpFile - TailFile) == 1)
			{
				End = 'T';
			}

			else if (std::abs(tmpRank - HeadRank) == 1 || std::abs(tmpFile - HeadFile) == 1)
			{
				End = 'H';
				Head = i - 1;
			}

			if (i == 1)
			{
				// First step: must be adjacent and either same file (vertical) or same rank (horizontal)
				if (tmpFile == TailFile && std::abs(tmpRank - TailRank) == 1)
				{
					Orientation = 'V';
					std::cout << "Orientation set to Vertical.\n";
					break;
				}
				else if (tmpRank == TailRank && std::abs(tmpFile - TailFile) == 1)
				{
					Orientation = 'H';
					std::cout << "Orientation set to Horizontal.\n";
					break;
				}
				else
				{
					std::cout << "Invalid placement. Must be adjacent and not diagonal. Try again.\n";
					continue;
				}
			}
			else
			{
				// Subsequent points: must follow chosen orientation and be adjacent to previous
				if (Orientation == 'V')
				{
					if (tmpFile != TailFile || End == 'T' && std::abs(tmpRank - TailRank) != 1 || End == 'H' && std::abs(tmpRank - HeadRank) != 1)
					{
						std::cout << "Invalid placement. Must continue vertically adjacent. Try again.\n";
						continue;
					}
					else
					{
						break;
					}
				}
				else // Orientation == 'H'
				{
					if (tmpRank != TailRank || End == 'T' && std::abs(tmpFile - TailFile) != 1 || End == 'H' && std::abs(tmpFile - HeadFile) != 1)
					{
						std::cout << "Invalid placement. Must continue horizontally adjacent. Try again.\n";
						continue;
					}
					else
					{
						break;
					}
				}
			}
		} // end while reading point

		// Accept the validated point
		TempShip.FileLocation[i] = tmpFile;
		TempShip.RankLocation[i] = tmpRank;

		Util::Clear();
		Board[TempShip.RankLocation[i]][TempShip.FileLocation[i]] = N;
		PrintBoard(Board);
	}
	return TempShip;
}
Ships PlaceShip(char Board[Rank][File], const std::string Ship)
{
	auto [TempShip, N] = CreateShip(Ship);

	TempShip = ManualPlacement(Board, TempShip, N, Ship);

	return TempShip;
}
void SetupFleet(char Board[Rank][File], Player &Number)
{
	std::cout << Number.Name << " ensure that the other player is looking away.\n";
	Util::Clean();

	std::cout << Number.Name << " you may now place your ships.\n";

	// -------------------------------------------------- Board Set-Up ---------------------------------------------------
	SetBoard(Board);
	PrintBoard(Board);

	// ------------------------------------------------- Ship Placement -------------------------------------------------
	Number.Fleet.push_back(PlaceShip(Board, "Destroyer"));
	Number.Fleet.push_back(PlaceShip(Board, "Submarine"));
	Number.Fleet.push_back(PlaceShip(Board, "Cruiser"));
	Number.Fleet.push_back(PlaceShip(Board, "Battleship"));
	Number.Fleet.push_back(PlaceShip(Board, "Carrier"));
	Util::Clean();
}

// ----------------------------------------------- Shooting Functions ------------------------------------------------
void ProcessBombardment(Player& Opponent, char Board[Rank][File], char Tracker[Rank][File], int Row, int Col)
{
	for (auto& ship : Opponent.Fleet)
	{
		for (int i = 0; i < ship.Length; i++)
		{
			if (ship.RankLocation[i] == Row && ship.FileLocation[i] == Col)
			{
				ship.Hits++;
				std::cout << "Its a hit!\n";
				Tracker[Row][Col] = 'X';

				if (ship.Hits == ship.Length)
				{
					std::cout << "You sunk " << Opponent.Name << "'s " << ship.Type << "!\n";
				}
				return;
			}
		}
	}
	std::cout << "You missed!\n";
	Tracker[Row][Col] = 'O';
	return;
}
void OrderBombardment(Player& Opponent, char Board[Rank][File], char Tracker[Rank][File])
{
	std::cout << "Where do you think " << Opponent.Name << "'s ship is?\n";
	PrintBoard(Tracker);
	while (true)
	{
		int tmpFile = LetterConverter();
		int tmpRank = Util::ValidateInt("Y (1-10): ", '+') - 1;

		if (tmpRank < 0 || tmpRank >= Rank || tmpFile < 0 || tmpFile >= File)
		{
			continue;
		}

		if (Tracker[tmpRank][tmpFile] == 'X' || Tracker[tmpRank][tmpFile] == 'O')
		{
			std::cout << "You already shot there! Choose a different location.\n";
			continue;
		}

		Util::Clean();
		ProcessBombardment(Opponent, Board, Tracker, tmpRank, tmpFile);
		PrintBoard(Tracker);
		Util::Clean();
		return;
	}
}

// ------------------------------------------- Dovie'andi se tovya sagain --------------------------------------------
bool DovieAndi(const Player& Navy)
{
	for (const auto& ship : Navy.Fleet)
	{
		if (ship.Hits < ship.Length)
		{
			return false;
		}
	}
	return true;
}
