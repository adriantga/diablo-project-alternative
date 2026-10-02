#pragma once
#include "Utilities.h"

class Character
{
    CharacterAttributes myAttributes = {};
    char* myName;
    int myHealth;
public:
    ~Character();
    Character(const char* aCharacterName, int aStrength = 1, int aAgility = 1, int aVitality = 1);
    CharacterAttributes GetAttributes() const { return myAttributes; }
    void SetStrength(int aStrength);
    void SetAgility(int aAgility);
    void SetVitality(int aVitality);
    void ResetHealth();
    
    int GetMaxHealth() const;
    int GetAttackValue() const;
    int GetDefense() const;
    int GetCarryCapacity() const;
    char* GetCharacterName() const { return myName; }
    int GetHealth() const { return myHealth; }
};