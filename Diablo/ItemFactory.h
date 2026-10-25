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
    void SetupItem(ItemID aType, const std::string& aName, int aWeight, const StatModifiers& aModifiers);
    
public:
    ItemFactory();
    void Init();
    Item CreateItem(ItemID aType) const;
};