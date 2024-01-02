#include "Game.h"

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

    //Tu się zaczyna kod gry

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