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
	sf::RenderWindow* window;
	bool quit;
	bool isSetUp;
	void quitState();

public:
	State(sf::RenderWindow* window);
	virtual ~State();

	//gettery
	const bool& getQuit() const;		//Wykorzystywane w klasie Game
	const bool& getIsSetUp() const;		//Chwilowo niewykorzystane, może nie być potrzebne
	virtual const bool checkIfSetUp() const;
	virtual void checkQuit();

	//settery
	virtual void setStateStatus();

	//Metody czysto wirtualne
	virtual void setUpState(std::ifstream &inputFile) = 0;
	virtual void endState() = 0;
	virtual void update(sf::Vector2f mousePosition) = 0;	//Pure virtual. Te metody będą musiały
	virtual void render(sf::RenderTarget* target = nullptr) = 0;	//być zdefiniowane w klasach pochodnych
};

