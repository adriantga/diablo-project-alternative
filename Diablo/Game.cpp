#include "Game.h"

#include "BattleController.h"
#include "Helpers.h"

Game::Game(Diablo& aDiablo) : myPlayer("Wanderer", aDiablo, 5, 4, 6)
{
    this->myDiablo = aDiablo;
    
    myRooms = std::vector<Room>();
    myDoors = std::vector<Door>();
    
    Room entranceRoom = Room("Entrance", aDiablo);
    Room cathedralRoom = Room("Cathedral", aDiablo);
    Room armoryRoom = Room("Armory", aDiablo);
    Room kitchenRoom = Room("Kitchen", aDiablo);
    Room cellsRoom = Room("Cells", aDiablo);
    
    entranceRoom.SetId(Rooms::GetRoom(RoomType::EntranceRoom));
    cathedralRoom.SetId(Rooms::GetRoom(RoomType::CathedralRoom));
    armoryRoom.SetId(Rooms::GetRoom(RoomType::ArmoryRoom));
    kitchenRoom.SetId(Rooms::GetRoom(RoomType::KitchenRoom));
    cellsRoom.SetId(Rooms::GetRoom(RoomType::CellsRoom));
    
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
    
    int cathedralEnemyCount = GetRandomNumber(EMPTY, LONE_WOLF);
    int armoryEnemyCount = GetRandomNumber(EMPTY, DUO);
    int kitchenEnemyCount = GetRandomNumber(EMPTY, TRIO);
    int cellsEnemyCount = GetRandomNumber(EMPTY, LONE_WOLF);
    
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
        AddRandomEnemyToRoom(cellsRoom, aDiablo, 4, 4);
    }
    
    LoreItems* loreItems = &aDiablo.loreItems;
    LoreChests* loreChests = &aDiablo.loreChests;
    LoreSpells* loreSpells = &aDiablo.loreSpells;

    entranceRoom.AddItem(myItemFactory.CreateItem(loreItems->wornDagger));

    loreChests->altarChest.AddItem(myItemFactory.CreateItem(loreItems->travelersBoots));
    loreChests->altarChest.AddItem(myItemFactory.CreateItem(loreItems->backpack));

    cathedralRoom.AddChest(loreChests->altarChest);

    armoryRoom.AddSpell(loreSpells->warCry);
    armoryRoom.AddSpell(loreSpells->blessingsOfTheTraveler);
    armoryRoom.AddSpell(loreSpells->mightOfTheWarrior);

    kitchenRoom.AddItem(myItemFactory.CreateItem(loreItems->trophyOfTheHero));
    
    myRooms.push_back(entranceRoom);
    myRooms.push_back(cathedralRoom);
    myRooms.push_back(armoryRoom);
    myRooms.push_back(kitchenRoom);
    myRooms.push_back(cellsRoom);
    
    Door entranceDoor = Door(myRooms[Rooms::GetRoom(RoomType::EntranceRoom)], aDiablo);
    Door cathedralDoor = Door(myRooms[Rooms::GetRoom(RoomType::CathedralRoom)], aDiablo);
    Door armoryDoor = Door(myRooms[Rooms::GetRoom(RoomType::ArmoryRoom)], aDiablo);
    
    int maxRequiredStrength = myPlayer.GetStrength();
    int maxRequiredAgility = myPlayer.GetAgility();
    
    armoryDoor.SetLocked(true, GetRandomNumber(1, maxRequiredStrength), GetRandomNumber(1, maxRequiredAgility));
    
    Door kitchenDoor = Door(myRooms[Rooms::GetRoom(RoomType::KitchenRoom)], aDiablo);
    kitchenDoor.SetLocked(true, GetRandomNumber(1, maxRequiredStrength), GetRandomNumber(1, maxRequiredAgility));
    
    Door cellsDoor = Door(myRooms[Rooms::GetRoom(RoomType::CellsRoom)], aDiablo);
    cellsDoor.SetLocked(true, GetRandomNumber(1, maxRequiredStrength), GetRandomNumber(1, maxRequiredAgility));
    
    myDoors.push_back(entranceDoor);
    myDoors.push_back(cathedralDoor);
    myDoors.push_back(armoryDoor);
    myDoors.push_back(kitchenDoor);
    myDoors.push_back(cellsDoor);
}

void Game::AddRandomEnemyToRoom(Room& aRoom, const Diablo& aDiablo, const int aLowestIndex, const int aHighestIndex) const
{
    Character character = myCharacterFactory.CreateRandomEnemy(aDiablo, aLowestIndex, aHighestIndex);
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

                const int viewStatsIndex = currentRoom.GetEnemyCount() + 1;
                const int viewInventoryIndex = viewStatsIndex + 1;
                int enemyChoice = -1;
                ForceInput(enemyChoice, 1, viewStatsIndex);
                
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
                std::cout << ConsoleColors::StartColor(Color::Red) << "You have died! Game Over." << ConsoleColors::EndColor() << '\n';
                DrawBreakerLine(LineType::EqualSign);
                Pause();
                return;
            }
            
            ClearScreen();
            DrawBreakerLine(LineType::EqualSign);
            std::cout << ConsoleColors::StartColor(Color::Green) << "Room cleared!" << ConsoleColors::EndColor() << '\n';
            DrawBreakerLine(LineType::EqualSign);
            Pause();
        }
        
        if (currentRoom.GetId() == Rooms::GetRoom(RoomType::CellsRoom) || strcmp(currentRoom.GetName(), "Cells") == 0)
        {
            ClearScreen();
            DrawBreakerLine(LineType::EqualSign);
            WriteLine("VICTORY SCREEN");
            DrawBreakerLine(LineType::EqualSign);
            std::cout << ConsoleColors::StartColor(Color::Green) << "Congratulations! You reached the Cells and won the game!" << ConsoleColors::EndColor() << '\n';
            Pause();
            return;
        }
        
        ClearScreen();
        DrawBreakerLine(LineType::Dash);
        WriteLine(currentRoom.GetName());
        DrawBreakerLine(LineType::Dash);
        
        std::vector<ActionOption> options;
        for (int connection = 0; connection < currentRoom.GetConnectionCount(); connection++)
        {
            ActionOption action = {
                OptionType::Move,
                connection,
                "Enter " + std::string(currentRoom.GetConnection(connection).GetName())
            };
            
            options.push_back(action);
        }
        
        if (currentRoom.HasItems())
        {
             ActionOption action = {
                OptionType::PickItem,
                0,
                "Pick up item from the floor"
            };
            
            options.push_back(action);
        }
        
        if (currentRoom.HasChests())
        {
             ActionOption action = {
                OptionType::OpenChest,
                0,
                "Open chest"
            };
            
            options.push_back(action);
        }
        
        if (currentRoom.HasSpells())
        {
             ActionOption action = {
                OptionType::ReadSpell,
                0,
                "Read the scroll"
            };
            
            options.push_back(action);
        }
        
        ActionOption inventory = {
            OptionType::ViewInventory,
            0,
            "View inventory"
        };
        
         ActionOption stats = {
                OptionType::ViewStats,
                0,
                "View stats"
         };

        options.push_back(inventory);
        options.push_back(stats);
        
        for (size_t i = 0; i < options.size(); i++)
        {
            std::cout << '[' << i + 1 << "] " << options[i].text << '\n';
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
            DrawBreakerLine(LineType::Dash);
            std::cout << "Items on the floor in " << currentRoom.GetName() << ":\n";
            DrawBreakerLine(LineType::Dash);
            const std::vector<Item>& roomItems = currentRoom.GetItems();
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
                    std::cout << ConsoleColors::StartColor(Color::Green) << "You picked up " << itemToPick.GetName() << "!" << ConsoleColors::EndColor() << '\n';
                    if (myPlayer.GetHealth() != myPlayer.GetMaxHealth())
                    {
                        myPlayer.ResetHealth();
                    }
                    
                    currentRoom.RemoveItem(itemIdx);
                    myPlayer.TickSpells();
                }
                else
                {
                    std::cout << ConsoleColors::StartColor(Color::Red) << "You cannot carry this item! Exceeds carry capacity (" << (myPlayer.GetInventoryWeight() + itemToPick.GetWeight()) << "/" << myPlayer.GetCarryCapacity() << " kg)." << ConsoleColors::EndColor() << '\n';
                }
                Pause();
            }
        }
        else if (selected.type == OptionType::OpenChest)
        {
            ClearScreen();
            DrawBreakerLine(LineType::Dash);
            std::cout << "Chests in " << currentRoom.GetName() << ":\n";
            DrawBreakerLine(LineType::Dash);
            std::vector<Chest>& roomChests = currentRoom.GetChests();
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
                std::cout << ConsoleColors::StartColor(Color::Green) << "You opened " << chest.GetName() << "!\n" << ConsoleColors::EndColor();
                
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
            DrawBreakerLine(LineType::Dash);
            std::cout << "Spell scrolls in " << currentRoom.GetName() << ":\n";
            DrawBreakerLine(LineType::Dash);
            const std::vector<Spell>& roomSpells = currentRoom.GetSpells();
            
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
                std::cout << ConsoleColors::StartColor(Color::Green) << "You read and activated " << spellToActivate.GetName() << "!" << ConsoleColors::EndColor() << '\n';
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
                        std::cout << ConsoleColors::StartColor(Color::Green) << "You broke the door open!" << ConsoleColors::EndColor() << '\n';
                        Pause();
                        currentRoomIndex = targetRoomId;
                        myPlayer.TickSpells();
                    }
                    else
                    {
                        std::cout << ConsoleColors::StartColor(Color::Red) << "You are not strong enough to break the door!" << ConsoleColors::EndColor() << '\n';
                        Pause();
                    }
                }
                else if (doorChoice == 2)
                {
                    if (myPlayer.GetAgility() >= targetDoor.GetRequiredAgility())
                    {
                        targetDoor.SetLocked(false, 0, 0);
                        std::cout << ConsoleColors::StartColor(Color::Green) << "You successfully picked the lock!" << ConsoleColors::EndColor() << '\n';
                        Pause();
                        currentRoomIndex = targetRoomId;
                        myPlayer.TickSpells();
                    }
                    else
                    {
                        std::cout << ConsoleColors::StartColor(Color::Red) << "You are not agile enough to lock pick the door!" << ConsoleColors::EndColor() << '\n';
                        Pause();
                    }
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