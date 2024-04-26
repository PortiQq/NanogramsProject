#pragma once
#include "Tile.h"
#include "Clue.h"
#include<fstream>


class Board
{
private:
	//Pola prywatne
	std::vector<std::vector<Tile*>> board;
	std::vector<std::vector<Clue*>> horizontalClues;	//Podpowiedzi dla wierszy
	std::vector<std::vector<Clue*>> verticalClues;		//Podpowiedzi dla kolumn
	short rows;
	short cols;
	short gridWidth;	//Ilość obiektów do wyrenderowania na osi poziomej
	short gridHeight;	//Ilość obiektów do wyrenderowania na osi pionowej

	sf::Texture& crossTexture;

	//Metody dla tworzenia planszy
	void checkDimensions(std::ifstream& inputLevel);	//Sprawdza plik i ustala rows i cols
	void createBoard();									//Wypełnia board kratkami
	void setUpTiles(std::ifstream& inputLevel);			//Ustala docelowe statusy
	void setUpClues(sf::Font& font);					//Tworzy tablice podpowiedzi
	void setUpPositions();								//Ustala pozycje kratek i podpowiedzi

	//Specyficzne dla edytora
	void setUpPositionsEditor();
	void setDimensions(unsigned short rows, unsigned short cols);
	void clearBoard();
	

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
	void setUpLevel(std::ifstream& inputLevel, sf::Font& font);
	void updateBoard(sf::Vector2f mousePosition);
	void updateClues();
	void drawBoard(sf::RenderTarget& target);

	bool checkIfCompleted();

	//Do zmiany rozmiaru zbyt dużych plansz
	void resize(sf::Vector2f newTileSize, float newMargin, int newCharacterSize);

	//Specyficzne dla edytora
	void setUpEdited(unsigned short rows, unsigned short cols);
	void updateEdited(sf::Vector2f mousePosition);
	void renderEdited(sf::RenderTarget& target);
	void saveEdited();

	//Manipulacja wielkością planszy
	void addRow();
	void addColumn();
	void subtractRow();
	void subtractColumn();

};

