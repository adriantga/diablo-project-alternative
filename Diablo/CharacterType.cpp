#include "CharacterType.h"

CharacterType::CharacterType(const std::string& aName, const CharacterAttributes& aAttributes, const CharacterID aId, const EnemyTypes aEnemyType)
    : myName(aName), myBaseAttributes(aAttributes), myCharacterId(aId), myEnemyType(aEnemyType)
{
}

CharacterType::CharacterType(const std::string& aName, const int aStrength, const int aAgility, const int aVitality, const CharacterID aId, const EnemyTypes aEnemyType)
    : myName(aName), myBaseAttributes{ aStrength, aAgility, aVitality }, myCharacterId(aId), myEnemyType(aEnemyType)
{
}
