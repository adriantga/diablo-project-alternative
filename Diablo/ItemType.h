#pragma once

#include <string>
#include "Utilities.h"

class ItemType
{
    std::string myName;
    int myWeight = 0;
    StatModifiers myModifiers;
    ItemID myItemType = ItemID::Weapon_IronDagger;
    
public:
    ItemType() = default;
    ItemType(const std::string& aName, int aWeight, const StatModifiers& aModifiers, ItemID aType = ItemID::Weapon_IronDagger);
    
    const std::string& GetName() const { return myName; }
    int GetWeight() const { return myWeight; }
    const StatModifiers& GetModifiers() const { return myModifiers; }
    ItemID GetItemType() const { return myItemType; }
};