#include "Game.h"

Game::Game()    //Konstruktor okna głównego gry
{
    this->initialiseVariables();
    this->createWindow();

}


Game::~Game()   //destruktor klasy okna gry
{
    delete this->gameWindow;
}


void Game::initialiseVariables()
{
    //Inicjalizacja szczegółów okna
    this->gameWindow = nullptr;
    backgroundColor = sf::Color(180, 170, 145, 255);

    //Inicjalizacja szczegółów kratek
    tileSize = sf::Vector2f(25.f, 25.f);
    outlineColorForTiles = sf::Color::Black;
    outlineThicknessForTiles = 2.f;
    tileMargin = 5.f;

    Tile::setStaticTileParameters(outlineColorForTiles, tileSize, outlineThicknessForTiles, tileMargin);                                                          //Jeśli się wywali to trzeba to przestawić dalej po stworzeniu pierwszego obiektu

    rows = 10;   //tymczasowe rozwiązanie zanim zacznę wczytywać plansze
    cols = 15;   //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    board = Board(rows, cols);

}


void Game::createWindow()   //Tworzenie okna gry
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->title = "Nanograms";
    this->style = sf::Style::Titlebar | sf::Style::Close;
    this->gameWindow = new sf::RenderWindow(videoMode, title, style);
    this->gameWindow->setFramerateLimit(60);
    if (icon.loadFromFile("image.png"))     //Ustawienie ikony okna 
        this->gameWindow->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

}


void Game::setUpBoard()
{
    board.setUpBoard(rows,cols);
}


void Game::updateBoard()
{
    board.updateBoard(viewMousePosition);
 }

void Game::renderGameBoard()
{
    //Renderowanie kratek
    for (auto &t : board.getTiles())
    {
        this->gameWindow->draw(t.getTile());

    }
}


const bool Game::gameBoardRendered() const
{
    if (board.getTiles().size() > 0)
        return true;
    return false;
}


const bool Game::gameRunning() const    //sprawdza czy okno gry jest otwarte
{
    return this->gameWindow->isOpen();
}


void Game::pollEvents()  //metoda do obsługi zdarzeń
{
    while (this->gameWindow->pollEvent(event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->gameWindow->close();
            break;
        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape)
                this->gameWindow->close();
            break;
        }
    }
}


void Game::updateMousePosition()
{
    this->windowMousePosition = sf::Mouse::getPosition(*this->gameWindow);
    this->viewMousePosition = this->gameWindow->mapPixelToCoords(this->windowMousePosition);
}


void Game::update()
{
    this->pollEvents();                         //Obsługa zdarzeń w oknie
    this->updateMousePosition();                //Aktualizacja pozycji myszy
    this->updateBoard();                        //Aktualizacja planszy
}


void Game::render()
{
    this->gameWindow->clear(backgroundColor);   //Wypełnienie okna kolorem
    this->renderGameBoard();                    //rysowanie obiektów
    this->gameWindow->display();                //Wyświetlenie zawartości w oknie
}


