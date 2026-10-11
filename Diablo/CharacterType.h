#pragma once

#include <string>
#include "Utilities.h"

class CharacterType
{
    std::string myName;
    CharacterAttributes myBaseAttributes = { 1, 1, 1 };
    CharacterID myCharacterId = CharacterID::Enemy;
    EnemyTypes myEnemyType = EnemyTypes::Skeleton;
    
public:
    CharacterType() = default;
    CharacterType(const std::string& aName, const CharacterAttributes& aAttributes, CharacterID aId = CharacterID::Enemy, EnemyTypes aEnemyType = EnemyTypes::Skeleton);
    CharacterType(const std::string& aName, int aStrength, int aAgility, int aVitality, CharacterID aId = CharacterID::Enemy, EnemyTypes aEnemyType = EnemyTypes::Skeleton);
    
    const std::string& GetName() const { return myName; }
    CharacterAttributes GetBaseAttributes() const { return myBaseAttributes; }
    CharacterID GetCharacterId() const { return myCharacterId; }
    EnemyTypes GetEnemyType() const { return myEnemyType; }
    bool IsPlayer() const { return myCharacterId == CharacterID::Player; }
    bool IsEnemy() const { return myCharacterId == CharacterID::Enemy; }
};
