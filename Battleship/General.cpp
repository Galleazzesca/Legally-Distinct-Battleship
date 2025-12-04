#pragma once
#include "General.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

namespace Util
{
    // ----------------------------------------------- Interface Functions -----------------------------------------------
    void Clear()
    {
#ifdef _WIN32
        system("cls"); // Windows
#else
        std::cout << "\033[2J\033[1;1H"; // Linux/macOS (\033[2J is a screen clear while \033[1;1H moves the cursor back to the top-left)
#endif
    }
    void Pause()
    {
        std::cout << "Press enter to continue.\n";
        std::cin.clear();
        if (std::cin.rdbuf()->in_avail() > 0)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.get(); // Only proceeds when enter is inputted
    }
    void Clean()
    {
        Pause();
        Clear();
    }

    // ----------------------------------------------- Validation Functions ----------------------------------------------
    char ValidateChar(const std::string& Prompt = "", const std::string& AllowedChars = "")
    {
        std::string InputLine;

        while (true)
        {
            if (!Prompt.empty())
            {
                std::cout << Prompt;
            }

            std::getline(std::cin, InputLine);

            if (InputLine.length() == 1)
            {
                std::transform(InputLine.begin(), InputLine.end(), InputLine.begin(), ::tolower);

                char val = InputLine[0];

                if (!AllowedChars.empty() && AllowedChars.find(val) == std::string::npos)
                {
                    std::cout << "Invalid input. The allowed characters are " << AllowedChars << "\n";
                    continue;
                }
                return val;
            }

            else
            {
                std::cout << "Invalid Input. Please input a single character.\n";
            }
        }
    }
    int ValidateInt(const std::string& Prompt = "", char Sign = 0)
    {
        std::string InputLine;

        while (true)
        {
            if (!Prompt.empty())
            {
                std::cout << Prompt;
            }

            std::getline(std::cin, InputLine);

            std::stringstream ss(InputLine);
            int val;

            if (ss >> val && ss.eof()) // eof checks if there are no more leftover characters
            {
                if (Sign == '-' && val >= 0)
                {
                    std::cout << "Invalid Input. Please input a negative integer.\n";
                    continue;
                }

                if (Sign == '+' && val <= 0)
                {
                    std::cout << "Invalid Input. Please input a positive integer.\n";
                    continue;
                }

                return val;
            }

            else
            {
                std::cout << "Invalid Input. Please input an integer.\n";
            }
        }
    }
    std::string ValidateString(const std::string& Prompt = "",
        const std::string& AllowedChars = "",
        size_t MinLength = 1,
        size_t MaxLength = 100,
        bool CaseSensitive = true,
        bool Trimming = true)
    {
        if (MinLength > MaxLength)
        {
            std::swap(MinLength, MaxLength);
        }

        std::string InputLine;

        while (true)
        {
            if (!Prompt.empty())
            {
                std::cout << Prompt;

                if (!Trimming)
                {
                    std::cout << "Keep in mind that both leading and trailing spaces will be included.";
                }
            }

            std::getline(std::cin, InputLine);

            if (Trimming)
            {
                size_t first = InputLine.find_first_not_of(" \t\n\r");
                size_t last = InputLine.find_last_not_of(" \t\n\r");

                if (first == std::string::npos)
                {
                    InputLine.clear();
                }

                else
                {
                    InputLine.erase(last + 1);   // remove everything after the last good character
                    InputLine.erase(0, first);   // remove everything before the first good character
                }
            }

            if (InputLine.length() < MinLength)
            {
                std::cout << "Invalid input. Please ensure that your input is at least " << MinLength << " characters long.\n"
                    << "Your input is currently " << InputLine.length() << " characters long.\n"
                    << "You must add " << MinLength - InputLine.length() << " characters.\n";
                continue;
            }

            if (InputLine.length() > MaxLength)
            {
                std::cout << "Invalid input. Please ensure that your input does not exceed " << MaxLength << " characters.\n"
                    << "Your input is currently " << InputLine.length() << " characters long.\n"
                    << "You must remove " << InputLine.length() - MaxLength << " characters.\n";
                continue;
            }

            if (!AllowedChars.empty())
            {
                bool invalidChar = false;
                for (char c : InputLine)
                {
                    char checkChar = c;
                    if (!CaseSensitive)
                    {
                        checkChar = std::tolower(static_cast<unsigned char>(c));
                    }
                    if (AllowedChars.find(checkChar) == std::string::npos)
                    {
                        invalidChar = true;
                        std::cout << "Invalid input. '" << c << "' is not an allowed character.\n"
                            << "The allowed characters are " << AllowedChars << ".\n";
                        break;
                    }
                }
                if (invalidChar)
                {
                    continue; // go back to the start of the while loop
                }
            }

            return InputLine;
        }
    }

    // ------------------------------------------------- Misc Functions --------------------------------------------------
    bool ProgramRestart()
    {
        Pause();
        Clear();

        char Input = Util::ValidateChar("Would you like to run the program again?\n1. Yes\n2. No\n", "12");

        if (Input == '1')
        {
            Clear();
            return true;
        }

        else
        {
            return false;
        }
    }
}