#include "Game.h"
#include "UI.h"
#include "Utilities.h"

int main()
{
    Cheats cheats = {};
    
    Diablo diablo = { cheats };
    Game game = Game(diablo);
    
    MainMenu::Draw(diablo, game);
    return 0;
}