#pragma once
#include <string>
#include <iostream>
#include "Utilities.h"

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
    StatModifiers(int aStrength, int aAgility, int aVitality, int aAttack = 0, int aDefense = 0, int aMaxHealth = 0, int aCarryCapacity = 0)
        : strength(aStrength), agility(aAgility), vitality(aVitality), attack(aAttack), defense(aDefense), maxHealth(aMaxHealth), carryCapacity(aCarryCapacity) {}

    StatModifiers& operator+=(const StatModifiers& aOther)
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

    void PrintModifiers() const
    {
        bool hasAny = false;
        if (strength != 0) { std::cout << (strength > 0 ? "+" : "") << strength << " Str "; hasAny = true; }
        if (agility != 0) { std::cout << (agility > 0 ? "+" : "") << agility << " Agi "; hasAny = true; }
        if (vitality != 0) { std::cout << (vitality > 0 ? "+" : "") << vitality << " Vit "; hasAny = true; }
        if (attack != 0) { std::cout << (attack > 0 ? "+" : "") << attack << " Dmg "; hasAny = true; }
        if (defense != 0) { std::cout << (defense > 0 ? "+" : "") << defense << " Def "; hasAny = true; }
        if (maxHealth != 0) { std::cout << (maxHealth > 0 ? "+" : "") << maxHealth << " HP "; hasAny = true; }
        if (carryCapacity != 0) { std::cout << (carryCapacity > 0 ? "+" : "") << carryCapacity << " Carry "; hasAny = true; }
        if (!hasAny)
        {
            std::cout << "None";
        }
    }
};

class Item
{
private:
    std::string myName;
    int myWeight = 0;
    StatModifiers myModifiers;

public:
    Item() = default;
    Item(const std::string& aName, int aWeight, const StatModifiers& aModifiers)
        : myName(aName), myWeight(aWeight), myModifiers(aModifiers) {}

    const std::string& GetName() const { return myName; }
    int GetWeight() const { return myWeight; }
    const StatModifiers& GetModifiers() const { return myModifiers; }

    void DisplayInfo() const
    {
        std::cout << myName << " (Weight: " << myWeight << " kg) [Modifiers: ";
        myModifiers.PrintModifiers();
        std::cout << "]\n";
    }
};
