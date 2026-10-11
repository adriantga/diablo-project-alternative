#include "CharacterFactory.h"
#include "Character.h"
#include "Utilities.h"

Character CharacterFactory::CreatePlayer(const Diablo& aDiablo, const std::string& aName, const int aStrength, const int aAgility, const int aVitality) const
{
    CharacterType playerType(aName, aStrength, aAgility, aVitality, CharacterID::Player);
    return Character(playerType, aDiablo, aStrength, aAgility, aVitality);
}

Character CharacterFactory::CreateCharacter(const CharacterType& aType, const Diablo& aDiablo) const
{
    return Character(aType, aDiablo);
}

Character CharacterFactory::CreateCharacter(const CharacterType& aType, const Diablo& aDiablo, const int aStrength, const int aAgility, const int aVitality) const
{
    return Character(aType, aDiablo, aStrength, aAgility, aVitality);
}

Character CharacterFactory::CreateCharacter(const std::string& aName, const Diablo& aDiablo, const int aStrength, const int aAgility, const int aVitality) const
{
    CharacterType type(aName, aStrength, aAgility, aVitality);
    return Character(type, aDiablo, aStrength, aAgility, aVitality);
}

Character CharacterFactory::CreateEnemy(const EnemyTypes aType, const Diablo& aDiablo) const
{
    return myEnemyFactory.CreateEnemy(aType, aDiablo);
}

Character CharacterFactory::CreateRandomEnemy(const Diablo& aDiablo, const int aLowestIndex, const int aHighestIndex) const
{
    return myEnemyFactory.CreateRandomEnemy(aDiablo, aLowestIndex, aHighestIndex);
}
