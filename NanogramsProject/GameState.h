#pragma once
#include "State.h"
class GameState : public State
{
private:
	//Pole planszy dla stanu gry
	Board board;

	//Prywatne metody obsługi planszy gry
	void renderGameBoard(sf::RenderTarget& target);
	void updateBoard(sf::Vector2f mousePosition);
public:
	//Konstruktor, destruktor
	GameState(sf::RenderWindow* window);
	virtual ~GameState();
	void setUpState(std::ifstream& inputFile);
	void endState();

	//Dostęp do zmiennych
	const bool checkIfSetUp() const;	

	//Inne metody publiczne
	void setUpGameBoard(std::ifstream& inputLevel);
	
	//Update
	void updateKeybinds();
	void update(sf::Vector2f mousePosition);

	//Render
	void render(sf::RenderTarget* target = nullptr);

};

