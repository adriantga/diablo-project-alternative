#include "BattleController.h"

#include <iostream>

#include "Game.h"
#include "Helpers.h"
#include "Room.h"

void BattleController::DisplayHealth(const Character& aPlayer, const Character& aEnemy)
{
    DisplayHealth(aPlayer);
    DisplayHealth(aEnemy);
    
    if (aPlayer.IsAlive()) std::cout << "Player Health: " << aPlayer.GetHealth() << " / " << aPlayer.GetMaxHealth() << '\n';
    if (aEnemy.IsAlive()) std::cout << "Enemy Health: " << aEnemy.GetHealth() << " / " << aEnemy.GetMaxHealth() << '\n';
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

void BattleController::Battle(Diablo& aDiablo, Game& aGame, Character& aEnemy)
{
    while (aGame.GetPlayer().IsAlive() && aEnemy.IsAlive())
    {
        int playerDamage = CalculateDamage(aGame.GetPlayer(), aEnemy);
        if (aDiablo.cheats.hasOneShot)
        {
            playerDamage = 9999999;
            std::cout << ConsoleColors::StartColor(ConsoleColors::GREEN) << "One shot is currently active!" << ConsoleColors::EndColor() << '\n';
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
            std::cout << ConsoleColors::StartColor(ConsoleColors::GREEN) << "God mode is active. Enemy dealt 0 damage." << ConsoleColors::EndColor() << '\n';
        }
        
        aGame.GetPlayer().TakeDamage(enemyDamage);
        std::cout << aEnemy.GetCharacterName() << " dealt " << enemyDamage << " damage to Player\n";
    }
}

void BattleController::Battle(Game& aGame, Character& aPlayer, Character& aEnemy)
{
    Diablo diablo = aGame.GetDiablo();
    Battle(diablo, aGame, aEnemy);
    aPlayer = aGame.GetPlayer();
}

void BattleController::BattleTurn(Diablo& aDiablo, Game& aGame, Room& aRoom, int aTargetIndex)
{
    if (aTargetIndex < 0 || aTargetIndex >= aRoom.GetEnemyCount())
    {
        return;
    }
    
    ClearScreen();
    Character& targetEnemy = aRoom.GetEnemyRef(aTargetIndex);
    
    int playerDamage = CalculateDamage(aGame.GetPlayer(), targetEnemy);
    if (aDiablo.cheats.hasOneShot)
    {
        playerDamage = 9999999;
        std::cout << ConsoleColors::StartColor(ConsoleColors::GREEN) << "One shot is currently active!" << ConsoleColors::EndColor() << '\n';
    }
    
    targetEnemy.TakeDamage(playerDamage);
    std::cout << "Player dealt " << playerDamage << " damage to " << targetEnemy.GetCharacterName() << '\n';
    
    if (!targetEnemy.IsAlive())
    {
        std::cout << targetEnemy.GetCharacterName() << " has been defeated!\n";
    }
    
    for (int i = 0; i < aRoom.GetEnemyCount(); i++)
    {
        Character& enemy = aRoom.GetEnemyRef(i);
        if (enemy.IsAlive())
        {
            int enemyDamage = CalculateDamage(enemy, aGame.GetPlayer());
            
            if (aDiablo.cheats.hasGodMode)
            {
                enemyDamage = 0;
                std::cout << ConsoleColors::StartColor(ConsoleColors::GREEN) << "God mode is active. Enemy dealt 0 damage." << ConsoleColors::EndColor() << '\n';
            }
            
            aGame.GetPlayer().TakeDamage(enemyDamage);
            std::cout << enemy.GetCharacterName() << " dealt " << enemyDamage << " damage to Player\n";
        }
    }
    
    aRoom.RemoveDeadEnemies();
}