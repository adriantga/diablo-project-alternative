#include "Room.h"

#include <iostream>

#include "Game.h"
#include "Helpers.h"

Room::Room(const char* aRoomName, const Diablo& aDiablo)
{
    myName = aRoomName;
    myDiablo = aDiablo;
}

void Room::AddConnection(const Room& aRoom)
{
    myConnections.push_back(aRoom);
}

void Room::EnterCombat(const Game& aGame) const
{
    ClearScreen();
    DrawBreakerLine(LineType::Hyphen);
    WriteLine(GetName());
    DrawBreakerLine(LineType::Hyphen);
    std::cout << "Your Health: " << aGame.GetPlayer().GetHealth() << " / " << aGame.GetPlayer().GetMaxHealth() << '\n';
     
    for (int enemy = 0; enemy < GetEnemyCount(); enemy++)
    {
        int enemyIndex = enemy + 1;
        const Character& enemyCharacter = GetEnemy(enemy);
        std::cout << "[" << enemyIndex << "] Attack " << enemyCharacter.GetCharacterName() << "(" << enemyCharacter.GetHealth() << "/" << enemyCharacter.GetMaxHealth() << ")" << '\n';
    }
    
    int viewStatsIndex = GetEnemyCount() + 1;
    std::cout << '[' << viewStatsIndex << "] View stats\n";
    int viewInventoryIndex = GetEnemyCount() + 2;
    std::cout << '[' << viewInventoryIndex << "] View inventory\n";
}

void Room::RemoveEnemy(int aIndex)
{
    if (aIndex >= 0 && aIndex < GetEnemyCount())
    {
        myEnemies.erase(myEnemies.begin() + aIndex);        
    }
}

void Room::RemoveDeadEnemies()
{
    for (std::vector<Character>::iterator it = myEnemies.begin(); it != myEnemies.end();)
    {
        if (!it->IsAlive())
        {
            it = myEnemies.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Room::RemoveItem(int aIndex)
{
    if (aIndex >= 0 && aIndex < static_cast<int>(myItems.size()))
    {
        myItems.erase(myItems.begin() + aIndex);
    }
}

void Room::RemoveSpell(int aIndex)
{
    if (aIndex >= 0 && aIndex < static_cast<int>(mySpells.size()))
    {
        mySpells.erase(mySpells.begin() + aIndex);
    }
}

void Room::RemoveChest(int aIndex)
{
    if (aIndex >= 0 && aIndex < static_cast<int>(myChests.size()))
    {
        myChests.erase(myChests.begin() + aIndex);
    }
}
