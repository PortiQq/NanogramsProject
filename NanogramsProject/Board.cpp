#include "Board.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>


Board::Board(short rows, short cols) : rows(rows), cols(cols), gridHeight(rows), gridWidth(cols)
{
	//
}


Board::Board() : rows(0), cols(0), gridHeight(rows), gridWidth(cols)
{
	//
}


Board::~Board()
{
    for (auto& tileRow : this->board)   //Zwalnianie pamięci planszy
    {
        for (auto& tile : tileRow)
        {
            delete tile;
        }
        tileRow.clear();
    }
    board.clear();

    for (auto& clueRow : this->horizontalClues) //Zwalnianie pamięci tablicy podpowiedzi poziomych
    {
        for (auto& clue : clueRow)
        {
            delete clue;
        }
        clueRow.clear();
    }
    horizontalClues.clear();

    for (auto& clueCol : this->verticalClues) //Zwalnianie pamięci tablicy podpowiedzi pionowych
    {
        for (auto& clue : clueCol)
        {
            delete clue;
        }
        clueCol.clear();
    }
    verticalClues.clear();

    std::cout << "Destruktor board";
}

void Board::checkDimensions(std::ifstream &inputLevel)
{
    int xMax = 0, yMax = 0;
    std::string line;

    while (std::getline(inputLevel, line)) {
        int x, y;
        std::istringstream iss(line);
        if (iss >> x >> y) {
            std::cout <<"Odczyt w funkcji checkDimensions: " << x << " " << y << std::endl;
        
            if (x > xMax)
                xMax = x;
            if (y > yMax)
                yMax = y;
        }
        else {
            std::cerr << "Error reading line: " << line << std::endl;
        }

    }
    inputLevel.clear();
    inputLevel.seekg(0, std::ios::beg);

    this->rows = xMax + 1;
    this->cols = yMax + 1;
}


void Board::createBoard()
{
    std::vector<Tile*> tileRow;
    for (int rowCounter = 0; rowCounter < this->rows; rowCounter++)
    {
        tileRow.clear();
        for (int colCounter = 0; colCounter < this->cols; colCounter++)
        {
            tileRow.push_back(new Tile());
        }
        this->board.push_back(tileRow);
    }
}


void Board::setUpTiles(std::ifstream& inputLevel)
{
    std::cout << "Setting up level..." << std::endl;
    std::string line;

    while (std::getline(inputLevel, line)) {
        std::istringstream iss(line);
        int x = 0, y = 0;
        if (iss >> x >> y) {
            std::cout << "Odczyt w funkcji setUpLevel: " << x << " " << y << std::endl;
            this->board[x][y]->setTargetStatus(FILLED);
        }
        else {
            std::cerr << "Error reading line: " << line << std::endl;
        }
    }
}


void Board::setUpClues()
{
    unsigned short counter = 0;
    std::vector<Clue*> clueRow;
    std::vector<Clue*> clueCol;
    size_t maxWidth = 0, maxHeight = 0;

    for (int i = 0; i < this->rows; i++)    //Zewnętrzna pętla - wiersze podpowiedzi
    {
        for (int j = 0; j < this->cols; j++)    //Wewnętrzna pętla - poszczególne kratki
        {
            bool check = this->board[i][j]->getTargetStatus() == 1;
            bool end = (j == cols - 1);
            if (check == true)
            {
                counter++;
                if (end)    //Gdy na końcu wiersza jest kratka pełna
                {
                    clueRow.push_back(new Clue(counter));
                    counter = 0;
                }
                    
            }
            else            //Gdy pojawi się kratka pusta ==> podsumowanie i stworzenie podpowiedzi
            {
                if (counter > 0) 
                {
                    clueRow.push_back(new Clue(counter));
                    counter = 0;
                }
            }    
        }
        if (clueRow.size() > maxWidth)
            maxWidth = clueRow.size();

        this->horizontalClues.push_back(clueRow);
        clueRow.clear();
        counter = 0;
    }


    for (int i = 0; i < this->cols; i++)    //Zewnętrzna pętla - wiersze podpowiedzi
    {
        for (int j = 0; j < this->rows; j++)    //Wewnętrzna pętla - poszczególne kratki
        {
            bool check = this->board[j][i]->getTargetStatus() == 1;
            bool end = (j == rows - 1);
            if (check == true)
            {
                counter++;
                if (end)    //Gdy na końcu jest kratka do zamalowania
                {
                    clueCol.push_back(new Clue(counter));
                    counter = 0;
                }

            }
            else            //Gdy pojawi się kratka pusta ==> podsumowanie i stworzenie podpowiedzi
            {
                if (counter > 0)
                {
                    clueCol.push_back(new Clue(counter));
                    counter = 0;
                }
            }
        }
        if (clueCol.size() > maxHeight)
            maxHeight = clueCol.size();
        this->verticalClues.push_back(clueCol);
        clueCol.clear();
        counter = 0;
    }

    this->gridWidth = this->cols + (short)maxWidth;        //Ustawienie ilości obiektów do wyrenderowania
    this->gridHeight = this->rows + (short)maxHeight;      //(Do zarezerwowania miejsca w oknie)
}


void Board::setUpPositions()
{
    unsigned short maxCluesWidth = this->gridWidth - this->cols;
    unsigned short maxCluesHeight = this->gridHeight - this->rows;

    sf::Vector2f oneTileSize = Tile::getTileSize();
    float tileMargin = Tile::getTileMargin();
    float boxMargin = Clue::getBoxMargin();

    sf::Vector2f tilesPosition = sf::Vector2f(  //Pozycja startowa kratek planszy
        maxCluesWidth * oneTileSize.x + tileMargin + 100.f, 
        maxCluesHeight * oneTileSize.y + tileMargin + 100.f);  

    sf::Vector2f horizontalCluesPosition = sf::Vector2f(    //Pozycja startowa podpowiedzi dla wierszy
        tilesPosition.x,
        tilesPosition.y - oneTileSize.y - tileMargin);  

    sf::Vector2f verticalCluesPosition = sf::Vector2f(  //Pozycja startowa podpowiedzi dla kolumn
        tilesPosition.x,
        tilesPosition.y - oneTileSize.y - tileMargin);  
    

    for (int row = 0; row < this->rows; row++)  //Ustalanie pozycji kratek planszy
    {
        for (int col = 0; col < this->cols; col++)
        {
            this->board[row][col]->setTilePosition  (
                tilesPosition.y + (oneTileSize.y + tileMargin) * col,
                tilesPosition.x + (oneTileSize.x + tileMargin) * row    );
        }
    }

    int rowCounter = 0;
    int forwI = 0;  //forward iterator
    for (auto& clueRow : this->horizontalClues) //Ustalanie pozycji podpowiedzi dla wierszy
    {
        for (int i = clueRow.size() - 1; i >= 0; i--)
        {
            clueRow[forwI]->setCluePosition(
                horizontalCluesPosition.y - (oneTileSize.x - boxMargin) * i,
                horizontalCluesPosition.x + (oneTileSize.x +  boxMargin) * rowCounter);
            forwI++;
        }
        rowCounter++;
        forwI = 0;
    }
   
    forwI = 0;
    int colCounter = 0;
    for (auto& clueCol : this->verticalClues) //Ustalanie pozycji podpowiedzi dla kolumn
    {
        for (int i = clueCol.size() - 1; i >= 0; i--)
        {
            clueCol[forwI]->setCluePosition(
                verticalCluesPosition.x + (oneTileSize.x + boxMargin) * colCounter,
                verticalCluesPosition.y - (oneTileSize.y + boxMargin) * i
                );
            forwI++;
        }
        colCounter++;
        forwI = 0;
    }
}


void Board::setUpLevel(std::ifstream& inputLevel)
{
    this->checkDimensions(inputLevel);
    this->createBoard();
    this->setUpTiles(inputLevel);
    this->setUpClues();
    this->setUpPositions();
}



void Board::updateBoard(sf::Vector2f mousePosition)
{
    static bool isMousePressed = false;
    static unsigned short int initialTileStatus = 0;
    
    for (auto& tileRow : this->board)
    {
        for (auto& tile : tileRow)  //Iteracja po całej planszy
        {
            if (tile->getTileGlobalBounds().contains(mousePosition))    //Jeśli najedziemy myszą na kratkę
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))    //1. Obsługa lewego przycisku
                {
                    if (!isMousePressed)
                    {
                        isMousePressed = true;
                        initialTileStatus = tile->getCurrentStatus();
                    }
                    if (initialTileStatus == UNFILLED) {
                        tile->setStatus(FILLED);
                    }
                    else if (initialTileStatus == FILLED) {
                        tile->setStatus(CROSSED);
                    }
                    else
                        tile->setStatus(UNFILLED);
                }

                else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))  //2. Obsługa prawego przycisku
                {
                    if (!isMousePressed)
                    {
                        isMousePressed = true;
                        initialTileStatus = tile->getCurrentStatus();
                    }
                    if (initialTileStatus != CROSSED) {
                        tile->setStatus(CROSSED);
                    }
                    else
                        tile->setStatus(UNFILLED);
                }

                else  //3. Ustawienie flagi wciśnięcia myszy na wyłączoną
                    isMousePressed = false;
                
            }
        }
    }
}


void Board::drawBoard(sf::RenderWindow& target)
{
    for (auto& tileRow : board) //Rysowanie kratek
    {
        for (auto& tile : tileRow)
        {
            tile->draw(target);
        }
    }

   for (auto& clueRow : this->horizontalClues)  //Rysowanie podpowiedzi dla wierszy
   {
        for (auto& clue : clueRow)
        {
            clue->draw(target);
        }
   }

   for (auto& clueCol : this->verticalClues)    //Rysowanie podpowiedzi dla kolumn
   {
       for (auto& clue : clueCol)
       {
           clue->draw(target);
       }
   }
}


const short Board::getRows() const
{
    return this->rows;
}


const short Board::getCols() const
{
    return this->cols;
}


std::vector<std::vector<Tile*>> Board::getBoard() const
{
    return this->board;
}


bool Board::checkIfCompleted()
{
    for (auto& tileRow : this->board)
    {
        for (auto& tile : tileRow)
        {
            if (tile->getBoolCurrentStatus() != tile->getTargetStatus())
            {
               //std::cout << "Board not completed" << std::endl;
                return false;
            }

        }
    }
    std::cout << "Board completed" << std::endl;
    return true;
}
