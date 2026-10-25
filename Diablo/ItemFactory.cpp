#include "ItemFactory.h"
#include "Helpers.h"

ItemFactory::ItemFactory()
{
    Init();
}

const char* ItemFactory::GetItemName(const ItemID aType)
{
    switch (aType)
    {
    case ItemID::Item_Backpack:         
        return "Backpack";
    case ItemID::Item_TravelerBoots:    
        return "Traveler's Boots";
    case ItemID::Item_TrophyOfTheHero:   
        return "Trophy of the Hero";
    case ItemID::Weapon_IronDagger:     
        return "Iron Dagger";
    case ItemID::Weapon_IronSword:       
        return "Iron Sword";
    case ItemID::Weapon_StrangeOrb:     
        return "Strange Orb";
    case ItemID::Accessory_AgilityRing:  
        return "Agility Ring";
    case ItemID::Accessory_VitalityRing: 
        return "Vitality Ring";
    case ItemID::Accessory_StrengthRing: 
        return "Strength Ring";
    default:                            
        return "Unknown";
    }
}

void ItemFactory::SetupItem(const ItemID aType, const std::string& aName, const int aWeight, const StatModifiers& aModifiers)
{
    const int index = static_cast<int>(aType);
    if (index < 0 || index >= ITEM_TYPE_COUNT)
    {
        return;
    }

    myItemTypes[index] = ItemType(aName, aWeight, aModifiers, aType);
}

void ItemFactory::Init()
{
    SetupItem(ItemID::Item_Backpack, "Backpack", 1, StatModifiers(0, 0, 0, 0, 0, 0, 10));
    SetupItem(ItemID::Item_TravelerBoots, "Traveler's Boots", 1, StatModifiers(0, 1, 0, 0, 1, 0, 0));
    SetupItem(ItemID::Item_TrophyOfTheHero, "Trophy of the Hero", 10, StatModifiers(10, 10, 10, 20, 20, 20, 0));
    SetupItem(ItemID::Weapon_IronDagger, "Iron Dagger", 1, StatModifiers(1, 0, 0, 2, 0, 0, 0));
    SetupItem(ItemID::Weapon_IronSword, "Iron Sword", 1, StatModifiers(2, 0, 0, 4, 0, 0, 0));
    SetupItem(ItemID::Weapon_StrangeOrb, "Strange Orb", 4, StatModifiers(3, 0, 3, 0, 3, 0, 0));
    SetupItem(ItemID::Accessory_AgilityRing, "Agility Ring", 5, StatModifiers(0, 2, 0, 0, 25, 0, 0));
    SetupItem(ItemID::Accessory_VitalityRing, "Vitality Ring", 5, StatModifiers(0, 0, 2, 0, 0, 25, 0));
    SetupItem(ItemID::Accessory_StrengthRing, "Strength Ring", 5, StatModifiers(2, 0, 0, 25, 0, 0, 0));
}

Item ItemFactory::CreateItem(const ItemID aType) const
{
    const int index = static_cast<int>(aType);
    if (index >= 0 && index < ITEM_TYPE_COUNT)
    {
        return Item(myItemTypes[index]);
    }
    
    return Item();
}

Item ItemFactory::CreateItem(const ItemType& aType) const
{
    return Item(aType);
}

Item ItemFactory::CreateItem(const ItemType& aType, const StatModifiers& aExtraModifiers) const
{
    return Item(aType, aExtraModifiers);
}

Item ItemFactory::CreateItem(const std::string& aName, const int aWeight, const StatModifiers& aModifiers, const ItemID aType) const
{
    ItemType type(aName, aWeight, aModifiers, aType);
    return Item(aName, aWeight, aModifiers);
}

Item ItemFactory::CreateWeapon(const std::string& aName, const int aWeight, const int aAttack, const int aStrength) const
{
    StatModifiers mods;
    mods.attack = aAttack;
    mods.strength = aStrength;
    ItemType weaponType(aName, aWeight, mods, ItemID::Weapon_IronSword);
    return Item(aName, aWeight, mods);
}

Item ItemFactory::CreateAccessory(const std::string& aName, const int aWeight, const StatModifiers& aModifiers, const ItemID aType) const
{
    ItemType accessoryType(aName, aWeight, aModifiers, aType);
    return Item(aName, aWeight, aModifiers);
}

ItemType ItemFactory::CreateItemType(const std::string& aName, const int aWeight, const StatModifiers& aModifiers, const ItemID aType) const
{
    return ItemType(aName, aWeight, aModifiers, aType);
}