#include "Spell.h"
#include "Utilities.h"

Spell::Spell(const std::string& aName, int aDuration, const StatModifiers& aModifiers) : 
    myName(aName), myDuration(aDuration), myModifiers(new StatModifiers(aModifiers))
{
    
}

void Spell::DisplayInfo() const
{
    std::cout << myName << " (Duration: " << myDuration << ") [Modifiers ";
    myModifiers->PrintModifiers();
    std::cout << "\n";
}