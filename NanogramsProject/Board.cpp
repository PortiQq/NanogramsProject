#include "Board.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

Board::Board(short rows, short cols) : rows(rows), cols(cols)
{
	//
}

Board::Board() : rows(0), cols(0)
{
	//
}

Board::~Board()
{

}

void Board::checkDimensions(std::ifstream &inputLevel)
{
    //TODO: Check dimensions
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

    // Clear the end-of-file state
    inputLevel.clear();
    // Rewind to the beginning of the file
    inputLevel.seekg(0, std::ios::beg);

    this->rows = xMax + 1;
    this->cols = yMax + 1;
    //return sf::Vector2i(xMax + 1, yMax + 1);
}

void Board::createBoard()
{
    sf::Vector2f position;      //TODO: Stąd zniknie ustalanie pozycji
    std::vector<Tile*> tileRow;
    Tile tile;
    for (int rowCounter = 1; rowCounter <= this->rows; rowCounter++)
    {
        tileRow.clear();
        for (int colCounter = 1; colCounter <= this->cols; colCounter++)
        {
            position = sf::Vector2f
            (colCounter * (tile.getTileSize().y + tile.getTileMargin()),
                rowCounter * (tile.getTileSize().x + tile.getTileMargin())
            );  //Stąd zniknie ustalanie pozycji
            tile.setTilePosition(position); //
            tileRow.push_back(new Tile(position,0,0));
        }
        this->board.push_back(tileRow);
    }
}

void Board::setUpLevel(std::ifstream& inputLevel)
{
    //TODO: Set up level
    std::cout << "Set up level..." << std::endl;
    //TODO: Czytanie pliku i ustalanie targetStatus
    std::string line;
    
    while (std::getline(inputLevel, line)) {
        std::istringstream iss(line);
        int x = 0, y = 0;
        if (iss >> x >> y) {
            std::cout<<"Odczyt w funkcji setUpLevel: " << x << " " << y << std::endl;
            this->board[x][y]->setTargetStatus(FILLED);
        }
        else {
            std::cerr << "Error reading line: " << line << std::endl;
        }
    }
    //TODO: Ustalanie cyferek na podstawie board
}

void Board::setUpPositions()
{
    //TODO: set up positions
    //TODO: Pojawią się pozycje liczb
    //Oraz pozycje kratek
}

void Board::updateBoard(sf::Vector2f mousePosition)
{
    static bool isMousePressed = false;
    static unsigned short int initialTileStatus = 0;
    
    for (auto& tileRow : this->board)
    {
        for (auto& tile : tileRow)
        {
            if (tile->getTileGlobalBounds().contains(mousePosition))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (!isMousePressed)
                    {
                        isMousePressed = true;
                        initialTileStatus = tile->getCurrentStatus();
                    }
                    if (initialTileStatus == UNFILLED) {
                        tile->setStatus(FILLED);
                    }
                    else
                        tile->setStatus(UNFILLED);
                }
                else
                {
                    isMousePressed = false;
                }
            }
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
            if (tile->getTargetStatus() == 1 &&
                (tile->getCurrentStatus() != tile->getTargetStatus()))
            {
                return false;
            }

        }
    }
    return true;
}
