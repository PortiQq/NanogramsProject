#include "Game.h"
#include <iostream>

int main()
{

    //Ładowanie tekstury z pamięci
    sf::Texture texture;
    if (!texture.loadFromFile("image.png"))
    {
        std::cout << "Wyebao sie";
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    //



    Game game;  //utworzenie obiektu gry
    if (game.gameRunning())
    {
        if (!game.gameBoardRendered())
            game.setUpBoard();

        while (game.gameRunning())  //Główna pętla gry
        {
            game.render();
            game.update();
        }
    }


    //system("pause");
    return 0;
}