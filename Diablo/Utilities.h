#pragma once

#include <iostream>
#include <string>
#include "Helpers.h"
#include <vector>

#include "Chest.h"
#include "Spell.h"

class Character;
struct LoreItems;
struct LoreSpells;
struct LoreChests;
struct IntCasterUtility;

struct StatModifiers
{
    int strength = 0;
    int agility = 0;
    int vitality = 0;
    int attack = 0;
    int defense = 0;
    int maxHealth = 0;
    int carryCapacity = 0;
    
    StatModifiers() = default;
    
    StatModifiers(const int aStrength, const int aAgility, const int aVitality, const int aAttack = 0, const int aDefense = 0, const int aMaxHealth = 0, const int aCarryCapacity = 0) 
    : strength(aStrength), agility(aAgility), vitality(aVitality), attack(aAttack), defense(aDefense), maxHealth(aMaxHealth), carryCapacity(aCarryCapacity) {}
    
    StatModifiers Add(const StatModifiers& aOther)
    {
        strength += aOther.strength;
        agility += aOther.agility;
        vitality += aOther.vitality;
        attack += aOther.attack;
        defense += aOther.defense;
        maxHealth += aOther.maxHealth;
        carryCapacity += aOther.carryCapacity;
        return *this;
    }
    
    void PrintModifier(const int& aModifier, const char* aModifierName, bool& aFlag) const
    {
        if (aModifier != 0)
        {
            const bool hasModifier = HasExceeded(aModifier, 0);
            std::cout << (hasModifier ? "+" : "") << aModifier << " " << aModifierName << " ";
            aFlag = true;
        }
    }
    
    void PrintModifiers() const
    {
        bool hasAny = false;
        
        PrintModifier(strength, "Str", hasAny);
        PrintModifier(agility, "Agi", hasAny);
        PrintModifier(vitality, "Vit", hasAny);
        PrintModifier(attack, "DMG", hasAny);
        PrintModifier(defense, "DEF", hasAny);
        PrintModifier(maxHealth, "HP", hasAny);
        PrintModifier(carryCapacity, "Carry Cap", hasAny);
        
        if (!hasAny)
        {
            std::cout << "None";
        }
    }
};

struct CharacterAttributes
{
    int strength;
    int agility;
    int vitality;
};

struct ChestConfig
{
    int minItemCount = 1;
    int maxItemCount = 3;
};

enum class EnemyArchetype
{
    Skeleton = 0,
    Wraith = 1,
    Brawler = 2,
    Undead = 3,
    Titan = 4,
    Count = 5
};

struct Enemies
{
    static int GetType(const EnemyArchetype aEnemyType)
    {
        return static_cast<int>(aEnemyType);
    }
};

enum class RoomType
{
    EntranceRoom = 0,
    CathedralRoom = 1,
    ArmoryRoom = 2,
    KitchenRoom = 3,
    CellsRoom = 4,
};

struct Rooms
{
    static int GetRoom(RoomType aRoomType)
    {
        return static_cast<int>(aRoomType);
    }
};

enum class Color
{
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36
};

struct ConsoleColors
{
    static int GetColor(const Color aColor)
    {
        return static_cast<int>(aColor);
    }
    
    static std::string StartColor(const Color aColor, const bool aBackground = false)
    {
        const int colorResult = GetColor(aColor);
        return "\033[" + std::to_string(aBackground ? colorResult + 10 : colorResult) + 'm';
    }
    
    static std::string EndColor()
    {
        return "\033[0m";
    }
};

enum class CharacterID
{
    Player,
    Enemy
};

struct Cheats
{
    bool hasGodMode;
    bool hasOneShot;
};

enum class LineType
{
    Dash,
    EqualSign
};

enum class ItemID
{
    Item_Backpack,
    Item_TravelerBoots,
    Item_TrophyOfTheHero,
    
    Weapon_IronDagger,
    Weapon_IronSword,
    Weapon_StrangeOrb,
    
    Accessory_AgilityRing,
    Accessory_VitalityRing,
    Accessory_StrengthRing
};

enum class OptionType
{
    Move,
    PickItem,
    OpenChest,
    ReadSpell,
    ViewInventory,
    ViewStats
};

struct ActionOption
{
    OptionType type;
    int data;
    std::string text;
};

struct LoreItems
{
    // Room-specific items
    ItemID wornDagger = ItemID::Weapon_IronDagger;
    ItemID travelersBoots = ItemID::Item_TravelerBoots;
    ItemID backpack = ItemID::Item_Backpack;
    ItemID trophyOfTheHero = ItemID::Item_TrophyOfTheHero;
    
    // Items dropped by enemies
    ItemID ironDagger = ItemID::Weapon_IronDagger;
    ItemID ironSword = ItemID::Weapon_IronSword;
    ItemID strangeOrb = ItemID::Weapon_StrangeOrb;
    ItemID agilityRing = ItemID::Accessory_AgilityRing;
    ItemID vitalityRing = ItemID::Accessory_VitalityRing;
    ItemID strengthRing = ItemID::Accessory_StrengthRing;
    
    std::vector<ItemID> enemyDrops =
    {
        ironDagger,
        ironSword,
        strangeOrb,
        agilityRing,
        vitalityRing,
        strengthRing
    };
};

struct LoreChests
{
    Chest altarChest = Chest("Altar Chest");
};

struct LoreSpells
{
    Spell warCry = Spell("War Cry", 4, StatModifiers(4, 4, 4, 15, 15, 20, 0));
    Spell blessingsOfTheTraveler = Spell("Blessings of the Traveler", 3, StatModifiers(0, 6, 4, 0, 0, 0, 5));
    Spell mightOfTheWarrior = Spell("Might of The Warrior", 3, StatModifiers(0, 0, 0, 50, 50, 50, 0));
};

struct Diablo
{
    LoreItems loreItems;
    LoreSpells loreSpells;
    LoreChests loreChests;
    Cheats cheats;
};