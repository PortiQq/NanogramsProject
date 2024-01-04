#pragma once
#include "Tile.h"
#include "Clue.h"
#include<fstream>


class Board
{
private:
	//Pola prywatne
	std::vector<std::vector<Tile*>> board;
	std::vector<std::vector<Clue*>> horizontalClues;
	std::vector<std::vector<Clue*>> verticalClues;
	short rows;
	short cols;
	short gridWidth;	//Ilość obiektów do wyrenderowania na osi poziomej
	short gridHeight;	//Ilość obiektów do wyrenderowania na osi pionowej
	//sf::Vector2f startingPosition;
	//Metody prywatne
	void setStartingPosition();		//TODO: Ustalenie pozycji startowej dla generowania planszy

	//Metody dla tworzenia planszy
	void checkDimensions(std::ifstream& inputLevel);
	void createBoard();
	void setUpTiles(std::ifstream& inputLevel);
	void setUpClues();
	void setUpPositions();

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
	void setUpLevel(std::ifstream& inputLevel);
	void updateBoard(sf::Vector2f mousePosition);
	void drawBoard(sf::RenderWindow& target);

	bool checkIfCompleted();
};

