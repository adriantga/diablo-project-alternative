#pragma once

#include <string>
#include "Utilities.h"

class ItemType
{
    std::string myName;
    int myWeight = 0;
    StatModifiers myModifiers;
    ItemTypes myItemType = ItemTypes::Dagger;
    
public:
    ItemType() = default;
    ItemType(const std::string& aName, int aWeight, const StatModifiers& aModifiers, ItemTypes aType = ItemTypes::Dagger);
    
    const std::string& GetName() const { return myName; }
    int GetWeight() const { return myWeight; }
    const StatModifiers& GetModifiers() const { return myModifiers; }
    ItemTypes GetItemType() const { return myItemType; }
};
