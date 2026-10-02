#include "Character.h"
#include "UI.h"
#include "Utilities.h"

int main()
{
    Character player = Character("Wanderer", 5, 4, 60);
    Cheats cheats = {};
    
    Diablo diablo = { &player, cheats };
    
    MainMenu::Draw(diablo);
    return 0;
}