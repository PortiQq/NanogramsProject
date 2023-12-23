#include "Game.h"

Game::Game()    //Konstruktor okna głównego gry
{
    this->initialiseVariables();
    this->createWindow();
    this->initialiseTiles();
}

Game::~Game()   //destruktor klasy okna gry
{
    delete this->gameWindow;
}

void Game::initialiseVariables()
{
    this->gameWindow = nullptr;
    backgroundColor = sf::Color(180, 170, 145, 255);

    filled = sf::Color::Black;      //Ustalenie szczegółów kratek
    unfilled = sf::Color::White;
    tileSize = sf::Vector2f(25.f, 25.f);
    tileMargin = 5.f;

    rows = 15;   //tymczasowe rozwiązanie zanim zacznę wczytywać plansze
    cols = 15;   //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

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
    if (icon.loadFromFile("image.png"))
        this->gameWindow->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

}

void Game::initialiseTiles()   //Tworzy kratkę
{
    this->tile.setPosition(sf::Vector2f(10.f, 10.f));  //Pozycja startowa
    this->tile.setSize(this->tileSize);
    this->tile.setFillColor(sf::Color::White);
    this->tile.setOutlineColor(sf::Color::Black);
    this->tile.setOutlineThickness(2.f);

}


void Game::setUpBoard()
{
    sf::Vector2f position;

    for (float rowCounter = 1.f; rowCounter <= rows; rowCounter += 1.f)
        for (float colCounter = 1.f; colCounter <= cols; colCounter += 1.f)
        {
            position = sf::Vector2f(rowCounter * (tileSize.x + tileMargin), colCounter * (tileSize.y + tileMargin));
            this->tile.setPosition(position);
            this->tiles.push_back(this->tile);
        }

}


void Game::updateTiles()
{
    static bool isMousePressed = false;
    static sf::Color initialTileColor;

    for (auto& t : this->tiles)
    {
        if (t.getGlobalBounds().contains(this->viewMousePosition))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (!isMousePressed)
                {
                    isMousePressed = true;
                    initialTileColor = t.getFillColor();
                }
                if (initialTileColor == unfilled)
                    t.setFillColor(filled);
                else
                    t.setFillColor(unfilled);
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
    for (auto& t : this->tiles)
    {
        this->gameWindow->draw(t);
    }
}

const bool Game::gameBoardRendered() const
{
    if (this->tiles.size() > 0)
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
    this->updateTiles();
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


