#pragma once
#include <vector>

#include "Character.h"

class Game;

class Room
{
    std::vector<Room> myConnections = {};
    const char* myName = nullptr;
    int myId = -1;
    std::vector<Character> myEnemies = {};
    Diablo myDiablo;
public:
    Room(const char* aRoomName, const Diablo& aDiablo);
    void AddConnection(const Room& aRoom);
    void EnterCombat(const Game& aGame) const;
    Diablo GetDiablo() const { return myDiablo; }
    
    void SetId(int aId) { myId = aId; }
    int GetId() const { return myId; }
    const char* GetName() const { return myName; }
    int GetConnectionsCount() const { return static_cast<int>(myConnections.size()); }
    Room GetConnection(int aIndex) const { return myConnections.at(aIndex); }
    void ClearConnections() { myConnections.clear(); }
    void SetConnections(const std::vector<Room>& aConnections) { myConnections = aConnections; }
    std::vector<Room> GetConnections() const { return myConnections; }
    
    void AddEnemy(const Character& aEnemy) { myEnemies.push_back(aEnemy); }
    void RemoveEnemy(int aIndex);
    
    bool IsRoomCleared() const { return myEnemies.empty(); }
    
    Character GetEnemy(int aIndex) const { return myEnemies.at(aIndex); }
    Character& GetEnemyRef(int aIndex) { return myEnemies.at(aIndex); }
    
    void RemoveDeadEnemies();
    
    int GetEnemyCount() const { return static_cast<int>(myEnemies.size()); }
};
