#include "Game.h"

int main()
{
    Game game;  //utworzenie obiektu gry
    if (game.gameRunning())
    {
        if (!game.gameBoardCreated())
            game.setUpGameBoard();

        while (game.gameRunning())  //Główna pętla gry
        {
            game.render();
            game.update();
        }
    }
    return 0;
}