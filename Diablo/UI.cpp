#include "UI.h"

#include "Game.h"
#include "Helpers.h"

namespace MainMenu
{
    void Draw(Diablo& aDiablo)
    {
        constexpr int PLAY_GAME = 1;
        constexpr int ACTIVATE_CHEATS = 2;
        constexpr int QUIT = 3;
        
        bool shouldQuit = false;
        while (!shouldQuit)
        {
            ClearScreen();
            DrawMenuLine(LineType::EqualSign);
            WriteLine("MAIN MENU");
            DrawMenuLine(LineType::EqualSign);
            WriteLine("[1] Play Game\n[2] Activate Cheats\n[3] Quit Game");
            
            int input = -1;
            ForceInput(input, PLAY_GAME, QUIT);

            switch (input)
            {
            case PLAY_GAME:
            {
                ClearScreen();
                Game newGame = Game(aDiablo);
                newGame.PlayGame(aDiablo);
                break;
            }
            case ACTIVATE_CHEATS:
                CheatsMenu::Draw(aDiablo);
                break;
            case QUIT:
                shouldQuit = true;
                break;
            default:
                std::cout << ConsoleColors::StartColor(Color::Magenta) << "Invalid input" << ConsoleColors::EndColor() << '\n';
                break;
            }
        }
    }
}

namespace CheatsMenu
{
    namespace 
    {
        std::string PrintState(const bool& aState)
        {
            return aState ? "ON" : "OFF";
        }
        
        std::string ColorState(const bool aState, const std::string& aText)
        {
           return ConsoleColors::StartColor(aState ? Color::Green : Color::Red) + aText + ConsoleColors::EndColor();
        }
        
        void Flip(bool& aToFlip)
        {
            aToFlip = !aToFlip;
        }

        void Redraw(const Diablo& aDiablo)
        {
            DrawMenuLine(LineType::Dash);
            WriteLine("CHEATS MENU");
            DrawMenuLine(LineType::Dash);

            const std::string godModeState = PrintState(aDiablo.cheats.hasGodMode);
            const std::string oneShotState = PrintState(aDiablo.cheats.hasOneShot);
            
            std::cout << "[1] God Mode: " << ColorState(aDiablo.cheats.hasGodMode, godModeState) << '\n';
            std::cout << "[2] One Shot: " <<ColorState(aDiablo.cheats.hasOneShot, oneShotState) << '\n';
            WriteLine("[3] Go Back");
        }
    }
    
    void Draw(Diablo& aDiablo)
    {
        constexpr int GOD_MODE = 1;
        constexpr int ONE_SHOT = 2;
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
            case ONE_SHOT:
                Flip(aDiablo.cheats.hasOneShot);
                break;
            case GO_BACK:
                shouldQuit = true;
                break;
            default:
                std::cout << ConsoleColors::StartColor(Color::Magenta) << "Invalid input" << ConsoleColors::EndColor() << '\n';
                break;
            }
        }
        
        ClearScreen();
    }
}
