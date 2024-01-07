#include "Game.h"

Game::Game()    //Konstruktor okna głównego gry
{
    this->initialiseVariables();
    this->createWindow();
    this->initialiseStates();
}


Game::~Game()   //destruktor klasy okna gry
{
    std::cout << "Destruktor game: Usuwane sa wszystkie stany\n";
    delete this->gameWindow;

    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
        
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
   
    //Inicjalizacja szczegółów podpowiedzi
    this->textColorForClues = sf::Color::Black;
    this->outlineThicknessForClues = 1.f;
    this->characterSizeForClues = 18;
    Clue::setStaticCluesParameters(textColorForClues, tileSize, outlineThicknessForClues, tileMargin, characterSizeForClues);
    
    //Inicjalizacja pliku poziomu
    this->inputFile = std::ifstream("Levels/level1.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        exit(1);
    }

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


void Game::initialiseStates()
{
    //this->states.push(new GameState((this->gameWindow), &this->states)); //TODO: Będzie zaczynało się od menu raczej
    this->states.push(new MainMenu((this->gameWindow), &this->states));
}


const bool Game::gameRunning() const    //sprawdza czy okno gry jest otwarte
{
    return this->gameWindow->isOpen();
}


void Game::pollEvents()  //metoda do obsługi zdarzeń okna
{
    while (this->gameWindow->pollEvent(event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->gameWindow->close();
            break;
        default:
            break;
        }
    }
}


void Game::update()
{
    this->pollEvents();                         //Obsługa zdarzeń w oknie

    if (!this->states.empty())  //Obsługa stanów
    {
        this->states.top()->update();  //Update bieżącego stanu

        if (this->states.top()->getQuit())  //Wychodzenie z bieżącego stanu
        {
            this->states.top()->endState();

            delete this->states.top();  //Zwalnianie pamięci po stanie
            this->states.pop();         //Board także jest usuwana
        }
    }
    else    //Gdy wszystkie stany są zamknięte - koniec działania programu
    {
        this->endApplication();
        this->gameWindow->close();
    }
}


void Game::render()
{
    this->gameWindow->clear(backgroundColor);   //Wypełnienie okna kolorem

    if (!this->states.empty())                          //Dopóki istnieje jakikolwiek stan aplikacji
        this->states.top()->render(this->gameWindow);   //Obiekty są rysowane na ekranie

    this->gameWindow->display();                //Wyświetlenie zawartości w oknie
}


void Game::runGame()
{
    while (gameRunning())
    {
        if (!this->states.empty())  
        {
            if (!this->states.top()->checkIfSetUp())
                this->states.top()->setUpState(this->inputFile);
        }
        this->render();
        this->update();
    }
}

void Game::endApplication()
{
    std::cout << "Ending application\n";
}

