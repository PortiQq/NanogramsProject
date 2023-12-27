#pragma once
#include "Tile.h"


class Board
{
private:
	std::vector<Tile>tiles;
	std::vector<std::vector<Tile>> board;	//TODO: macierz kratek
	short rows;
	short cols;

public:
	Board(short rows, short cols);
	Board();
	~Board();
	void setUpBoard(short rows, short cols);
	void updateBoard(sf::Vector2f mousePosition);

	const short getRows() const;
	const short getCols() const;
	std::vector<Tile> getTiles() const;



	bool checkIfCompleted();	//TODO: check if board completed
};

