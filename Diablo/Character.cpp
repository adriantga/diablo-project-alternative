#include "Character.h"

Character::~Character()
{
    delete myName;
    myName = nullptr;
}

Character::Character(const char* aCharacterName, int aStrength, int aAgility, int aVitality) : myAttributes()
{
    const size_t len = std::strlen(aCharacterName);
    myName = new char[len + 1];
    strcpy_s(myName, len + 1, aCharacterName);
    
    SetStrength(aStrength);
    SetAgility(aAgility);
    SetVitality(aVitality);
    
    ResetHealth();
}

void Character::SetStrength(int aStrength)
{
    myAttributes.strength = aStrength;
}

void Character::SetAgility(int aAgility)
{
    myAttributes.agility = aAgility;
}

void Character::SetVitality(int aVitality)
{
    myAttributes.vitality = aVitality;
}

int Character::GetAttackValue() const
{
    return myAttributes.strength * myAttributes.agility;
}

int Character::GetDefense() const
{
    return myAttributes.vitality + myAttributes.agility;
}

int Character::GetMaxHealth() const
{
    return myAttributes.vitality * 4 + myAttributes.strength * 6 + myAttributes.agility * 3;
}

int Character::GetCarryCapacity() const
{
    return myAttributes.strength + myAttributes.agility / 3;
}

void Character::ResetHealth()
{
    myHealth = GetMaxHealth();
}