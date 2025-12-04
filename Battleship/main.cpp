#include <iostream>
#include "General.h"
#include "Board.h"
#include "Ship.h"

int main()
{
    while (true)
    {
        // -------------------------------------------------- Introduction ---------------------------------------------------
        std::cout << "Welcome to Shipbattles! A game totally distinct from Battleship, and most definitly not a rip-off.\n";
        Util::Clean();

        // ----------------------------------------------------- Set-up ------------------------------------------------------
        Player Alpha;
        Player Beta;

        Alpha.Name = Util::ValidateString("What is your name Player 1?\n", "", 1, 20, false, true);
        Beta.Name = Util::ValidateString("What about your name Player 2?\n", "", 1, 20, false, true);
        Util::Clean();

        SetupFleet(BoardAlpha, Alpha);
        SetupFleet(BoardBeta, Beta);

        // ---------------------------------------------------- Gameplay -----------------------------------------------------
        SetBoard(TrackerAlpha);
        SetBoard(TrackerBeta);

        while (true)
        {
            OrderBombardment(Beta, BoardBeta, TrackerAlpha);
            if (DovieAndi(Beta))
            {
                std::cout << "Congratulations " << Alpha.Name << "! You won legally distinct Battleship!\n";
                break;
            }
            Util::Clean();

            OrderBombardment(Alpha, BoardAlpha, TrackerBeta);
            if (DovieAndi(Alpha))
            {
                std::cout << "Congratulations " << Beta.Name << "! You won legally distinct Battleship!\n";
                break;
            }
            Util::Clean();
        }

        if (!Util::ProgramRestart())
        {
            break;
        }
    }
    return 0;
}