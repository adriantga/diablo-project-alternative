#pragma once
#include <string>
#include <iostream>
#include "Item.h"

class Spell
{
private:
    std::string myName;
    int myDuration = 0; // Number of actions / room steps remaining
    StatModifiers myModifiers;

public:
    Spell() = default;
    Spell(const std::string& aName, int aDuration, const StatModifiers& aModifiers)
        : myName(aName), myDuration(aDuration), myModifiers(aModifiers) {}

    const std::string& GetName() const { return myName; }
    int GetDuration() const { return myDuration; }
    const StatModifiers& GetModifiers() const { return myModifiers; }

    bool Tick()
    {
        if (myDuration > 0)
        {
            myDuration--;
        }
        return myDuration <= 0;
    }

    void DisplayInfo() const
    {
        std::cout << myName << " (Duration: " << myDuration << " actions) [Modifiers: ";
        myModifiers.PrintModifiers();
        std::cout << "]\n";
    }
};
