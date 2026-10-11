#include "Character.h"
#include "Helpers.h"
#include <cstring>

Character::~Character()
{
    delete[] myName;
    myName = nullptr;
}

void Character::SetName(const char* aName, const bool aRemoveOld)
{
    if (myName)
    {
        delete[] myName;
        myName = nullptr;
    }

    if (aName)
    {
        const size_t len = std::strlen(aName);
        myName = new char[len + 1];
        strcpy_s(myName, len + 1, aName);
    }
    else if (!aName && aRemoveOld)
    {
        myName = nullptr;
    }
}

Character::Character(const Character& aOther)
{
    myDiablo = aOther.myDiablo;
    myAttributes = aOther.myAttributes;
    myHealth = aOther.myHealth;
    myInventory = aOther.myInventory;
    myActiveSpells = aOther.myActiveSpells;
    myType = aOther.myType;
    myAttack = aOther.myAttack;
    myDefense = aOther.myDefense;
    myMaxHealth = aOther.myMaxHealth;
    myUseDirectStats = aOther.myUseDirectStats;
   
    SetName(aOther.myName, true);
}

Character Character::Set(const Character& aOther)
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
        myType = aOther.myType;
        myAttack = aOther.myAttack;
        myDefense = aOther.myDefense;
        myMaxHealth = aOther.myMaxHealth;
        myUseDirectStats = aOther.myUseDirectStats;
        SetName(aOther.myName, true);
    }
    
    return *this;
}

Character& Character::operator=(const Character& aOther)
{
    Set(aOther);
    return *this;
}

Character::Character(const char* aCharacterName, const Diablo& aDiablo, const int aStrength, const int aAgility, const int aVitality)
{
    this->myDiablo = aDiablo;
    SetName(aCharacterName, true);
    
    SetStrength(aStrength);
    SetAgility(aAgility);
    SetVitality(aVitality);
    
    ResetHealth();
}

Character::Character(const CharacterType& aType, const Diablo& aDiablo)
    : Character(aType.GetName().c_str(), aDiablo, aType.GetBaseAttributes().strength, aType.GetBaseAttributes().agility, aType.GetBaseAttributes().vitality)
{
    myType = aType;
}

Character::Character(const CharacterType& aType, const Diablo& aDiablo, const int aStrength, const int aAgility, const int aVitality)
    : Character(aType.GetName().c_str(), aDiablo, aStrength, aAgility, aVitality)
{
    myType = aType;
}

CharacterAttributes Character::GetAttributes() const
{
    CharacterAttributes attributes;
    attributes.strength = GetStrength();
    attributes.agility = GetAgility();
    attributes.vitality = GetVitality();
    return attributes;
}

StatModifiers Character::GetTotalModifiers() const
{
    StatModifiers total;
    for (const Item& item : myInventory)
    {
        total.Add(item.GetModifiers());
    }
    
    for (const Spell& spell : myActiveSpells)
    {
        total.Add(spell.GetModifiers());
    }
    
    return total;
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
    const int base = myUseDirectStats ? myAttack : (GetStrength() * GetAgility());
    const int result = base + GetTotalModifiers().attack;
    return Min(result, 0);
}

int Character::GetDefense() const
{
    const int base = myUseDirectStats ? myDefense : (GetVitality() + GetAgility());
    const int result = base + GetTotalModifiers().defense;
    return Min(result, 0);
}

int Character::GetMaxHealth() const
{
    const int base = myUseDirectStats ? myMaxHealth : (GetVitality() * 4 + GetStrength() * 6 + GetAgility() * 3);
    const int result = base + GetTotalModifiers().maxHealth;
    return Min(result, 1);
}

int Character::GetCarryCapacity() const
{
    const int base = GetStrength() + GetAgility() / 3;
    const int result = base + GetTotalModifiers().carryCapacity;
    return Min(result, 0);
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
    myHealth = Max(myHealth, GetMaxHealth());
}

void Character::TickSpells()
{
    for (std::vector<Spell>::iterator it = myActiveSpells.begin(); it != myActiveSpells.end();)
    {
        if (it->Tick())
        {
            std::cout << ConsoleColors::StartColor(Color::Yellow) << "Spell effect expired: " << it->GetName() << ConsoleColors::EndColor() << '\n';
            it = myActiveSpells.erase(it);
        }
        else
        {
            ++it;
        }
    }
    
    myHealth = Max(myHealth, GetMaxHealth());
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

bool Character::CanCarry(const int aWeight) const
{
    return (GetInventoryWeight() + aWeight) <= GetCarryCapacity();
}

void Character::TakeDamage(int aDamage)
{
    aDamage = Min(aDamage, 0);
    myHealth -= aDamage;
}

void Character::SetStrength(const int aStrength)
{
    myAttributes.strength = aStrength;
}

void Character::SetAgility(const int aAgility)
{
    myAttributes.agility = aAgility;
}

void Character::SetVitality(const int aVitality)
{
    myAttributes.vitality = aVitality;
}

void Character::ResetHealth()
{
    myHealth = GetMaxHealth();
}

void Character::SetAttack(const int aAttack)
{
    myAttack = aAttack;
    myUseDirectStats = true;
}

void Character::SetDefense(const int aDefense)
{
    myDefense = aDefense;
    myUseDirectStats = true;
}

void Character::SetMaxHealth(const int aMaxHealth)
{
    myMaxHealth = aMaxHealth;
    myHealth = aMaxHealth;
    myUseDirectStats = true;
}

void Character::SetHealth(const int aHealth)
{
    myHealth = aHealth;
}