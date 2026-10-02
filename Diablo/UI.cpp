#include "UI.h"

#include <iostream>

#include "Helpers.h"

namespace MainMenu
{
    void Draw(Diablo& aDiablo)
    {
        constexpr int PLAY_GAME = 1;
        constexpr int ACTIVATE_CHEATS = 2;
        constexpr int QUIT_GAME = 3;
        
        DrawMenuLine(LineType::Hyphen);
        WriteLine("DIABLO");
        DrawMenuLine(LineType::Hyphen);
        WriteLine("[1] Play Game\n[2] Activate Cheats\n[3] Quit Game");
        
        int input;
        ForceInput(input, PLAY_GAME, QUIT_GAME);

        switch (input)
        {
        case PLAY_GAME:
            ClearScreen();
            WriteLine("Quit playing with me man :(");
            break;
        case ACTIVATE_CHEATS:
            CheatsMenu::Draw(aDiablo);
            break;
        case QUIT_GAME:
            Exit();
            break;
        }
    }
}

namespace CheatsMenu
{
    static std::string PrintState(bool& aState)
    {
        return aState ? "ON" : "OFF";
    }
    
    void Flip(bool& aToFlip)
    {
        aToFlip = !aToFlip;
    }
    
    static void Redraw(Diablo& aDiablo)
    {
        DrawMenuLine(LineType::Hyphen);
        WriteLine("CHEATS MENU");
        DrawMenuLine(LineType::Hyphen);
        std::cout << "[1] God Mode: " << PrintState(aDiablo.cheats.hasGodMode) << '\n';
        std::cout << "[2] Instant Hit: " << PrintState(aDiablo.cheats.hasInstantWin) << '\n';
        WriteLine("[3] Go Back");
    }
    
    void Draw(Diablo& aDiablo)
    {
        ClearScreen();
        Redraw(aDiablo);
        
        constexpr int GOD_MODE = 1;
        constexpr int INSTANT_HIT = 2;
        constexpr int GO_BACK = 3;

        bool shouldQuit = false;
        while (!shouldQuit)
        {
            ClearScreen();
            Redraw(aDiablo);
            int input = -1;
            
            ForceInput(input, GOD_MODE, GO_BACK);

            switch (input)
            {
            case GOD_MODE:
                Flip(aDiablo.cheats.hasGodMode);
                break;
            case INSTANT_HIT:
                Flip(aDiablo.cheats.hasInstantWin);
                break;
            case GO_BACK:
                shouldQuit = true;
                break;
            }
        }
        
        ClearScreen();
        MainMenu::Draw(aDiablo);
    }
}
