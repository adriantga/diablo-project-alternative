#include "UI.h"
#include "Utilities.h"

int main()
{
    const Cheats cheats = {};
    const LoreItems loreItems = {};
    const LoreChests loreChests = {};
    const LoreSpells loreSpells = {};
    
    Diablo diablo = { loreItems, loreSpells, loreChests, cheats };
    MainMenu::Draw(diablo);
    
    return 0;
}