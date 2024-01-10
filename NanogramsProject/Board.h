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

	sf::Texture& crossTexture;

	//Metody dla tworzenia planszy
	void checkDimensions(std::ifstream& inputLevel);	//Sprawdza plik i ustala rows i cols
	void createBoard();									//Wypełnia board kratkami
	void setUpTiles(std::ifstream& inputLevel);			//Ustala docelowe statusy
	void setUpClues();									//Tworzy tablice podpowiedzi
	void setUpPositions();								//Ustala pozycje kratek i podpowiedzi

public:
	//Konstruktory, destruktor
	Board(short rows, short cols, sf::Texture& texture);
	Board(sf::Texture& texture);
	~Board();

	//gettery
	const short getRows() const;
	const short getCols() const;
	const short getGridWidth() const;
	const short getGridHeight() const;
	std::vector<std::vector<Tile*>> getBoard() const;

	//metody publiczne
	void setUpLevel(std::ifstream& inputLevel);
	void updateBoard(sf::Vector2f mousePosition);
	void updateClues();
	void drawBoard(sf::RenderTarget& target);

	bool checkIfCompleted();

	void resize(sf::Vector2f newTileSize, float newMargin, int newCharacterSize);

};

