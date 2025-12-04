#pragma once
#include <string>

namespace Util
{
    // ----------------------------------------------- Interface Functions -----------------------------------------------
    void Clear();
    void Pause();
    void Clean();

    // ----------------------------------------------- Validation Functions ----------------------------------------------
    char ValidateChar(const std::string& Prompt, const std::string& AllowedChars);
    int ValidateInt(const std::string& Prompt, char Sign);
    std::string ValidateString(const std::string& Prompt,
        const std::string& AllowedChars,
        size_t MinLength,
        size_t MaxLength,
        bool CaseSensitive,
        bool Trimming);

    // ------------------------------------------------- Misc Functions --------------------------------------------------
    bool ProgramRestart();
}