#pragma once

#include <string>
#include "Item.h"
#include "ItemType.h"
#include "Utilities.h"

class ItemFactory
{
public:
    static constexpr int ITEM_TYPE_COUNT = 9;

private:
    ItemType myItemTypes[ITEM_TYPE_COUNT];

public:
    ItemFactory();
    
    void Init();
    void SetupItem(ItemID aType, const std::string& aName, int aWeight, const StatModifiers& aModifiers);
    
    Item CreateItem(ItemID aType) const;
    Item CreateItem(const ItemType& aType) const;
    Item CreateItem(const ItemType& aType, const StatModifiers& aExtraModifiers) const;
    Item CreateItem(const std::string& aName, int aWeight, const StatModifiers& aModifiers, ItemID aType = ItemID::Weapon_IronDagger) const;
    
    Item CreateWeapon(const std::string& aName, int aWeight, int aAttack, int aStrength = 0) const;
    Item CreateAccessory(const std::string& aName, int aWeight, const StatModifiers& aModifiers, ItemID aType = ItemID::Accessory_AgilityRing) const;
    
    ItemType CreateItemType(const std::string& aName, int aWeight, const StatModifiers& aModifiers, ItemID aType = ItemID::Weapon_IronDagger) const;
    static const char* GetItemName(ItemID aType);
};