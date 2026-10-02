#pragma once
#include "Room.h"

class Door
{
    const Room* myRoom = nullptr;
    bool myIsLocked = false;
    
    int myRequiredStrength = 0;
    int myRequiredAgility = 0;
    
    Diablo myDiablo = {};
public:
    Door(const Room& aRoom, const Diablo& aDiablo);
    Door(const Room& aRoom, const Diablo& aDiablo, bool aIsLocked, int aRequiredStrength,  int aRequiredAgility);
    void OpenDoor(const Diablo& aDiablo) const;
    int GetRequiredStrength() const { return myRequiredStrength; }
    int GetRequiredAgility() const { return myRequiredAgility; }
    bool IsLocked() const { return myIsLocked; }
    
    void SetLocked(bool aLocked, int aRequiredStrength = 0, int aRequiredAgility = 0)
    {
        myIsLocked = aLocked;
        myRequiredStrength = aRequiredStrength;
        myRequiredAgility = aRequiredAgility;
    }
    
    void Unlock()
    {
        myIsLocked = false;
    }
    
    const char* GetRoomName() const { return myRoom ? myRoom->GetName() : ""; }
    const Room* GetRoom() const { return myRoom; }
};
