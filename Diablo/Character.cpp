#include "Character.h"

#include "Helpers.h"
#include <cstring>

Character::~Character()
{
    delete[] myName;
    myName = nullptr;
}

Character::Character(const Character& aOther)
{
    myDiablo = aOther.myDiablo;
    myAttributes = aOther.myAttributes;
    myHealth = aOther.myHealth;
    
    if (aOther.myName)
    {
        const size_t len = std::strlen(aOther.myName);
        myName = new char[len + 1];
        strcpy_s(myName, len + 1, aOther.myName);
    }
    else
    {
        myName = nullptr;
    }
}

Character::Character(Character&& aOther) noexcept
{
    myDiablo = aOther.myDiablo;
    myAttributes = aOther.myAttributes;
    myHealth = aOther.myHealth;
    myName = aOther.myName;
    aOther.myName = nullptr;
}

Character& Character::operator=(const Character& aOther)
{
    if (this != &aOther)
    {
        delete[] myName;
        myName = nullptr;
        
        myDiablo = aOther.myDiablo;
        myAttributes = aOther.myAttributes;
        myHealth = aOther.myHealth;
        
        if (aOther.myName)
        {
            const size_t len = std::strlen(aOther.myName);
            myName = new char[len + 1];
            strcpy_s(myName, len + 1, aOther.myName);
        }
    }
    return *this;
}

Character& Character::operator=(Character&& aOther) noexcept
{
    if (this != &aOther)
    {
        delete[] myName;
        
        myDiablo = aOther.myDiablo;
        myAttributes = aOther.myAttributes;
        myHealth = aOther.myHealth;
        myName = aOther.myName;
        aOther.myName = nullptr;
    }
    return *this;
}

Character::Character(const char* aCharacterName, const Diablo& aDiablo, int aStrength, int aAgility, int aVitality)
{
    this->myDiablo = aDiablo;
    
    if (aCharacterName)
    {
        const size_t len = std::strlen(aCharacterName);
        myName = new char[len + 1];
        strcpy_s(myName, len + 1, aCharacterName);
    }
    else
    {
        myName = nullptr;
    }
    
    SetStrength(aStrength);
    SetAgility(aAgility);
    SetVitality(aVitality);
    
    ResetHealth();
}

void Character::TakeDamage(int aDamage)
{
    aDamage = Min(aDamage, 1);
    myHealth -= aDamage;
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