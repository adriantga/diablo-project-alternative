#include "EnemyFactory.h"
#include "CharacterFactory.h"
#include "Character.h"
#include "Helpers.h"

EnemyFactory::EnemyFactory()
{
    Init();
}

const char* EnemyFactory::GetEnemyName(const EnemyTypes aType)
{
    switch (aType)
    {
    case EnemyTypes::Skeleton: return "Skeleton";
    case EnemyTypes::Wraith:   return "Wraith";
    case EnemyTypes::Brawler:  return "Brawler";
    case EnemyTypes::Undead:   return "Undead";
    case EnemyTypes::Titan:    return "Titan";
    default:                   return "Unknown";
    }
}

void EnemyFactory::SetupEnemy(const EnemyTypes aType, const int aAttackDamage, const int aDefense, const int aHealth)
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
    SetupEnemy(EnemyTypes::Skeleton, 12, 2, 25);
    SetupEnemy(EnemyTypes::Wraith, 14, 1, 20);
    SetupEnemy(EnemyTypes::Brawler, 13, 5, 40);
    SetupEnemy(EnemyTypes::Undead, 11, 4, 30);
    SetupEnemy(EnemyTypes::Titan, 16, 8, 60);
}

Character EnemyFactory::CreateEnemy(const EnemyTypes aType) const
{
    const int index = static_cast<int>(aType);
    if (index >= 0 && index < ENEMY_TYPE_COUNT)
    {
        Character newEnemy(myEnemyTypes[index]);
        return newEnemy;
    }
    return Character();
}

Character EnemyFactory::CreateEnemy(const EnemyTypes aType, const Diablo& aDiablo) const
{
    Character newEnemy = CreateEnemy(aType);
    newEnemy.SetDiablo(aDiablo);
    return newEnemy;
}

Character EnemyFactory::CreateEnemy(const EnemyTypes aType, const Diablo& aDiablo, const CharacterFactory& /*aCharacterFactory*/) const
{
    return CreateEnemy(aType, aDiablo);
}

Character EnemyFactory::CreateRandomEnemy(const int aLowestIndex, const int aHighestIndex) const
{
    const int pickedTypeIndex = GetRandomNumber(aLowestIndex, aHighestIndex);
    const EnemyTypes pickedType = static_cast<EnemyTypes>(pickedTypeIndex);
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

const CharacterType& EnemyFactory::GetArchetype(const EnemyTypes aType) const
{
    const int index = static_cast<int>(aType);
    if (index >= 0 && index < ENEMY_TYPE_COUNT)
    {
        return myEnemyTypes[index].GetCharacterType();
    }
    return myEnemyTypes[0].GetCharacterType();
}

const Character& EnemyFactory::GetEnemyPrototype(const EnemyTypes aType) const
{
    const int index = static_cast<int>(aType);
    if (index >= 0 && index < ENEMY_TYPE_COUNT)
    {
        return myEnemyTypes[index];
    }
    return myEnemyTypes[0];
}
