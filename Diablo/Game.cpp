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
    
    // Add starting items, chests, and spells to rooms
    // StatModifiers(strength, agility, vitality, attack, defense, maxHealth, carryCapacity)
    entranceRoom.AddItem(Item("Worn Dagger", 1, StatModifiers(0, 0, 0, 1, 0, 0, 0)));
    entranceRoom.AddItem(Item("Traveler's Boots", 1, StatModifiers(0, 1, 0, 0, 1, 0, 0)));
    
    Chest cathedralChest("Altar Chest");
    cathedralChest.AddItem(Item("Blessed Mace", 3, StatModifiers(2, 0, 0, 4, 0, 0, 0)));
    cathedralChest.AddItem(Item("Holy Relic", 1, StatModifiers(0, 0, 2, 0, 0, 20, 0)));
    cathedralRoom.AddChest(cathedralChest);
    cathedralRoom.AddSpell(Spell("Prayer of Fortitude", 5, StatModifiers(0, 0, 2, 0, 5, 20, 0)));
    
    armoryRoom.AddItem(Item("Heavy Steel Armor", 5, StatModifiers(0, -1, 1, 0, 6, 30, 0)));
    armoryRoom.AddItem(Item("Greatsword", 4, StatModifiers(3, 0, 0, 5, 0, 0, 0)));
    Chest armoryChest("Armory Cache");
    armoryChest.AddItem(Item("Tower Shield", 4, StatModifiers(0, 0, 1, 0, 5, 0, 0)));
    armoryChest.AddItem(Item("Ring of Might", 0, StatModifiers(3, 0, 0, 0, 0, 0, 0)));
    armoryRoom.AddChest(armoryChest);
    armoryRoom.AddSpell(Spell("War Cry", 4, StatModifiers(2, 0, 0, 6, 0, 0, 0)));
    
    kitchenRoom.AddItem(Item("Chef's Cleaver", 2, StatModifiers(0, 0, 0, 3, 0, 0, 0)));
    kitchenRoom.AddItem(Item("Hearty Stew", 1, StatModifiers(0, 0, 2, 0, 0, 15, 0)));
    kitchenRoom.AddSpell(Spell("Feast of Agility", 5, StatModifiers(0, 3, 0, 0, 0, 0, 2)));
    
    cellsRoom.AddItem(Item("Hero's Trophy", 1, StatModifiers(2, 2, 2, 0, 0, 0, 0)));
    
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
    Diablo enemyDiablo = aDiablo;
    enemyDiablo.cheats.hasGodMode = false;
    enemyDiablo.cheats.hasOneShot = false;

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
        
            character = Character("Skeleton", enemyDiablo, GetRandomNumber(MIN_SKELETON_SKILL, MAX_SKELETON_SKILL), GetRandomNumber(MIN_SKELETON_SKILL, MAX_SKELETON_SKILL), GetRandomNumber(MIN_SKELETON_SKILL, MAX_SKELETON_SKILL));
        }
        break;
    case WRAITH_ID:
        {
            constexpr int MIN_WRAITH_SKILL = 2;
            constexpr int MAX_WRAITH_SKILL = 3;
        
            character = Character("Wraith", enemyDiablo, GetRandomNumber(MIN_WRAITH_SKILL, MAX_WRAITH_SKILL), GetRandomNumber(MIN_WRAITH_SKILL, MAX_WRAITH_SKILL), GetRandomNumber(MIN_WRAITH_SKILL, MAX_WRAITH_SKILL));
        }
        break;
    case BRAWLER_ID:
        {
            constexpr int MIN_BRAWLER_SKILL = 3;
            constexpr int MAX_BRAWLER_SKILL = 4;
        
            character = Character("Brawler", enemyDiablo, GetRandomNumber(MIN_BRAWLER_SKILL, MAX_BRAWLER_SKILL - 1), GetRandomNumber(MIN_BRAWLER_SKILL, MAX_BRAWLER_SKILL - 2), GetRandomNumber(MIN_BRAWLER_SKILL, MAX_BRAWLER_SKILL));
        }
        break;
    case UNDEAD_ID:
        {
            constexpr int MIN_UNDEAD_SKILL = 4;
            constexpr int MAX_UNDEAD_SKILL = 5;
        
            character = Character("Undead", enemyDiablo, GetRandomNumber(MIN_UNDEAD_SKILL, MAX_UNDEAD_SKILL), GetRandomNumber(MIN_UNDEAD_SKILL, MAX_UNDEAD_SKILL), GetRandomNumber(MIN_UNDEAD_SKILL, MAX_UNDEAD_SKILL));
        }
        break;
    case TITAN_ID:
        {
            constexpr int MIN_TITAN_SKILL = 4;
            constexpr int MAX_TITAN_SKILL = 6;
        
            character = Character("Titan", enemyDiablo, GetRandomNumber(MIN_TITAN_SKILL, MAX_TITAN_SKILL - 1), GetRandomNumber(MIN_TITAN_SKILL, MAX_TITAN_SKILL), GetRandomNumber(MIN_TITAN_SKILL, MAX_TITAN_SKILL - 1));
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
    myPlayer.SetDiablo(aDiablo);
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
                int viewInventoryIndex = currentRoom.GetEnemyCount() + 2;
                int enemyChoice = -1;
                ForceInput(enemyChoice, 1, viewInventoryIndex);
                
                if (enemyChoice == viewStatsIndex)
                {
                    ClearScreen();
                    ShowStats(myPlayer, myDiablo);
                    Pause();
                }
                else if (enemyChoice == viewInventoryIndex)
                {
                    ClearScreen();
                    ShowInventory(myPlayer);
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
        
        enum class OptionType { Move, PickItem, OpenChest, ReadSpell, ViewInventory, ViewStats };
        struct ActionOption
        {
            OptionType type;
            int data;
            std::string label;
        };
        
        std::vector<ActionOption> options;
        for (int connection = 0; connection < currentRoom.GetConnectionsCount(); connection++)
        {
            options.push_back({ OptionType::Move, connection, "Go to " + std::string(currentRoom.GetConnection(connection).GetName()) });
        }
        
        if (currentRoom.HasItems())
        {
            options.push_back({ OptionType::PickItem, 0, "Pick up item from floor" });
        }
        
        if (currentRoom.HasChests())
        {
            options.push_back({ OptionType::OpenChest, 0, "Open chest" });
        }
        
        if (currentRoom.HasSpells())
        {
            options.push_back({ OptionType::ReadSpell, 0, "Read spell scroll" });
        }
        
        options.push_back({ OptionType::ViewInventory, 0, "View inventory" });
        options.push_back({ OptionType::ViewStats, 0, "View stats" });
        
        for (size_t i = 0; i < options.size(); i++)
        {
            std::cout << '[' << (i + 1) << "] " << options[i].label << '\n';
        }
        
        int choice = -1;
        ForceInput(choice, 1, static_cast<int>(options.size()));
        const ActionOption& selected = options[choice - 1];
        
        if (selected.type == OptionType::ViewStats)
        {
            ClearScreen();
            ShowStats(myPlayer, myDiablo);
            Pause();
        }
        else if (selected.type == OptionType::ViewInventory)
        {
            ClearScreen();
            ShowInventory(myPlayer);
            Pause();
        }
        else if (selected.type == OptionType::PickItem)
        {
            ClearScreen();
            DrawBreakerLine(LineType::Hyphen);
            std::cout << "Items on the floor in " << currentRoom.GetName() << ":\n";
            DrawBreakerLine(LineType::Hyphen);
            const auto& roomItems = currentRoom.GetItems();
            for (size_t i = 0; i < roomItems.size(); ++i)
            {
                std::cout << '[' << (i + 1) << "] ";
                roomItems[i].DisplayInfo();
            }
            int backOption = static_cast<int>(roomItems.size()) + 1;
            std::cout << '[' << backOption << "] Back\n";
            
            int itemChoice = -1;
            ForceInput(itemChoice, 1, backOption);
            if (itemChoice != backOption)
            {
                int itemIdx = itemChoice - 1;
                Item itemToPick = roomItems[itemIdx];
                if (myPlayer.AddItem(itemToPick))
                {
                    std::cout << ConsoleColors::StartColor(ConsoleColors::GREEN)
                              << "You picked up " << itemToPick.GetName() << "!"
                              << ConsoleColors::EndColor() << '\n';
                    currentRoom.RemoveItem(itemIdx);
                    myPlayer.TickSpells();
                }
                else
                {
                    std::cout << ConsoleColors::StartColor(ConsoleColors::RED)
                              << "You cannot carry this item! Exceeds carry capacity ("
                              << (myPlayer.GetInventoryWeight() + itemToPick.GetWeight()) << "/"
                              << myPlayer.GetCarryCapacity() << " kg)."
                              << ConsoleColors::EndColor() << '\n';
                }
                Pause();
            }
        }
        else if (selected.type == OptionType::OpenChest)
        {
            ClearScreen();
            DrawBreakerLine(LineType::Hyphen);
            std::cout << "Chests in " << currentRoom.GetName() << ":\n";
            DrawBreakerLine(LineType::Hyphen);
            auto& roomChests = currentRoom.GetChests();
            for (size_t i = 0; i < roomChests.size(); ++i)
            {
                std::cout << '[' << (i + 1) << "] " << roomChests[i].GetName() << '\n';
            }
            int backOption = static_cast<int>(roomChests.size()) + 1;
            std::cout << '[' << backOption << "] Back\n";
            
            int chestChoice = -1;
            ForceInput(chestChoice, 1, backOption);
            if (chestChoice != backOption)
            {
                int chestIdx = chestChoice - 1;
                Chest& chest = roomChests[chestIdx];
                std::vector<Item> dropped = chest.OpenAndTakeItems();
                std::cout << ConsoleColors::StartColor(ConsoleColors::GREEN)
                          << "You opened " << chest.GetName() << "!\n"
                          << ConsoleColors::EndColor();
                if (dropped.empty())
                {
                    std::cout << "The chest was empty.\n";
                }
                else
                {
                    std::cout << "Items dropped onto the floor:\n";
                    for (const Item& droppedItem : dropped)
                    {
                        std::cout << "- ";
                        droppedItem.DisplayInfo();
                        currentRoom.AddItem(droppedItem);
                    }
                }
                currentRoom.RemoveChest(chestIdx);
                myPlayer.TickSpells();
                Pause();
            }
        }
        else if (selected.type == OptionType::ReadSpell)
        {
            ClearScreen();
            DrawBreakerLine(LineType::Hyphen);
            std::cout << "Spell scrolls in " << currentRoom.GetName() << ":\n";
            DrawBreakerLine(LineType::Hyphen);
            const auto& roomSpells = currentRoom.GetSpells();
            for (size_t i = 0; i < roomSpells.size(); ++i)
            {
                std::cout << '[' << (i + 1) << "] ";
                roomSpells[i].DisplayInfo();
            }
            int backOption = static_cast<int>(roomSpells.size()) + 1;
            std::cout << '[' << backOption << "] Back\n";
            
            int spellChoice = -1;
            ForceInput(spellChoice, 1, backOption);
            if (spellChoice != backOption)
            {
                int spellIdx = spellChoice - 1;
                Spell spellToActivate = roomSpells[spellIdx];
                myPlayer.AddSpell(spellToActivate);
                std::cout << ConsoleColors::StartColor(ConsoleColors::GREEN)
                          << "You read and activated " << spellToActivate.GetName() << "!"
                          << ConsoleColors::EndColor() << '\n';
                currentRoom.RemoveSpell(spellIdx);
                myPlayer.TickSpells();
                Pause();
            }
        }
        else if (selected.type == OptionType::Move)
        {
            int targetRoomId = currentRoom.GetConnection(selected.data).GetId();
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
                        myPlayer.TickSpells();
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
                        myPlayer.TickSpells();
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
                myPlayer.TickSpells();
            }
        }
    }
}
