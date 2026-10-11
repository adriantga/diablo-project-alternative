#include "ItemFactory.h"
#include "Helpers.h"

Item ItemFactory::CreateItem(const ItemType& aType) const
{
    return Item(aType);
}

Item ItemFactory::CreateItem(const ItemType& aType, const StatModifiers& aExtraModifiers) const
{
    return Item(aType, aExtraModifiers);
}

Item ItemFactory::CreateItem(const std::string& aName, const int aWeight, const StatModifiers& aModifiers, const ItemTypes aType) const
{
    ItemType type(aName, aWeight, aModifiers, aType);
    return Item(aName, aWeight, aModifiers);
}

Item ItemFactory::CreateWeapon(const std::string& aName, const int aWeight, const int aAttack, const int aStrength) const
{
    StatModifiers mods;
    mods.attack = aAttack;
    mods.strength = aStrength;
    ItemType weaponType(aName, aWeight, mods, ItemTypes::Sword);
    return Item(aName, aWeight, mods);
}

Item ItemFactory::CreateAccessory(const std::string& aName, const int aWeight, const StatModifiers& aModifiers, const ItemTypes aType) const
{
    ItemType accessoryType(aName, aWeight, aModifiers, aType);
    return Item(aName, aWeight, aModifiers);
}

Item ItemFactory::CreateRandomItem(const ItemConfig& aConfig, const int aTier) const
{
    const int roll = GetRandomNumber(1, 2);
    if (roll == 1)
    {
        return CreateRandomWeapon(aConfig, aTier);
    }
    return CreateRandomAccessory(aConfig, aTier);
}

Item ItemFactory::CreateRandomWeapon(const ItemConfig& aConfig, const int aTier) const
{
    std::string name = "Iron Sword";
    if (!aConfig.itemWeapon.empty())
    {
        const int index = GetRandomNumber(0, static_cast<int>(aConfig.itemWeapon.size()) - 1);
        name = aConfig.itemWeapon[index];
    }
    
    const int weight = GetRandomNumber(1, 3);
    StatModifiers mods;
    mods.attack = GetRandomNumber(1 * aTier, 3 * aTier);
    mods.strength = GetRandomNumber(0, 2 * aTier);
    
    ItemType type(name, weight, mods, ItemTypes::Sword);
    return Item(name, weight, mods);
}

Item ItemFactory::CreateRandomAccessory(const ItemConfig& aConfig, const int aTier) const
{
    std::string name = "Ring";
    if (!aConfig.itemAccessory.empty())
    {
        const int index = GetRandomNumber(0, static_cast<int>(aConfig.itemAccessory.size()) - 1);
        name = aConfig.itemAccessory[index];
    }
    
    const int weight = 1;
    StatModifiers mods;
    mods.agility = GetRandomNumber(0, 2 * aTier);
    mods.vitality = GetRandomNumber(0, 2 * aTier);
    mods.maxHealth = GetRandomNumber(5 * aTier, 15 * aTier);
    
    ItemType type(name, weight, mods, ItemTypes::Ring);
    return Item(name, weight, mods);
}

ItemType ItemFactory::CreateItemType(const std::string& aName, const int aWeight, const StatModifiers& aModifiers, const ItemTypes aType) const
{
    return ItemType(aName, aWeight, aModifiers, aType);
}
