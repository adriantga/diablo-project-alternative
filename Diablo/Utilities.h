#pragma once
#include <string>
#include <vector>

class Character;

struct CharacterAttributes
{
    int strength;
    int agility;
    int vitality;
};

enum class LineType
{
    EqualSign,
    Hyphen
};

struct ConsoleColors
{
    static constexpr int BLACK = 30;
    static constexpr int RED = 31;
    static constexpr int GREEN = 32;
    static constexpr int YELLOW = 33;
    static constexpr int BLUE = 34;
    static constexpr int MAGENTA = 35;
    static constexpr int CYAN = 36;
    static constexpr int WHITE = 37;
    
    static std::string StartColor(int aColor, bool aBackground = false)
    {
        return "\033[" + std::to_string((aBackground ? aColor + 10 : aColor)) + 'm';
    }
    
    static std::string EndColor()
    {
        return "\033[0m";
    }
};

struct Cheats
{
    bool hasGodMode;
    bool hasOneShot;
};

struct Diablo
{
    Cheats cheats;
};
