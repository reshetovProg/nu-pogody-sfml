#include "Game.h"
#include <Windows.h>


int main()
{
    srand(time(NULL));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Game game;
    game.run();
    
}