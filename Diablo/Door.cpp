#include "Door.h"

#include <iostream>

#include "Game.h"
#include "Helpers.h"

Door::Door(const Room& aRoom, const Diablo& aDiablo) : Door(aRoom, aDiablo, false, 0, 0)
{
    
}

Door::Door(const Room& aRoom, const Diablo& aDiablo, bool aIsLocked, int aRequiredStrength, int aRequiredAgility)
{
    myRoom = &aRoom;
    myDiablo = aDiablo;
    SetLocked(aIsLocked, aRequiredStrength, aRequiredAgility);
}

void Door::OpenDoor(const Diablo& aDiablo) const
{
    ClearScreen();
    if (myIsLocked)
    {
        WriteLine("The door is locked. What would you like to do?");
        std::cout << "[1] Break the door (Strength " << myRequiredStrength << ")" << '\n';
        std::cout << "[2] Lock pick the door (Agility " << myRequiredAgility << ")" << '\n';
        WriteLine("[3] Go Back");
        return;
    }
    
    if (myRoom && !myRoom->IsRoomCleared())
    {
        myRoom->EnterCombat(Game(aDiablo));
        return;
    }
    
    DrawBreakerLine(LineType::Hyphen);
    WriteLine(myRoom ? myRoom->GetName() : "");
    DrawBreakerLine(LineType::Hyphen);
    
    if (myRoom)
    {
        for (int connection = 0; connection < myRoom->GetConnectionsCount(); connection++)
        {
            int connectionIndex = connection + 1;
            std::cout << '[' << connectionIndex << "] " << myRoom->GetConnection(connection).GetName() << '\n';
        }
        
        std::cout << "[" << myRoom->GetConnectionsCount() + 1 << "] View stats" << '\n';
    }
}
