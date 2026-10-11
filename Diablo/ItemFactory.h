#pragma once

#include <string>
#include "Item.h"
#include "ItemType.h"
#include "Utilities.h"

class ItemFactory
{
public:
    ItemFactory() = default;
    
    Item CreateItem(const ItemType& aType) const;
    Item CreateItem(const ItemType& aType, const StatModifiers& aExtraModifiers) const;
    Item CreateItem(const std::string& aName, int aWeight, const StatModifiers& aModifiers, ItemTypes aType = ItemTypes::Dagger) const;
    
    Item CreateWeapon(const std::string& aName, int aWeight, int aAttack, int aStrength = 0) const;
    Item CreateAccessory(const std::string& aName, int aWeight, const StatModifiers& aModifiers, ItemTypes aType = ItemTypes::Ring) const;
    
    Item CreateRandomItem(const ItemConfig& aConfig, int aTier = 1) const;
    Item CreateRandomWeapon(const ItemConfig& aConfig, int aTier = 1) const;
    Item CreateRandomAccessory(const ItemConfig& aConfig, int aTier = 1) const;
    
    ItemType CreateItemType(const std::string& aName, int aWeight, const StatModifiers& aModifiers, ItemTypes aType = ItemTypes::Dagger) const;
};
