#pragma once
#include "Utilities.h"
#include "Character.h"
#include "Door.h"
#include "Room.h"
#include "CharacterFactory.h"
#include "ItemFactory.h"

class Game
{
    Character myPlayer;
    Diablo myDiablo;
    CharacterFactory myCharacterFactory;
    ItemFactory myItemFactory;
    
    std::vector<Room> myRooms;
    std::vector<Door> myDoors;
    
    void AddRandomEnemyToRoom(Room& aRoom, const Diablo& aDiablo, int aLowestIndex, int aHighestIndex) const;
    
public:
    Game(Diablo& aDiablo);
    void PlayGame(const Diablo& aDiablo);
    Diablo GetDiablo() const { return myDiablo; }
    const Character& GetPlayer() const { return myPlayer; }
    Character& GetPlayer() { return myPlayer; }
    const CharacterFactory& GetCharacterFactory() const { return myCharacterFactory; }
    CharacterFactory& GetCharacterFactory() { return myCharacterFactory; }
    const ItemFactory& GetItemFactory() const { return myItemFactory; }
    ItemFactory& GetItemFactory() { return myItemFactory; }
};