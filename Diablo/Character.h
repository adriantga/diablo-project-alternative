#pragma once
#include "Utilities.h"

class Character
{
    Diablo myDiablo = {};
    CharacterAttributes myAttributes = {};
    char* myName = nullptr;
    int myHealth = 0;
public:
    ~Character();
    Character() = default;
    Character(const Character& aOther);
    Character(Character&& aOther) noexcept;
    Character& operator=(const Character& aOther);
    Character& operator=(Character&& aOther) noexcept;
    Character(const char* aCharacterName, const Diablo& aDiablo, int aStrength = 1, int aAgility = 1, int aVitality = 1);
    CharacterAttributes GetAttributes() const { return myAttributes; }
    void SetStrength(int aStrength);
    void SetAgility(int aAgility);
    void SetVitality(int aVitality);
    void ResetHealth();
    Diablo GetDiablo() const { return myDiablo; }
    
    int GetStrength() const { return myAttributes.strength; }
    int GetAgility() const { return myAttributes.agility; }
    int GetVitality() const { return myAttributes.vitality; }
    
    int GetMaxHealth() const;
    int GetAttackValue() const;
    int GetDefense() const;
    int GetCarryCapacity() const;
    const char* GetCharacterName() const { return myName ? myName : ""; }
    int GetHealth() const { return myHealth; }
    void TakeDamage(int aDamage);
    
    bool IsAlive() const { return myHealth > 0; }
};