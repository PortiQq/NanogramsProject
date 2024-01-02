#pragma once
#include "Tile.h"
#include "Number.h"
#include<fstream>


class Board
{
private:
	std::vector<std::vector<Tile*>> board;
	short rows;
	short cols;

public:
	//Konstruktory, destruktor
	Board(short rows, short cols);
	Board();
	~Board();

	//gettery
	const short getRows() const;
	const short getCols() const;
	std::vector<std::vector<Tile*>> getBoard() const;

	//metody publiczne
	void checkDimensions(std::ifstream &inputLevel);
	void createBoard();
	void setUpLevel(std::ifstream& inputLevel);
	void setUpPositions();

	void updateBoard(sf::Vector2f mousePosition);


	bool checkIfCompleted();	//TODO: check if board completed
};

