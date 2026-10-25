#pragma once

#include <string>
#include "CharacterType.h"
#include "EnemyFactory.h"

class Character;
struct Diablo;

class CharacterFactory
{
    EnemyFactory myEnemyFactory;

public:
    CharacterFactory() = default;
    
    Character CreatePlayer(const Diablo& aDiablo, const std::string& aName = "Hero", int aStrength = 5, int aAgility = 5, int aVitality = 5) const;
    Character CreateCharacter(const CharacterType& aType, const Diablo& aDiablo) const;
    Character CreateCharacter(const CharacterType& aType, const Diablo& aDiablo, int aStrength, int aAgility, int aVitality) const;
    Character CreateCharacter(const std::string& aName, const Diablo& aDiablo, int aStrength = 1, int aAgility = 1, int aVitality = 1) const;
    
    Character CreateEnemy(EnemyArchetype aType, const Diablo& aDiablo) const;
    Character CreateRandomEnemy(const Diablo& aDiablo, int aLowestIndex = 0, int aHighestIndex = 4) const;
    
    const EnemyFactory& GetEnemyFactory() const { return myEnemyFactory; }
    EnemyFactory& GetEnemyFactory() { return myEnemyFactory; }
};