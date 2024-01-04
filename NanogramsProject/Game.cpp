#include "Game.h"

Game::Game()    //Konstruktor okna głównego gry
{
    this->initialiseVariables();
    this->createWindow();
}


Game::~Game()   //destruktor klasy okna gry
{
    std::cout << "Destruktor game";
    delete this->gameWindow;
}


void Game::initialiseVariables()
{
    //Inicjalizacja szczegółów okna
    this->gameWindow = nullptr;
    backgroundColor = sf::Color(180, 170, 145, 255);

    //Inicjalizacja szczegółów kratek
    this->tileSize = sf::Vector2f(25.f, 25.f);
    this->outlineColorForTiles = sf::Color::Black;
    this->outlineThicknessForTiles = 2.f;
    this->tileMargin = 5.f;
    Tile::setStaticTileParameters(outlineColorForTiles, tileSize, outlineThicknessForTiles, tileMargin);
   
    //Inicjalizacja szczegółów text boxów
    this->textColorForTextBox = sf::Color::Black;
    this->outlineThicknessForTextBox = 0.f;
    characterSizeForTextBox = 20;
    Clue::setStaticTextBoxParameters(textColorForTextBox, tileSize, outlineThicknessForTextBox, tileMargin, characterSizeForTextBox);
    
    //Inicjalizacja pliku poziomu
    this->inputFile = std::ifstream("Levels/level1.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        exit(1);
    }

    //Ładowanie czcionki z pliku
    if (!font.loadFromFile("Fonts/arial.ttf")) {
        std::cerr << "Error loading font\n";
        exit(1);
    }
    Clue number(font, backgroundColor);

}


void Game::createWindow()   //Tworzenie okna gry
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->title = "Nanograms";
    this->style = sf::Style::Titlebar | sf::Style::Close;
    this->gameWindow = new sf::RenderWindow(videoMode, title, style);
    this->gameWindow->setFramerateLimit(60);
    if (icon.loadFromFile("Images/cross.png"))     //Ustawienie ikony okna 
        this->gameWindow->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

}


void Game::setUpGameBoard()
{
    board.setUpLevel(inputFile);
}


void Game::updateBoard()
{
    board.updateBoard(viewMousePosition);
 }

void Game::renderGameBoard()
{
    //Renderowanie kratek
    board.drawBoard(*this->gameWindow);
    //Clue number1(font, backgroundColor);
    //number1.draw(*this->gameWindow);
    number.draw(*this->gameWindow);
}


const bool Game::gameBoardCreated() const
{
    if (board.getBoard().size() > 0)
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
    this->board.checkIfCompleted();
}


void Game::render()
{
    this->gameWindow->clear(backgroundColor);   //Wypełnienie okna kolorem
    this->renderGameBoard();                    //rysowanie obiektów
    this->gameWindow->display();                //Wyświetlenie zawartości w oknie
}


