#pragma once
#include "Character.h"
#include "Game.h"
#include "Room.h"

class BattleController
{
    static void DisplayHealth(const Character& aCharacter);
    static void DisplayHealth(const Character& aPlayer, const Character& aEnemy);
    static void DisplayHealth(const Character& aPlayer, const std::vector<Character>& aEnemies);
public:
    static void Battle(Diablo& aDiablo, Game& aGame, Character& aEnemy);
    static void Battle(Game& aGame, Character& aPlayer, Character& aEnemy);
    static void BattleTurn(Diablo& aDiablo, Game& aGame, Room& aRoom, int aTargetIndex);
};
