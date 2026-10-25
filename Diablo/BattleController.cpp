#include "BattleController.h"

#include "Helpers.h"

static void DropEnemyLoot(Room& aRoom, const Character& aDeadEnemy, const LoreItems& aLoreItems, const ItemFactory& aItemFactory)
{
    if (aLoreItems.enemyDrops.empty())
    {
        return;
    }

    constexpr int MIN_ROLL = 1;
    constexpr int MAX_ROLL = 100;

    if (GetRandomNumber(MIN_ROLL, MAX_ROLL) <= 60)
    {
        const int dropCount = static_cast<int>(aLoreItems.enemyDrops.size());
        const int roll = GetRandomNumber(0, dropCount - 1);

        ItemID dropID = aLoreItems.enemyDrops[roll];
        Item drop = aItemFactory.CreateItem(dropID);
        aRoom.AddItem(drop);
        std::cout << ConsoleColors::StartColor(Color::Blue) << aDeadEnemy.GetCharacterName() << " dropped: ";
        drop.DisplayInfo();
        std::cout << ConsoleColors::EndColor();
    }
}

void BattleController::DisplayHealth(const Character& aPlayer, const Character& aEnemy)
{
    DisplayHealth(aPlayer);
    DisplayHealth(aEnemy);
}

void BattleController::DisplayHealth(const Character& aPlayer, const std::vector<Character>& aEnemies)
{
    DisplayHealth(aPlayer);
    
    for (const Character& enemy : aEnemies)
    {
        DisplayHealth(enemy);
    }
}

void BattleController::DisplayHealth(const Character& aCharacter)
{
    if (aCharacter.IsAlive()) std::cout << aCharacter.GetCharacterName() << " Health: " << aCharacter.GetHealth() << " / " << aCharacter.GetMaxHealth() << '\n';
}

void BattleController::Battle(const Diablo& aDiablo, Game& aGame, Character& aEnemy)
{
    while (aGame.GetPlayer().IsAlive() && aEnemy.IsAlive())
    {
        int playerDamage = CalculateDamage(aGame.GetPlayer(), aEnemy);
        if (aDiablo.cheats.hasOneShot)
        {
            playerDamage = 9999999;
            std::cout << ConsoleColors::StartColor(Color::Green) << "One shot is currently active!" << ConsoleColors::EndColor() << '\n';
        }
        
        aEnemy.TakeDamage(playerDamage);
        std::cout << "Player dealt " << playerDamage << " damage to " << aEnemy.GetCharacterName() << '\n';
        
        if (!aEnemy.IsAlive())
        {
            std::cout << aEnemy.GetCharacterName() << " has been defeated!\n";
            break;
        }
        
        int enemyDamage = CalculateDamage(aEnemy, aGame.GetPlayer());
        if (aDiablo.cheats.hasGodMode)
        {
            enemyDamage = 0;
            std::cout << ConsoleColors::StartColor(Color::Green) << "God mode is active. Enemy dealt 0 damage." << ConsoleColors::EndColor() << '\n';
        }
        
        aGame.GetPlayer().TakeDamage(enemyDamage);
        std::cout << aEnemy.GetCharacterName() << " dealt " << enemyDamage << " damage to Player\n";
    }
}

void BattleController::Battle(Game& aGame, Character& aPlayer, Character& aEnemy)
{
    const Diablo diablo = aGame.GetDiablo();
    Battle(diablo, aGame, aEnemy);
    aPlayer.Set(aGame.GetPlayer());
}

void BattleController::BattleTurn(const Diablo& aDiablo, Game& aGame, Room& aRoom, const int aTargetIndex)
{
    if (aTargetIndex < 0 || aTargetIndex >= aRoom.GetEnemyCount())
    {
        return;
    }
    
    ClearScreen();
    Character& targetEnemy = aRoom.GetEnemyReference(aTargetIndex);
    
    int playerDamage = CalculateDamage(aGame.GetPlayer(), targetEnemy);
    if (aDiablo.cheats.hasOneShot)
    {
        playerDamage = 9999999;
        std::cout << ConsoleColors::StartColor(Color::Green) << "One shot is currently active!" << ConsoleColors::EndColor() << '\n';
    }
    
    targetEnemy.TakeDamage(playerDamage);
    std::cout << "Player dealt " << playerDamage << " damage to " << targetEnemy.GetCharacterName() << '\n';
    
    if (!targetEnemy.IsAlive())
    {
        std::cout << targetEnemy.GetCharacterName() << " has been defeated!\n";
        DropEnemyLoot(aRoom, targetEnemy, aGame.GetDiablo().loreItems, aGame.GetItemFactory());
    }
    
    for (int i = 0; i < aRoom.GetEnemyCount(); i++)
    {
        Character& enemy = aRoom.GetEnemyReference(i);
        if (enemy.IsAlive())
        {
            int enemyDamage = CalculateDamage(enemy, aGame.GetPlayer());
            
            if (aDiablo.cheats.hasGodMode)
            {
                enemyDamage = 0;
                std::cout << ConsoleColors::StartColor(Color::Green) << "God mode is active. Enemy dealt 0 damage." << ConsoleColors::EndColor() << '\n';
            }
            
            aGame.GetPlayer().TakeDamage(enemyDamage);
            std::cout << enemy.GetCharacterName() << " dealt " << enemyDamage << " damage to Player\n";
        }
    }
    
    aRoom.RemoveDeadEnemies();
}