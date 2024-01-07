#pragma once


#include <fstream>
#include <vector>
#include <stack>

#include "Tile.h"
#include "Clue.h"
#include "Board.h"


class State
{
private:
	
protected:
	std::stack<State*>* states;

	sf::RenderWindow* window;
	bool quit;
	bool isSetUp;

	//Pozycja myszy
	sf::Vector2i windowMousePosition;
	sf::Vector2f viewMousePosition;

	//Czcionka
	sf::Font font;
	void loadFonts();

	//Metody chronione
	void quitState();

public:
	State(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~State();

	//gettery
	const bool& getQuit() const;		//Wykorzystywane w klasie Game
	const bool& getIsSetUp() const;		//Chwilowo niewykorzystane, może nie być potrzebne
	virtual const bool checkIfSetUp() const;
	virtual void checkQuit();			//Ustawia quit jeśli: warunek esc

	//settery
	virtual void setStateStatus();

	//Pozycja myszy
	virtual void updateMousePosition();

	//Metody czysto wirtualne
	virtual void setUpState(std::ifstream &inputFile) = 0;
	virtual void endState() = 0;
	virtual void update() = 0;	//Pure virtual. Te metody będą musiały
	virtual void render(sf::RenderTarget* target = nullptr) = 0;	//być zdefiniowane w klasach pochodnych
};

