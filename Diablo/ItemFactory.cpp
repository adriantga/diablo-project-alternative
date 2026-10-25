#include "ItemFactory.h"

ItemFactory::ItemFactory()
{
    Init();
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