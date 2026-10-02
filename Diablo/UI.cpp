#include "UI.h"

#include <iostream>

#include "Game.h"
#include "Helpers.h"

namespace MainMenu
{
    void Draw(Diablo& aDiablo, Game& aGame)
    {
        constexpr int PLAY_GAME = 1;
        constexpr int ACTIVATE_CHEATS = 2;
        constexpr int QUIT_GAME = 3;
        
        bool shouldQuit = false;
        while (!shouldQuit)
        {
            ClearScreen();
            DrawMenuLine(LineType::Hyphen);
            WriteLine("DIABLO");
            DrawMenuLine(LineType::Hyphen);
            WriteLine("[1] Play Game\n[2] Activate Cheats\n[3] Quit Game");
            
            int input = -1;
            ForceInput(input, PLAY_GAME, QUIT_GAME);

            switch (input)
            {
            case PLAY_GAME:
            {
                ClearScreen();
                Game newGame(aDiablo);
                newGame.PlayGame(aDiablo);
                break;
            }
            case ACTIVATE_CHEATS:
                CheatsMenu::Draw(aDiablo, aGame);
                break;
            case QUIT_GAME:
                shouldQuit = true;
                break;
            default:
                std::cout << ConsoleColors::StartColor(ConsoleColors::RED) << "ERROR. Invalid index." << ConsoleColors::EndColor();
                break;
            }
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
    
    void Redraw(Diablo& aDiablo)
    {
        DrawMenuLine(LineType::Hyphen);
        WriteLine("CHEATS MENU");
        DrawMenuLine(LineType::Hyphen);
        
        std::string godModeState = PrintState(aDiablo.cheats.hasGodMode);
        std::string instantHitState = PrintState(aDiablo.cheats.hasOneShot);
        
        std::cout << "[1] God Mode: " << ConsoleColors::StartColor(aDiablo.cheats.hasGodMode ? ConsoleColors::GREEN : ConsoleColors::RED) << godModeState << ConsoleColors::EndColor() << '\n';
        std::cout << "[2] Instant Hit: " << ConsoleColors::StartColor(aDiablo.cheats.hasOneShot ? ConsoleColors::GREEN : ConsoleColors::RED) << instantHitState << ConsoleColors::EndColor() << '\n';
        WriteLine("[3] Go Back");
    }
    
    void Draw(Diablo& aDiablo, Game& aGame)
    {
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
                Flip(aDiablo.cheats.hasOneShot);
                break;
            case GO_BACK:
                shouldQuit = true;
                break;
            default:
                std::cout << ConsoleColors::StartColor(ConsoleColors::RED) << "ERROR. Invalid index." << ConsoleColors::EndColor();
                break;
            }
        }
        
        ClearScreen();
    }
}
