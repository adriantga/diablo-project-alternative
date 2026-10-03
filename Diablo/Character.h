#pragma once
#include <vector>
#include "Utilities.h"
#include "Item.h"
#include "Spell.h"

class Character
{
    Diablo myDiablo = {};
    CharacterAttributes myAttributes = {};
    char* myName = nullptr;
    int myHealth = 0;
    std::vector<Item> myInventory = {};
    std::vector<Spell> myActiveSpells = {};
public:
    ~Character();
    Character() = default;
    Character(const Character& aOther);
    Character(Character&& aOther) noexcept;
    Character& operator=(const Character& aOther);
    Character& operator=(Character&& aOther) noexcept;
    Character(const char* aCharacterName, const Diablo& aDiablo, int aStrength = 1, int aAgility = 1, int aVitality = 1);
    CharacterAttributes GetBaseAttributes() const { return myAttributes; }
    CharacterAttributes GetAttributes() const;
    StatModifiers GetTotalModifiers() const;
    void SetStrength(int aStrength);
    void SetAgility(int aAgility);
    void SetVitality(int aVitality);
    void ResetHealth();
    void SetDiablo(const Diablo& aDiablo) { myDiablo = aDiablo; }
    Diablo GetDiablo() const { return myDiablo; }
    
    int GetBaseStrength() const { return myAttributes.strength; }
    int GetBaseAgility() const { return myAttributes.agility; }
    int GetBaseVitality() const { return myAttributes.vitality; }

    int GetStrength() const;
    int GetAgility() const;
    int GetVitality() const;
    
    int GetMaxHealth() const;
    int GetAttackValue() const;
    int GetDefense() const;
    int GetCarryCapacity() const;
    int GetInventoryWeight() const;
    bool CanCarry(int aWeight) const;

    bool AddItem(const Item& aItem);
    void AddSpell(const Spell& aSpell);
    void TickSpells();

    const std::vector<Item>& GetInventory() const { return myInventory; }
    std::vector<Item>& GetInventory() { return myInventory; }
    const std::vector<Spell>& GetActiveSpells() const { return myActiveSpells; }

    const char* GetCharacterName() const { return myName ? myName : ""; }
    int GetHealth() const { return myHealth; }
    void SetHealth(int aHealth) { myHealth = aHealth; }
    void TakeDamage(int aDamage);
    
    bool IsAlive() const { return myHealth > 0; }
};