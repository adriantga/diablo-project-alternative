#include "Game.h"

#include <iostream>
#include <random>
#include <cstring>
#include "BattleController.h"
#include "Helpers.h"

Game::Game(const Diablo& aDiablo) : myPlayer("Wanderer", aDiablo, 5, 4, 6)
{
    this->myDiablo = aDiablo;
    
    Room entranceRoom = Room("Entrance", aDiablo);
    Room cathedralRoom = Room("Cathedral", aDiablo);
    Room armoryRoom = Room("Armory", aDiablo);
    Room kitchenRoom = Room("Kitchen", aDiablo);
    Room cellsRoom = Room("Cells", aDiablo);
    
    entranceRoom.SetId(0);
    cathedralRoom.SetId(1);
    armoryRoom.SetId(2);
    kitchenRoom.SetId(3);
    cellsRoom.SetId(4);
    
    entranceRoom.AddConnection(cathedralRoom);
    
    cathedralRoom.AddConnection(entranceRoom);
    cathedralRoom.AddConnection(armoryRoom);
    
    armoryRoom.AddConnection(cathedralRoom);
    armoryRoom.AddConnection(kitchenRoom);
    
    kitchenRoom.AddConnection(armoryRoom);
    kitchenRoom.AddConnection(cellsRoom);
    
    cellsRoom.AddConnection(kitchenRoom);
    
    constexpr int EMPTY = 0;
    constexpr int LONE_WOLF = 1;
    constexpr int DUO = 2;
    constexpr int TRIO = 3;
    constexpr int SQUAD = 4;
    
    int cathedralEnemyCount = GetRandomNumber(EMPTY, LONE_WOLF);
    int armoryEnemyCount = GetRandomNumber(EMPTY, DUO);
    int kitchenEnemyCount = GetRandomNumber(EMPTY, TRIO);
    int cellsEnemyCount = GetRandomNumber(EMPTY, SQUAD);
    
    int i;
    for (i = 0; i < cathedralEnemyCount; i++)
    {
        AddRandomEnemyToRoom(cathedralRoom, aDiablo, 0, 1);
    }
    
    for (i = 0; i < armoryEnemyCount; i++)
    {
        AddRandomEnemyToRoom(armoryRoom, aDiablo, 0, 2);
    }
    
    for (i = 0; i < kitchenEnemyCount; i++)
    {
        AddRandomEnemyToRoom(kitchenRoom, aDiablo, 1, 3);
    }
    
    for (i = 0; i < cellsEnemyCount; i++)
    {
        AddRandomEnemyToRoom(cellsRoom, aDiablo, 0, 4);
    }
    
    myRooms.push_back(entranceRoom);
    myRooms.push_back(cathedralRoom);
    myRooms.push_back(armoryRoom);
    myRooms.push_back(kitchenRoom);
    myRooms.push_back(cellsRoom);
    
    Door entranceDoor = Door(myRooms[0], aDiablo);
    Door cathedralDoor = Door(myRooms[1], aDiablo);
    Door armoryDoor = Door(myRooms[2], aDiablo);
    armoryDoor.SetLocked(true, 3, 4);
    
    Door kitchenDoor = Door(myRooms[3], aDiablo);
    kitchenDoor.SetLocked(true, 5, 4);
    
    Door cellsDoor = Door(myRooms[4], aDiablo);
    cellsDoor.SetLocked(true, 5, 5);
    
    myDoors.push_back(entranceDoor);
    myDoors.push_back(cathedralDoor);
    myDoors.push_back(armoryDoor);
    myDoors.push_back(kitchenDoor);
    myDoors.push_back(cellsDoor);
}

void Game::AddRandomEnemyToRoom(Room& aRoom, const Diablo& aDiablo, int lowestIndex, int highestIndex) const
{
    int pickedEnemy = GetRandomNumber(lowestIndex, highestIndex);
    
    constexpr int SKELETON_ID = 0;
    constexpr int WRAITH_ID = 1;
    constexpr int BRAWLER_ID = 2;
    constexpr int UNDEAD_ID = 3;
    constexpr int TITAN_ID = 4;
    
    Character character;
    
    switch (pickedEnemy)
    {
    case SKELETON_ID:
        {
            constexpr int MIN_SKELETON_SKILL = 1;
            constexpr int MAX_SKELETON_SKILL = 2;
        
            character = Character("Skeleton", aDiablo, GetRandomNumber(MIN_SKELETON_SKILL, MAX_SKELETON_SKILL), GetRandomNumber(MIN_SKELETON_SKILL, MAX_SKELETON_SKILL), GetRandomNumber(MIN_SKELETON_SKILL, MAX_SKELETON_SKILL));
        }
        break;
    case WRAITH_ID:
        {
            constexpr int MIN_WRAITH_SKILL = 2;
            constexpr int MAX_WRAITH_SKILL = 3;
        
            character = Character("Wraith", aDiablo, GetRandomNumber(MIN_WRAITH_SKILL, MAX_WRAITH_SKILL), GetRandomNumber(MIN_WRAITH_SKILL, MAX_WRAITH_SKILL), GetRandomNumber(MIN_WRAITH_SKILL, MAX_WRAITH_SKILL));
        }
        break;
    case BRAWLER_ID:
        {
            constexpr int MIN_BRAWLER_SKILL = 3;
            constexpr int MAX_BRAWLER_SKILL = 4;
        
            character = Character("Brawler", aDiablo, GetRandomNumber(MIN_BRAWLER_SKILL, MAX_BRAWLER_SKILL - 1), GetRandomNumber(MIN_BRAWLER_SKILL, MAX_BRAWLER_SKILL - 2), GetRandomNumber(MIN_BRAWLER_SKILL, MAX_BRAWLER_SKILL));
        }
        break;
    case UNDEAD_ID:
        {
            constexpr int MIN_UNDEAD_SKILL = 4;
            constexpr int MAX_UNDEAD_SKILL = 5;
        
            character = Character("Undead", aDiablo, GetRandomNumber(MIN_UNDEAD_SKILL, MAX_UNDEAD_SKILL), GetRandomNumber(MIN_UNDEAD_SKILL, MAX_UNDEAD_SKILL), GetRandomNumber(MIN_UNDEAD_SKILL, MAX_UNDEAD_SKILL));
        }
        break;
    case TITAN_ID:
        {
            constexpr int MIN_TITAN_SKILL = 4;
            constexpr int MAX_TITAN_SKILL = 6;
        
            character = Character("Titan", aDiablo, GetRandomNumber(MIN_TITAN_SKILL, MAX_TITAN_SKILL - 1), GetRandomNumber(MIN_TITAN_SKILL, MAX_TITAN_SKILL), GetRandomNumber(MIN_TITAN_SKILL, MAX_TITAN_SKILL - 1));
        }
        break;
    default:
        std::cout << ConsoleColors::StartColor(ConsoleColors::RED) << "Invalid enemy picked" << ConsoleColors::EndColor() << '\n';
        break;
    }
    
    aRoom.AddEnemy(character);
}

void Game::PlayGame(const Diablo& aDiablo)
{
    myDiablo = aDiablo;
    int currentRoomIndex = 0;
    
    while (myPlayer.IsAlive())
    {
        Room& currentRoom = myRooms[currentRoomIndex];
        
        if (!currentRoom.IsRoomCleared())
        {
            while (!currentRoom.IsRoomCleared() && myPlayer.IsAlive())
            {
                currentRoom.EnterCombat(*this);
                
                int viewStatsIndex = currentRoom.GetEnemyCount() + 1;
                int enemyChoice = -1;
                ForceInput(enemyChoice, 1, viewStatsIndex);
                
                if (enemyChoice == viewStatsIndex)
                {
                    ClearScreen();
                    ShowStats(myPlayer, myDiablo);
                    Pause();
                }
                else
                {
                    BattleController::BattleTurn(myDiablo, *this, currentRoom, enemyChoice - 1);
                    Pause();
                }
            }
            
            if (!myPlayer.IsAlive())
            {
                ClearScreen();
                DrawBreakerLine(LineType::EqualSign);
                std::cout << ConsoleColors::StartColor(ConsoleColors::RED) << "You have died! Game Over." << ConsoleColors::EndColor() << '\n';
                DrawBreakerLine(LineType::EqualSign);
                Pause();
                return;
            }
            
            ClearScreen();
            DrawBreakerLine(LineType::EqualSign);
            std::cout << ConsoleColors::StartColor(ConsoleColors::GREEN) << "Room cleared!" << ConsoleColors::EndColor() << '\n';
            DrawBreakerLine(LineType::EqualSign);
            Pause();
        }
        
        if (currentRoom.GetId() == 4 || strcmp(currentRoom.GetName(), "Cells") == 0)
        {
            ClearScreen();
            DrawBreakerLine(LineType::EqualSign);
            WriteLine("VICTORY SCREEN");
            DrawBreakerLine(LineType::EqualSign);
            std::cout << ConsoleColors::StartColor(ConsoleColors::GREEN) << "Congratulations! You reached the Cells and won the game!" << ConsoleColors::EndColor() << '\n';
            Pause();
            return;
        }
        
        ClearScreen();
        DrawBreakerLine(LineType::Hyphen);
        WriteLine(currentRoom.GetName());
        DrawBreakerLine(LineType::Hyphen);
        
        for (int connection = 0; connection < currentRoom.GetConnectionsCount(); connection++)
        {
            int connectionIndex = connection + 1;
            std::cout << '[' << connectionIndex << "] " << currentRoom.GetConnection(connection).GetName() << '\n';
        }
        
        int viewStatsIndex = currentRoom.GetConnectionsCount() + 1;
        std::cout << '[' << viewStatsIndex << "] View stats\n";
        
        int choice = -1;
        ForceInput(choice, 1, viewStatsIndex);
        
        if (choice == viewStatsIndex)
        {
            ClearScreen();
            ShowStats(myPlayer, myDiablo);
            Pause();
        }
        else
        {
            int targetRoomId = currentRoom.GetConnection(choice - 1).GetId();
            Door& targetDoor = myDoors[targetRoomId];
            
            if (targetDoor.IsLocked())
            {
                targetDoor.OpenDoor(myDiablo);
                
                int doorChoice = -1;
                ForceInput(doorChoice, 1, 3);
                
                if (doorChoice == 1)
                {
                    if (myPlayer.GetStrength() >= targetDoor.GetRequiredStrength())
                    {
                        targetDoor.SetLocked(false, 0, 0);
                        std::cout << ConsoleColors::StartColor(ConsoleColors::GREEN) << "You broke the door open!" << ConsoleColors::EndColor() << '\n';
                        Pause();
                        currentRoomIndex = targetRoomId;
                    }
                    else
                    {
                        std::cout << ConsoleColors::StartColor(ConsoleColors::RED) << "You are not strong enough to break the door!" << ConsoleColors::EndColor() << '\n';
                        Pause();
                    }
                }
                else if (doorChoice == 2)
                {
                    if (myPlayer.GetAgility() >= targetDoor.GetRequiredAgility())
                    {
                        targetDoor.SetLocked(false, 0, 0);
                        std::cout << ConsoleColors::StartColor(ConsoleColors::GREEN) << "You successfully picked the lock!" << ConsoleColors::EndColor() << '\n';
                        Pause();
                        currentRoomIndex = targetRoomId;
                    }
                    else
                    {
                        std::cout << ConsoleColors::StartColor(ConsoleColors::RED) << "You are not agile enough to lock pick the door!" << ConsoleColors::EndColor() << '\n';
                        Pause();
                    }
                }
                else
                {
                    // Go back - stay in current room
                }
            }
            else
            {
                currentRoomIndex = targetRoomId;
            }
        }
    }
}
