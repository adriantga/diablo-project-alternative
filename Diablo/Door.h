#pragma once
#include "Room.h"

class Game;

class Door
{
    const Room* myRoom = nullptr;
    bool myIsLocked = false;
    
    int myRequiredStrength = 0;
    int myRequiredAgility = 0;
    
    Diablo myDiablo = {};
    
    void SetRequired(const int aRequiredStrength)
    {
        if (myIsLocked && aRequiredStrength == 0) myRequiredStrength = 1;
    }
    
public:
    Door(const Room& aRoom, const Diablo& aDiablo);
    Door(const Room& aRoom, const Diablo& aDiablo, bool aIsLocked, int aRequiredStrength, int aRequiredAgility);
    void OpenDoor(const Game& aGame) const;
    int GetRequiredStrength() const { return myRequiredStrength; }
    int GetRequiredAgility() const { return myRequiredAgility; }
    bool IsLocked() const { return myIsLocked; }
    
    void SetLocked(const bool aIsLocked, const int aRequiredStrength, const int aRequiredAgility)
    {
        myIsLocked = aIsLocked;
        myRequiredStrength = aRequiredStrength;
        myRequiredAgility = aRequiredAgility;
        
        if (aIsLocked)
        {
            SetRequired(aRequiredStrength);
            SetRequired(aRequiredAgility);
        }
    }
    
    void Unlock()
    {
        myIsLocked = false;
    }
    
    const char* GetRoomName() const { return myRoom ? myRoom->GetName() : ""; }
    const Room* GetRoom() const { return myRoom; }
};
