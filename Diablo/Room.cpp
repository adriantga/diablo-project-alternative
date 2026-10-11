#include "Room.h"

#include "Game.h"
#include "Helpers.h"

Room::Room(const char* aName, const Diablo& aDiablo)
{
    myName = aName;
    myDiablo = aDiablo;
}

void Room::AddConnection(const Room& aRoom)
{
    myConnections.push_back(aRoom);
}

void Room::RemoveEnemy(const int aIndex)
{
    if (aIndex >= 0 && aIndex < GetEnemyCount())
    {
        std::vector<Character> remainingEnemies;
        for (int i = 0; i < GetEnemyCount(); ++i)
        {
            if (i != aIndex)
            {
                remainingEnemies.push_back(myEnemies[i]);
            }
        }
        
        myEnemies.swap(remainingEnemies);
    }
}

void Room::RemoveItem(const int aIndex)
{
    if (aIndex >= 0 && aIndex < static_cast<int>(myItems.size()))
    {
        myItems.erase(myItems.begin() + aIndex);
    }
}

void Room::RemoveChest(const int aIndex)
{
     if (aIndex >= 0 && aIndex < static_cast<int>(myChests.size()))
    {
        myChests.erase(myChests.begin() + aIndex);
    }
}

void Room::RemoveSpell(const int aIndex)
{
     if (aIndex >= 0 && aIndex < static_cast<int>(mySpells.size()))
    {
        mySpells.erase(mySpells.begin() + aIndex);
    }
}

void Room::EnterCombat(const Game& aGame) const
{
    ClearScreen();
    DrawBreakerLine(LineType::Dash);
    WriteLine(myName);
    DrawBreakerLine(LineType::Dash);
    
    std::cout << "Your Health: " << aGame.GetPlayer().GetHealth() << " / " << aGame.GetPlayer().GetMaxHealth() << "\n";
    
    for (int index = 0; index < GetEnemyCount(); index++)
    {
        const int enemyIndex = index + 1;
        const Character& enemy = GetEnemy(index);
        std::cout << "[" << enemyIndex << "] Attack " << enemy.GetCharacterName() << "(" << enemy.GetHealth() << " / " << enemy.GetMaxHealth() << ")\n";
    }

    const int viewStatsIndex = GetEnemyCount() + 1;
    std::cout << "[" << viewStatsIndex << "] View Stats\n";
}

void Room::RemoveDeadEnemies()
{
    std::vector<Character> aliveEnemies;
    for (const Character& enemy : myEnemies)
    {
        if (enemy.IsAlive())
        {
            aliveEnemies.push_back(enemy);
        }
    }
    myEnemies.swap(aliveEnemies);
}
