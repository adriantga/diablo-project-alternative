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
    myInventory = aOther.myInventory;
    myActiveSpells = aOther.myActiveSpells;
    
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
    myInventory = std::move(aOther.myInventory);
    myActiveSpells = std::move(aOther.myActiveSpells);
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
        myInventory = aOther.myInventory;
        myActiveSpells = aOther.myActiveSpells;
        
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
        myInventory = std::move(aOther.myInventory);
        myActiveSpells = std::move(aOther.myActiveSpells);
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
    if (aDamage <= 0)
    {
        return;
    }
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

StatModifiers Character::GetTotalModifiers() const
{
    StatModifiers total;
    for (const Item& item : myInventory)
    {
        total += item.GetModifiers();
    }
    for (const Spell& spell : myActiveSpells)
    {
        total += spell.GetModifiers();
    }
    return total;
}

CharacterAttributes Character::GetAttributes() const
{
    CharacterAttributes attr;
    attr.strength = GetStrength();
    attr.agility = GetAgility();
    attr.vitality = GetVitality();
    return attr;
}

int Character::GetStrength() const
{
    return myAttributes.strength + GetTotalModifiers().strength;
}

int Character::GetAgility() const
{
    return myAttributes.agility + GetTotalModifiers().agility;
}

int Character::GetVitality() const
{
    return myAttributes.vitality + GetTotalModifiers().vitality;
}

int Character::GetAttackValue() const
{
    int base = GetStrength() * GetAgility();
    int result = base + GetTotalModifiers().attack;
    return Min(result, 0);
}

int Character::GetDefense() const
{
    int base = GetVitality() + GetAgility();
    int result = base + GetTotalModifiers().defense;
    return Min(result, 0);
}

int Character::GetMaxHealth() const
{
    int base = GetVitality() * 4 + GetStrength() * 6 + GetAgility() * 3;
    int result = base + GetTotalModifiers().maxHealth;
    return Min(result, 1);
}

int Character::GetCarryCapacity() const
{
    int base = GetStrength() + GetAgility() / 3;
    int result = base + GetTotalModifiers().carryCapacity;
    return Min(result, 0);
}

int Character::GetInventoryWeight() const
{
    int totalWeight = 0;
    for (const Item& item : myInventory)
    {
        totalWeight += item.GetWeight();
    }
    return totalWeight;
}

bool Character::CanCarry(int aWeight) const
{
    return (GetInventoryWeight() + aWeight) <= GetCarryCapacity();
}

bool Character::AddItem(const Item& aItem)
{
    if (CanCarry(aItem.GetWeight()))
    {
        myInventory.push_back(aItem);
        return true;
    }
    return false;
}

void Character::AddSpell(const Spell& aSpell)
{
    myActiveSpells.push_back(aSpell);
    if (myHealth > GetMaxHealth())
    {
        myHealth = GetMaxHealth();
    }
}

void Character::TickSpells()
{
    for (std::vector<Spell>::iterator it = myActiveSpells.begin(); it != myActiveSpells.end();)
    {
        if (it->Tick())
        {
            std::cout << ConsoleColors::StartColor(ConsoleColors::YELLOW)
                      << "Spell effect expired: " << it->GetName()
                      << ConsoleColors::EndColor() << '\n';
            it = myActiveSpells.erase(it);
        }
        else
        {
            ++it;
        }
    }
    if (myHealth > GetMaxHealth())
    {
        myHealth = GetMaxHealth();
    }
}

void Character::ResetHealth()
{
    myHealth = GetMaxHealth();
}