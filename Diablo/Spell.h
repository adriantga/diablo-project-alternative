#pragma once
#include <string>

#include "Helpers.h"

struct StatModifiers;

class Spell
{
    std::string myName;
    int myDuration = 0;
    StatModifiers* myModifiers;
public:
    Spell() = default;
    Spell(const std::string& aName, int aDuration, const StatModifiers& aModifiers);
    const std::string& GetName() const { return myName; }
    int GetDuration() const { return myDuration; }
    const StatModifiers& GetModifiers() const { return *myModifiers; }
    
    bool Tick()
    {
        if (HasExceeded(myDuration, 0))
        {
            myDuration--;
        }
        
        return myDuration <= 0;
    }
    
    void DisplayInfo() const;
};