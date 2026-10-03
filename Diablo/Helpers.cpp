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
    StatModifiers mods = aCharacter.GetTotalModifiers();
    
    DrawBreakerLine(LineType::Hyphen);
    std::cout << aCharacter.GetCharacterName() << "'s Stats" << '\n';
    DrawBreakerLine(LineType::Hyphen);
    std::cout << "Strength: " << aCharacter.GetStrength() << " (Base: " << aCharacter.GetBaseStrength() << ", Mod: " << (mods.strength >= 0 ? "+" : "") << mods.strength << ")\n";
    std::cout << "Agility: " << aCharacter.GetAgility() << " (Base: " << aCharacter.GetBaseAgility() << ", Mod: " << (mods.agility >= 0 ? "+" : "") << mods.agility << ")\n";
    std::cout << "Vitality: " << aCharacter.GetVitality() << " (Base: " << aCharacter.GetBaseVitality() << ", Mod: " << (mods.vitality >= 0 ? "+" : "") << mods.vitality << ")\n";
    DrawBreakerLine(LineType::Hyphen);
    std::cout << "Damage: " << aCharacter.GetAttackValue() << " (Mod: " << (mods.attack >= 0 ? "+" : "") << mods.attack << ")\n";
    std::cout << "Defense: " << aCharacter.GetDefense() << " (Mod: " << (mods.defense >= 0 ? "+" : "") << mods.defense << ")\n";
    std::cout << "Carry Cap: " << aCharacter.GetCarryCapacity() << " (Weight: " << aCharacter.GetInventoryWeight() << "/" << aCharacter.GetCarryCapacity() << " kg)\n";
    DrawBreakerLine(LineType::Hyphen);
    std::cout << "Health: " << aCharacter.GetHealth() << " / " << maxHealth << " (Mod: " << (mods.maxHealth >= 0 ? "+" : "") << mods.maxHealth << ")\n";
    
    const auto& spells = aCharacter.GetActiveSpells();
    if (!spells.empty())
    {
        DrawBreakerLine(LineType::Hyphen);
        std::cout << "Active Spells:\n";
        for (const auto& spell : spells)
        {
            std::cout << "- ";
            spell.DisplayInfo();
        }
    }
    
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

void ShowInventory(const Character& aCharacter)
{
    DrawBreakerLine(LineType::Hyphen);
    std::cout << aCharacter.GetCharacterName() << "'s Inventory" << '\n';
    DrawBreakerLine(LineType::Hyphen);
    const auto& items = aCharacter.GetInventory();
    if (items.empty())
    {
        std::cout << "Inventory is empty.\n";
    }
    else
    {
        for (size_t i = 0; i < items.size(); ++i)
        {
            std::cout << "[" << (i + 1) << "] ";
            items[i].DisplayInfo();
        }
    }
    DrawBreakerLine(LineType::Hyphen);
    std::cout << "Total Weight: " << aCharacter.GetInventoryWeight() << " / " << aCharacter.GetCarryCapacity() << " kg\n";

    const auto& spells = aCharacter.GetActiveSpells();
    if (!spells.empty())
    {
        DrawBreakerLine(LineType::Hyphen);
        std::cout << "Active Spells:\n";
        for (const auto& spell : spells)
        {
            std::cout << "- ";
            spell.DisplayInfo();
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