#include "Helpers.h"

#include <iostream>

#include "Utilities.h"

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
        std::cout << ConsoleColors::GetColor(ConsoleColors::RED, false) << "Input is not limited\n";
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