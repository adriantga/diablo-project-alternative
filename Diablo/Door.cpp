#include "Door.h"

#include "Helpers.h"

Door::Door(const Room& aRoom, const Diablo& aDiablo) : Door(aRoom, aDiablo, false, 0, 0)
{
    
}

Door::Door(const Room& aRoom, const Diablo& aDiablo, const bool aIsLocked, const int aRequiredStrength, const int aRequiredAgility)
{
    myRoom = &aRoom;
    myDiablo = aDiablo;
    SetLocked(aIsLocked, aRequiredStrength, aRequiredAgility);
}

void Door::OpenDoor(const Game& aGame) const
{
    ClearScreen();
    if (myIsLocked)
    {
        WriteLine("The door is locked.");
        std::cout << "[1] Attempt to break the door (Requires " << myRequiredStrength << " strength)\n";
        std::cout << "[2] Attempt to lock pick the door (Requires " << myRequiredAgility << " agility)\n";
        WriteLine("[3] Go Back");
        return;
    }
    
    if (myRoom && !myRoom->IsRoomCleared())
    {
        myRoom->EnterCombat(aGame);
        return;
    }
    
    DrawBreakerLine(LineType::Dash);
    WriteLine(myRoom ? myRoom->GetName() : "");
    DrawBreakerLine(LineType::Dash);
    
    if (myRoom)
    {
        for (int connection = 0; connection < myRoom->GetConnectionCount(); connection++)
        {
            const int connectionIndex = connection + 1;
            std::cout << "[" << connectionIndex << "] Enter " << myRoom->GetConnection(connection).GetName() << "\n";
        }
        
        std::cout << "[" << myRoom->GetConnectionCount() + 1 << "] View stats\n";
    }
}