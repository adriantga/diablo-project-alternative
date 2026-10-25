#pragma once

#include <string>
#include "Utilities.h"

class CharacterType
{
    std::string myName;
    CharacterAttributes myBaseAttributes = { 1, 1, 1 };
    CharacterID myCharacterId = CharacterID::Enemy;
    EnemyArchetype myEnemyType = EnemyArchetype::Skeleton;
    
public:
    CharacterType() = default;
    CharacterType(const std::string& aName, const CharacterAttributes& aAttributes, CharacterID aId = CharacterID::Enemy, EnemyArchetype aEnemyType = EnemyArchetype::Skeleton);
    CharacterType(const std::string& aName, int aStrength, int aAgility, int aVitality, CharacterID aId = CharacterID::Enemy, EnemyArchetype aEnemyType = EnemyArchetype::Skeleton);
    
    const std::string& GetName() const { return myName; }
    CharacterAttributes GetBaseAttributes() const { return myBaseAttributes; }
    CharacterID GetCharacterId() const { return myCharacterId; }
    EnemyArchetype GetEnemyType() const { return myEnemyType; }
    bool IsPlayer() const { return myCharacterId == CharacterID::Player; }
    bool IsEnemy() const { return myCharacterId == CharacterID::Enemy; }
};