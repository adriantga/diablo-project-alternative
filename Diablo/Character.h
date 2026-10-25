#pragma once
#include "Item.h"
#include "Spell.h"
#include "Utilities.h"
#include "CharacterType.h"
#include <vector>

class Character
{
    Diablo myDiablo = {};
    CharacterAttributes myAttributes = {};
    char* myName = nullptr;
    int myHealth = 0;
    std::vector<Item> myInventory = {};
    std::vector<Spell> myActiveSpells = {};
    CharacterType myType = {};
    int myAttack = 0;
    int myDefense = 0;
    int myMaxHealth = 0;
    bool myUseDirectStats = false;
    
public:
    ~Character();
    Character() = default;
    Character(const Character& aOther);
    Character(const char* aCharacterName, const Diablo& aDiablo, int aStrength = 1, int aAgility = 1, int aVitality = 1);
    Character(const CharacterType& aType, const Diablo& aDiablo);
    Character(const CharacterType& aType, const Diablo& aDiablo, int aStrength, int aAgility, int aVitality);
    CharacterAttributes GetAttributes() const;
    Character Set(const Character& aOther);
    Character& operator=(const Character& aOther);
    
    void SetName(const char* aName, bool aRemoveOld = false);
    
    const CharacterType& GetCharacterType() const { return myType; }
    void SetCharacterType(const CharacterType& aType) { myType = aType; }
    bool IsPlayer() const { return myType.IsPlayer(); }
    bool IsEnemy() const { return myType.IsEnemy(); }
    
    /* DIRECT / ENEMY STATS */
    void SetAttack(int aAttack);
    void SetDefense(int aDefense);
    void SetMaxHealth(int aMaxHealth);
    void SetHealth(int aHealth);
    int GetAttack() const { return myAttack; }
    
    /* SHARED */
    void SetStrength(int aStrength);
    void SetAgility(int aAgility);
    void SetVitality(int aVitality);
    void ResetHealth();
    Diablo GetDiablo() const { return myDiablo; }
    void SetDiablo(const Diablo& aDiablo) { myDiablo = aDiablo; }
    CharacterAttributes GetBaseAttributes() const { return myAttributes; }
    
    /* PLAYER SPECIFIC */
    StatModifiers GetTotalModifiers() const;
    bool AddItem(const Item& aItem);
    void AddSpell(const Spell& aSpell);
    void TickSpells();
    
    int GetBaseStrength() const { return myAttributes.strength; }
    int GetBaseAgility() const { return myAttributes.agility; }
    int GetBaseVitality() const { return myAttributes.vitality; }
    
    const std::vector<Item>& GetInventory() const { return myInventory; }
    std::vector<Item>& GetInventory() { return myInventory; }
    const std::vector<Spell>& GetActiveSpells() const { return myActiveSpells; }
    int GetInventoryWeight() const;
    bool CanCarry(int aWeight) const;
    
    int GetStrength() const;
    int GetAgility() const;
    int GetVitality() const;
    
    void SetPlayer(const Diablo& aDiablo) { myDiablo = aDiablo; }
    int GetMaxHealth() const;
    int GetAttackValue() const;
    int GetDefense() const;
    int GetCarryCapacity() const;
    const char* GetCharacterName() const { return myName; }
    int GetHealth() const { return myHealth; }
    void TakeDamage(int aDamage);
    bool IsAlive() const { return myHealth > 0; }
};