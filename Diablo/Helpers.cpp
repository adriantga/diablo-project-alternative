#include "Helpers.h"

#include <random>

#include "Character.h"

namespace 
{
    std::random_device globalRnd;
    std::mt19937 globalRndEngine(globalRnd());  // NOLINT(bugprone-throwing-static-initialization)
    
    bool HasCheatsEnabled(const Diablo& aDiablo)
    {
        return aDiablo.cheats.hasGodMode || aDiablo.cheats.hasOneShot;
    }
    
    void RemindRange(const int aMin, const int aMax)
    {
        const bool isMinMax = aMin == aMax;
        if (isMinMax)
        {
            std::cout << "Please enter " << aMin << ":\n";
        }
        else
        {
            std::cout << "Please enter a number(" << aMin << " - " << aMax << "):\n";
        }
    }
    
    void DoCommand(const char* aCommand)
    {
        system(aCommand);  // NOLINT(bugprone-command-processor)
    }
}

int GetRandomNumber(const int aMin, const int aMax)
{
    const bool isMinGreater = HasExceeded(aMin, aMax);
    const int min = isMinGreater ? aMax : aMin;
    const int max = isMinGreater ? aMin : aMax;
    std::uniform_int_distribution<int> dist(min, max);
    return dist(globalRndEngine);
}

bool HasSubceeded(const int aSource, const int aValue)
{
    return aSource < aValue;
}

bool HasExceeded(const int aSource, const int aValue)
{
    return aSource > aValue;
}

int Min(const int aSource, const int aMin)
{
    return HasSubceeded(aSource, aMin) ? aMin : aSource;
}

int Max(const int aSource, const int aMax)
{
    return HasExceeded(aSource, aMax) ? aMax : aSource;
}

void ShowInventory(const Character& aCharacter)
{
    DrawBreakerLine(LineType::Dash);
    std::cout << aCharacter.GetCharacterName() << "'s Inventory\n";
    DrawBreakerLine(LineType::Dash);
    const std::vector<Item>& items = aCharacter.GetInventory();
    if (items.empty())
    {
        WriteLine("The inventory is empty!");
    }
    else
    {
        for (size_t i = 0; i < items.size(); ++i)
        {
            std::cout << "[" << (i + 1) << "] ";
            items[i].DisplayInfo();
        }
    }
    
    DrawBreakerLine(LineType::Dash);
    std::cout << "Total Weight: " << aCharacter.GetInventoryWeight() << " / " << aCharacter.GetCarryCapacity() << " kg\n";

    const std::vector<Spell>& spells = aCharacter.GetActiveSpells();
    if (!spells.empty())
    {
        DrawBreakerLine(LineType::Dash);
        WriteLine("Active Spells");
        for (const Spell& spell : spells)
        {
            std::cout << "-";
            spell.DisplayInfo();
        }
    }
}

void ShowStats(const Character& aCharacter, const Diablo& aDiablo)
{
    const int maxHealth = aCharacter.GetMaxHealth();
    
    DrawBreakerLine(LineType::Dash);
    std::cout << aCharacter.GetCharacterName() << "'s Stats\n"; 
    DrawBreakerLine(LineType::Dash);

    std::cout << "Strength: " << aCharacter.GetStrength() << '\n';
    std::cout << "Agility: " << aCharacter.GetAgility() << '\n';
    std::cout << "Vitality: " << aCharacter.GetVitality() << '\n';
    DrawBreakerLine(LineType::Dash);
    std::cout << "Max Health: " << maxHealth << '\n';
    std::cout << "Damage: " << aCharacter.GetAttackValue() << '\n';
    std::cout << "Defense: " << aCharacter.GetDefense() << '\n';
    std::cout << "Carry Cap: " << aCharacter.GetCarryCapacity() << '\n';
    std::cout << "Health: " << aCharacter.GetHealth() << '/' << maxHealth << '\n';
    
    if (HasCheatsEnabled(aDiablo))
    {
        DrawBreakerLine(LineType::Dash);

        if (aDiablo.cheats.hasGodMode)
        {
            std::cout << ConsoleColors::StartColor(Color::Yellow) << "God Mode Enabled" << ConsoleColors::EndColor() << '\n';
        }
    
        if (aDiablo.cheats.hasOneShot)
        {
            std::cout << ConsoleColors::StartColor(Color::Yellow) << "One-Shot Enabled" << ConsoleColors::EndColor() << '\n';
        }
    }
}

int CalculateDamage(const Character& aSource, const Character& aTarget)
{
    int result = aSource.GetAttackValue() - aTarget.GetDefense();
    result = Min(result, 1);
    return result;
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

void ForceInput(int& aInput, const int aMin, const int aMax)
{
    const bool hasLimit = aMin != -1 && aMax != -1;
    if (!hasLimit)
    {
        std::cout << ConsoleColors::StartColor(Color::Red) << "Invalid input. The input has no range!\n" << ConsoleColors::EndColor();
        return;
    }
    
    bool isInRange = !HasSubceeded(aInput, aMin) && !HasExceeded(aInput, aMax);
    while (!isInRange)
    {
        RemindRange(aMin, aMax);

        while (std::cin.fail())
        {
            ClearInput();
            std::cin >> aInput;
        }
        
        std::cin >> aInput;
        isInRange = !HasSubceeded(aInput, aMin) && !HasExceeded(aInput, aMax);
    }
}

/*
 * In the future I shall combine these two and replace them with a 'DrawLine' method.
 * I don't have time to do that now, so I'll try to get it done for 4.3!
 */
void DrawMenuLine(LineType aLineType)
{
    switch (aLineType)
    {
    case LineType::EqualSign:
        WriteLine("======================================================================================");
        break;
    case LineType::Dash:
        WriteLine("--------------------------------------------------------------------------------------");
        break;
    }
}

void ClearInput()
{
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

void DrawBreakerLine(LineType aLineType)
{
    switch (aLineType)
    {
    case LineType::EqualSign:
        WriteLine("========================================================");
        break;
    case LineType::Dash:
        WriteLine("--------------------------------------------------------");
        break;
    }
}