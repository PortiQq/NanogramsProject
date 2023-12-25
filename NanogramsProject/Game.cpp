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
    filled = sf::Color::Black;      
    unfilled = sf::Color::White;

    tileSize = sf::Vector2f(25.f, 25.f);
    outlineColorForTiles = sf::Color::Black;
    outlineThicknessForTiles = 2.f;
    tileMargin = 5.f;

    Tile::setStaticTileParameters(outlineColorForTiles, tileSize, outlineThicknessForTiles);                                                          //Jeśli się wywali to trzeba to przestawić dalej po stworzeniu pierwszego obiektu

    rows = 3;   //tymczasowe rozwiązanie zanim zacznę wczytywać plansze
    cols = 3;   //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    mouseHold = false;

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
    sf::Vector2f position;
    
    Tile tile2(sf::Vector2f(0.f, 0.f), 0, 1);
    for (float rowCounter = 1.f; rowCounter <= rows; rowCounter += 1.f)
        for (float colCounter = 1.f; colCounter <= cols; colCounter += 1.f)
        {
            position = sf::Vector2f(rowCounter * (tileSize.x + tileMargin), colCounter * (tileSize.y + tileMargin));
            tile2.setTilePosition(position);
            this->tiles2.push_back(tile2);
        }

}


void Game::updateBoard()
{
    static bool isMousePressed = false;
    static unsigned short int initialTileStatus = 0;

    for (auto& t : this->tiles2)
    {
        if (t.getTileGlobalBounds().contains(this->viewMousePosition))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (!isMousePressed)
                {
                    isMousePressed = true;
                    initialTileStatus = t.getCurrentStatus();
                }
                if (initialTileStatus == UNFILLED)
                    t.setStatus(FILLED);
                else
                    t.setStatus(UNFILLED);
            }
            else
            {
                isMousePressed = false;
            }
        }
    }
}

void Game::renderTiles()
{
    //Renderowanie kratek
    for (auto& t : this->tiles2)
    {
        this->gameWindow->draw(t.getTile());

    }
}


const bool Game::gameBoardRendered() const
{
    if (this->tiles2.size() > 0)
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
    this->pollEvents();
    this->updateMousePosition();
    this->updateBoard();
}


void Game::render()
{
    //Wypełnienie okna
    this->gameWindow->clear(backgroundColor);
    //rysowanie obiektów
    this->renderTiles();
    //Wyświetlenie zawartości w oknie
    this->gameWindow->display();
}


