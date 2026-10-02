#include "Helpers.h"

#include <iostream>
#include <random>


#include "Utilities.h"

namespace
{
    std::random_device globalSeed;
    std::mt19937 globalGenerator(globalSeed());  // NOLINT(bugprone-throwing-static-initialization)
}

int GetRandomNumber(const int aMin, const int aMax)
{
    if (aMin > aMax)
    {
        std::uniform_int_distribution<> distribution(aMax, aMin);
        return distribution(globalGenerator);
    }
    std::uniform_int_distribution<> distribution(aMin, aMax);
    return distribution(globalGenerator);
}

bool HasSubceeded(int aSource, int aValue)
{
    return aSource < aValue;
}

bool HasExceeded(int aSource, int aValue)
{
    return aSource > aValue;
}

int Min(int aValue, int aMin)
{
    return HasSubceeded(aValue, aMin) ? aMin : aValue;
}

int Max(int aValue, int aMax)
{
    return HasExceeded(aValue, aMax) ? aMax : aValue;
}

int Clamp(int aValue, int aMin, int aMax)
{
    return Min(Max(aValue, aMin), aMax);
}

static bool HasCheatsEnabled(const Diablo& aDiablo) { return aDiablo.cheats.hasGodMode || aDiablo.cheats.hasOneShot; }

void ShowStats(const Character& aCharacter, const Diablo& aDiablo)
{
    int maxHealth = aCharacter.GetMaxHealth();
    
    DrawBreakerLine(LineType::Hyphen);
    std::cout << aCharacter.GetCharacterName() << "'s Stats" << '\n';
    DrawBreakerLine(LineType::Hyphen);
    std::cout << "Strength: " << aCharacter.GetStrength() << "\n";
    std::cout << "Agility: " << aCharacter.GetAgility() << "\n";
    std::cout << "Vitality: " << aCharacter.GetVitality() << "\n";
    DrawBreakerLine(LineType::Hyphen);
    std::cout << "Damage: " << aCharacter.GetAttackValue() << '\n';
    std::cout << "Defense: " << aCharacter.GetDefense() << '\n';
    std::cout << "Carry Cap: " << aCharacter.GetCarryCapacity() << '\n';
    DrawBreakerLine(LineType::Hyphen);
    std::cout << "Health: " << aCharacter.GetHealth() << " / " << maxHealth << '\n';
    
    if (HasCheatsEnabled(aDiablo))
    {
        DrawBreakerLine(LineType::Hyphen);

        if (aDiablo.cheats.hasGodMode)
        {
            std::cout << ConsoleColors::StartColor(ConsoleColors::YELLOW) << "God Mode Enabled" << ConsoleColors::EndColor() << '\n';
        }
    
        if (aDiablo.cheats.hasOneShot)
        {
            std::cout << ConsoleColors::StartColor(ConsoleColors::YELLOW) << "One-Shot Enabled" << ConsoleColors::EndColor() << '\n';
        }
    }
}

int CalculateDamage(const Character& aSource, const Character& aTarget)
{
    int result = aSource.GetAttackValue() - aTarget.GetDefense();
    result = Min(result, 0);
    return result;
}

void DoCommand(const char* aCommand)
{
    system(aCommand);
}

void Exit()
{
    DoCommand("exit");
}

void RemindPlayerOfRange(int aMin, int aMax)
{
    bool isMinMax = aMin == aMax;
    if (isMinMax)
    {
        std::cout << "Please enter " << aMin << ":\n";
    }
    else
    {
        std::cout << "Please enter a number(" << aMin << " - " << aMax << "):\n";
    }
}

void ForceInput(int& aInput, int aMin, int aMax)
{
    bool hasLimit = aMin != -1 && aMax != -1;
    if (!hasLimit)
    {
        std::cout << ConsoleColors::StartColor(ConsoleColors::RED, false) << "Input is not limited\n";
        return;
    }
    
    bool isInRange = !HasSubceeded(aInput, aMin) && !HasExceeded(aInput, aMax);
    while (!isInRange)
    {
        RemindPlayerOfRange(aMin, aMax);
        
        while (std::cin.fail())
        {
            ClearInput();
            std::cin >> aInput;
        }
        
        std::cin >> aInput;
        isInRange = !HasSubceeded(aInput, aMin) && !HasExceeded(aInput, aMax);
    }
    
    ClearInput();
}

void ClearScreen()
{
    DoCommand("cls");
}

void Pause()
{
    DoCommand("pause");
}

void WriteLine(const char* aText, bool aNewLine)
{
    std::cout << aText << (aNewLine ? '\n' : '\0');
}

void ClearInput()
{
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

void DrawMenuLine(LineType aMenuLineType)
{
    switch (aMenuLineType)
    {
    case LineType::EqualSign:
        std::cout << "====================================================" << '\n';
        break;
    case LineType::Hyphen:
        std::cout << "----------------------------------------------------" << '\n';
        break;
    }
}

void DrawBreakerLine(LineType aBreakerLineType)
{
    switch (aBreakerLineType)
    {
    case LineType::EqualSign:
        std::cout << "=======================================================================" << '\n';
        break;
    case LineType::Hyphen:
        std::cout << "-----------------------------------------------------------------------" << '\n';
        break;
    }
}