#include "Board.h"

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
	//
}

void Board::setUpBoard(short rows, short cols)
{
    sf::Vector2f position;

    Tile tile(sf::Vector2f(0.f, 0.f), 0, 1);       //TODO: Tworzenie obiektu tile z rozróżnieniem czy ma być pokryty czy nie
    for (float rowCounter = 1.f; rowCounter <= rows; rowCounter += 1.f)
        for (float colCounter = 1.f; colCounter <= cols; colCounter += 1.f)
        {
            position = sf::Vector2f(colCounter * (tile.getTileSize().y + tile.getTileMargin()), rowCounter * (tile.getTileSize().x + tile.getTileMargin()));
            tile.setTilePosition(position);
            this->tiles.push_back(tile);
        }
}

void Board::updateBoard(sf::Vector2f mousePosition)
{
    static bool isMousePressed = false;
    static unsigned short int initialTileStatus = 0;
    

    for (auto &t : this->tiles)
    {
        if (t.getTileGlobalBounds().contains(mousePosition))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (!isMousePressed)
                {
                    isMousePressed = true;
                    initialTileStatus = t.getCurrentStatus();
                }
                if (initialTileStatus == UNFILLED) {
                t.setStatus(FILLED);
            }
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

const short Board::getRows() const
{
    return this->rows;
}

const short Board::getCols() const
{
    return this->cols;
}

std::vector<Tile> Board::getTiles() const
{
    return this->tiles;
}