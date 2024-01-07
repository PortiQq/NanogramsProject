#pragma once
#include "State.h"
class GameState : public State
{
private:
	//Pole planszy dla stanu gry
	Board board;

	//Prywatne metody obsługi planszy gry
	void renderGameBoard(sf::RenderTarget& target);
	void updateBoard();
public:
	//Konstruktor, destruktor
	GameState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~GameState();
	void setUpState(std::ifstream& inputFile);
	void endState();

	//Dostęp do zmiennych
	const bool checkIfSetUp() const;	

	//Inne metody publiczne
	void setUpGameBoard(std::ifstream& inputLevel);
	
	//Update
	void updateKeybinds();
	void update();

	//Render
	void render(sf::RenderTarget* target = nullptr);

};

