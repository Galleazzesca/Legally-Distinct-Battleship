#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <random>
#include <algorithm>
#include <sstream>

// All utility functions are inside the Util namespace
namespace Util
{
    // Clear:
    // Clears the console screen.
    // Uses system("cls") on Windows, ANSI escape codes on Linux/macOS.
    inline void Clear()
    {
#ifdef _WIN32
        system("cls"); // Windows
#else
        std::cout << "\033[2J\033[1;1H"; // Linux/macOS (\033[2J is a screen clear while \033[1;1H moves the cursor back to the top-left)
#endif
    }

    // Pause:
    // Pauses the program and waits until the user presses Enter.
    // Removes a newline if one is already there.
    inline void Pause()
    {
        std::cout << "Press enter to continue.\n";
        std::cin.clear();
        if (std::cin.rdbuf()->in_avail() > 0)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.get(); // Only proceeds when enter is inputted
    }

    // ValidateChar:
    // Prompts the user to input a single character and validates it.
    // Keeps asking until the input is valid.
    // Input is case-insensitive and filterable.
    // AllowedChars must be lowercase
    inline char ValidateChar(const std::string& Prompt = "", const std::string& AllowedChars = "")
    {
        if (std::cin.rdbuf()->in_avail() > 0)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

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

    // ValidateDouble:
    // Prompts the user to input a single double and validates it.
    // The sign of a valid input can be specified.
    // Keeps asking until the input is valid.
    inline double ValidateDouble(const std::string& Prompt = "", char Sign = 0)
    {
        if (std::cin.rdbuf()->in_avail() > 0)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::string InputLine;

        while (true)
        {
            if (!Prompt.empty())
            {
                std::cout << Prompt;
            }

            std::getline(std::cin, InputLine);

            std::stringstream ss(InputLine);
            double val;

            if (ss >> val && ss.eof()) // eof checks if there are no more leftover characters
            {
                if (Sign == '-' && val >= 0)
                {
                    std::cout << "Invalid Input. Please input a negative decimal value.\n";
                    continue;
                }

                if (Sign == '+' && val <= 0)
                {
                    std::cout << "Invalid Input. Please input a positive decimal value.\n";
                    continue;
                }

                return val;
            }

            else
            {
                std::cout << "Invalid Input. Please input a decimal value.\n";
            }
        }
    }

    // ValidateFloat:
    // Prompts the user to input a single float and validates it.
    // The sign of a valid input can be specified.
    // Keeps asking until the input is valid.
    inline float ValidateFloat(const std::string& Prompt = "", char Sign = 0)
    {
        if (std::cin.rdbuf()->in_avail() > 0)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::string InputLine;

        while (true)
        {
            if (!Prompt.empty())
            {
                std::cout << Prompt;
            }

            std::getline(std::cin, InputLine);

            std::stringstream ss(InputLine);
            float val;

            if (ss >> val && ss.eof()) // eof checks if there are no more leftover characters
            {
                if (Sign == '-' && val >= 0)
                {
                    std::cout << "Invalid Input. Please input a negative decimal value.\n";
                    continue;
                }

                if (Sign == '+' && val <= 0)
                {
                    std::cout << "Invalid Input. Please input a positive decimal value.\n";
                    continue;
                }

                return val;
            }

            else
            {
                std::cout << "Invalid Input. Please input a decimal value.\n";
            }
        }
    }

    // ValidateInt:
    // Prompts the user to input a single integer and validates it.
    // The sign of a valid input can be specified.
    // Keeps asking until the input is valid.
    inline int ValidateInt(const std::string& Prompt = "", char Sign = 0)
    {
        if (std::cin.rdbuf()->in_avail() > 0)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

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

    // ValidateString:
    // Prompts the user to input a string and validates it.
    // The length of a valid input can be restricted.
    // The input is filterable and has toggleable case-sensitivity.
    // Capable of removing whitespace.
    // If case-insensitive AllowedChars must be lowercase.
    inline std::string ValidateString(const std::string& Prompt = "", const std::string& AllowedChars = "",
        size_t MinLength = 1, size_t MaxLength = std::numeric_limits<size_t>::max(),
        bool CaseSensitive = true, bool Trimming = true)
    {
        if (std::cin.rdbuf()->in_avail() > 0)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

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

    // ProgramRestart:
    // Asks the user if they want to restart the program.
    // Returns true if yes, false if no.
    inline bool ProgramRestart()
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

    // RollDie:
    // Generates a random number between 1 and an integer specified within the code.
    // Default: 6 faces (D6)
    inline int RollDie(int Faces = 6)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());

        if (Faces <= 0)
        {
            std::cout << "Invalid number of faces.\n";
            return 0;
        }

        std::uniform_int_distribution<> dist(1, Faces);
        return dist(gen);
    }

    // GenerateRandomNumber:
    // Generates a random number within a range specified by the user.
    inline int GenerateRandomNumber()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());

        int Min, Max;
        while (true)
        {
            Min = ValidateInt("What is the minimum?\n");
            Max = ValidateInt("What is the maximum?\n");

            if (Min > Max)
            {
                std::cout << "The minimum cannot be greater than the maximum.\nPlease try again\n";
            }

            else
            {
                break;
            }
        }

        std::uniform_int_distribution<> dist(Min, Max);
        return dist(gen);
    }
}


#endif // UTILITIES_H