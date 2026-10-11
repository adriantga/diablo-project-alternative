#pragma once
#include <vector>

#include "Character.h"
#include "Chest.h"
#include "Item.h"
#include "Spell.h"
#include "Utilities.h"

class Game;

class Room
{
    std::vector<Room> myConnections = {};
    const char* myName = nullptr;
    int myId = -1;
    std::vector<Character> myEnemies = {};
    Diablo myDiablo;
    
    std::vector<Item> myItems = {};
    std::vector<Chest> myChests = {};
    std::vector<Spell> mySpells = {};
    
    int GetCount(const size_t aType) const { return static_cast<int>(aType); }
    
public:
    Room(const char* aName, const Diablo& aDiablo);
    void AddConnection(const Room& aRoom);
    void EnterCombat(const Game& aGame) const;
    Diablo GetDiablo() const { return myDiablo; }
    void SetId(const int aId) { myId = aId; }
    int GetId() const { return myId; }
    const char* GetName() const { return myName; }
    int GetConnectionCount() const { return GetCount(myConnections.size()); }
    int GetEnemyCount() const { return GetCount(myEnemies.size()); }
    void ClearConnections() { myConnections.clear(); }
    void SetConnections(const std::vector<Room>& aConnections) { myConnections = aConnections; }
    std::vector<Room> GetConnections() const { return myConnections; }
    Room GetConnection(const int aIndex) const { return myConnections.at(aIndex); }
    bool IsRoomCleared() const { return myEnemies.empty(); }
    void AddEnemy(const Character& aEnemy) { myEnemies.push_back(aEnemy); }
    void RemoveEnemy(int aIndex);
    std::vector<Character> GetEnemies() const { return myEnemies; }
    Character GetEnemy(const int aIndex) const { return myEnemies.at(aIndex); }
    Character& GetEnemyReference(const int aIndex) { return myEnemies.at(aIndex); }
    void RemoveDeadEnemies();
    
    void AddItem(const Item& aItem) { myItems.push_back(aItem); }
    void AddChest(const Chest& aChest) { myChests.push_back(aChest); }
    void AddSpell(const Spell& aSpell) { mySpells.push_back(aSpell); }
    
    void RemoveItem(int aIndex);
    void RemoveChest(int aIndex);
    void RemoveSpell(int aIndex);
    
    bool HasItems() const { return !myItems.empty(); }
    bool HasChests() const { return !myChests.empty(); }
    bool HasSpells() const { return !mySpells.empty(); }
    
    const std::vector<Item>& GetItems() const { return myItems; }
    const std::vector<Chest>& GetChests() const { return myChests; }
    const std::vector<Spell>& GetSpells() const { return mySpells; }
    
    std::vector<Item>& GetItems() { return myItems; }
    std::vector<Chest>& GetChests() { return myChests; }
    std::vector<Spell>& GetSpells() { return mySpells; }
};