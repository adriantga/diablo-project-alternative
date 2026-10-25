#pragma once

#include "Character.h"
#include "CharacterType.h"
#include "Utilities.h"

class CharacterFactory;
struct Diablo;

class EnemyFactory
{
public:
    static constexpr int ENEMY_TYPE_COUNT = 5;

private:
    Character myEnemyTypes[ENEMY_TYPE_COUNT];

public:
    EnemyFactory();
    
    void Init();
    void SetupEnemy(EnemyArchetype aType, int aAttackDamage, int aDefense, int aHealth);
    
    Character CreateEnemy(EnemyArchetype aType) const;
    Character CreateEnemy(EnemyArchetype aType, const Diablo& aDiablo) const;
    Character CreateEnemy(EnemyArchetype aType, const Diablo& aDiablo, const CharacterFactory& aCharacterFactory) const;
    
    Character CreateRandomEnemy(int aLowestIndex = 0, int aHighestIndex = 4) const;
    Character CreateRandomEnemy(const Diablo& aDiablo, int aLowestIndex = 0, int aHighestIndex = 4) const;
    Character CreateRandomEnemy(const Diablo& aDiablo, const CharacterFactory& aCharacterFactory, int aLowestIndex = 0, int aHighestIndex = 4) const;
    
    const CharacterType& GetArchetype(EnemyArchetype aType) const;
    const Character& GetArchetypeCharacter(EnemyArchetype aType) const;
    static const char* GetEnemyName(EnemyArchetype aType);
};