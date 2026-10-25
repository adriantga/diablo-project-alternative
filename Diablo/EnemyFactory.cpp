#include "EnemyFactory.h"
#include "Character.h"
#include "Helpers.h"

EnemyFactory::EnemyFactory()
{
    Init();
}

const char* EnemyFactory::GetEnemyName(const EnemyArchetype aType)
{
    switch (aType)
    {
    case EnemyArchetype::Skeleton: 
        return "Skeleton";
    case EnemyArchetype::Wraith:   
        return "Wraith";
    case EnemyArchetype::Brawler: 
        return "Brawler";
    case EnemyArchetype::Undead:   
        return "Undead";
    case EnemyArchetype::Titan:    
        return "Titan";
    default:                       
        return "Unknown";
    }
}

void EnemyFactory::SetupEnemy(const EnemyArchetype aType, const int aAttackDamage, const int aDefense, const int aHealth)
{
    const int index = static_cast<int>(aType);
    if (index < 0 || index >= ENEMY_TYPE_COUNT)
    {
        return;
    }

    const char* name = GetEnemyName(aType);
    myEnemyTypes[index].SetName(name);
    myEnemyTypes[index].SetAttack(aAttackDamage);
    myEnemyTypes[index].SetDefense(aDefense);
    myEnemyTypes[index].SetMaxHealth(aHealth);
    myEnemyTypes[index].SetCharacterType(CharacterType(name, 0, 0, 0, CharacterID::Enemy, aType));
}

void EnemyFactory::Init()
{
    SetupEnemy(EnemyArchetype::Skeleton, 12, 2, 25);
    SetupEnemy(EnemyArchetype::Wraith, 14, 1, 20);
    SetupEnemy(EnemyArchetype::Brawler, 13, 5, 40);
    SetupEnemy(EnemyArchetype::Undead, 11, 4, 30);
    SetupEnemy(EnemyArchetype::Titan, 16, 8, 60);
}

Character EnemyFactory::CreateEnemy(const EnemyArchetype aType) const
{
    const int index = static_cast<int>(aType);
    if (index >= 0 && index < ENEMY_TYPE_COUNT)
    {
        Character newEnemy(myEnemyTypes[index]);
        return newEnemy;
    }
    
    return Character();
}

Character EnemyFactory::CreateEnemy(const EnemyArchetype aType, const Diablo& aDiablo) const
{
    Character newEnemy = CreateEnemy(aType);
    newEnemy.SetDiablo(aDiablo);
    return newEnemy;
}

Character EnemyFactory::CreateEnemy(const EnemyArchetype aType, const Diablo& aDiablo, const CharacterFactory& /*aCharacterFactory*/) const
{
    return CreateEnemy(aType, aDiablo);
}

Character EnemyFactory::CreateRandomEnemy(const int aLowestIndex, const int aHighestIndex) const
{
    const int pickedTypeIndex = GetRandomNumber(aLowestIndex, aHighestIndex);
    const EnemyArchetype pickedType = static_cast<EnemyArchetype>(pickedTypeIndex);
    return CreateEnemy(pickedType);
}

Character EnemyFactory::CreateRandomEnemy(const Diablo& aDiablo, const int aLowestIndex, const int aHighestIndex) const
{
    Character newEnemy = CreateRandomEnemy(aLowestIndex, aHighestIndex);
    newEnemy.SetDiablo(aDiablo);
    return newEnemy;
}

Character EnemyFactory::CreateRandomEnemy(const Diablo& aDiablo, const CharacterFactory& /*aCharacterFactory*/, const int aLowestIndex, const int aHighestIndex) const
{
    return CreateRandomEnemy(aDiablo, aLowestIndex, aHighestIndex);
}

const CharacterType& EnemyFactory::GetArchetype(const EnemyArchetype aType) const
{
    const int index = static_cast<int>(aType);
    if (index >= 0 && index < ENEMY_TYPE_COUNT)
    {
        return myEnemyTypes[index].GetCharacterType();
    }
    return myEnemyTypes[0].GetCharacterType();
}

const Character& EnemyFactory::GetArchetypeCharacter(const EnemyArchetype aType) const
{
    const int index = static_cast<int>(aType);
    if (index >= 0 && index < ENEMY_TYPE_COUNT)
    {
        return myEnemyTypes[index];
    }
    
    return myEnemyTypes[0];
}