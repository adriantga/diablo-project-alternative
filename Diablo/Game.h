#pragma once

#include "Character.h"
#include "Door.h"
#include "Room.h"
#include "Utilities.h"

class Game
{
    Character myPlayer;
    Diablo myDiablo;
    
    std::vector<Room> myRooms = {};
    std::vector<Door> myDoors = {};
    
    void AddRandomEnemyToRoom(Room& aRoom, const Diablo& aDiablo, int lowestIndex, int highestIndex) const;
public:
    Game(const Diablo& aDiablo);
    void PlayGame(const Diablo& aDiablo);
    Diablo GetDiablo() const { return myDiablo; }
    const Character& GetPlayer() const { return myPlayer; }
    Character& GetPlayer() { return myPlayer; }
};
