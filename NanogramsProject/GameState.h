#pragma once
#include "State.h"
#include "MainMenu.h"
#include "LevelSelect.h"

class GameState : public State
{
private:
	//metody inicjalizacji
	sf::RectangleShape gameStateBackground;
	void initialiseBackground();
	void initialiseTexts();

	//Obsługa przycisków
	Button* backButton; // *nextLevelButton;
	void initialiseButtons();
	void renderButtons(sf::RenderTarget* target = nullptr);
	void updateButtons(sf::Event& gameEvent);
	
	Board board;	//Pole planszy dla gameState

	//Pola plikowe
	std::ifstream levelFile;
	std::string inputFileName;

	//Obsługa wyświetlania informacji o zakończonym poziomie
	bool visible;
	sf::Text congrats;
	sf::RectangleShape congratsRect;
	void renderText(sf::RenderTarget* target = nullptr);
	void updateText();

	//Prywatne metody obsługi planszy gry
	void renderGameBoard(sf::RenderTarget& target);
	void updateBoard();
public:
	//Konstruktory, destruktor
	GameState(sf::RenderWindow* window, std::stack<State*>* states, std::string inputFileName);
	virtual ~GameState();

	void setUpState();
	void endState();
	
	//Update
	void update(sf::Event& gameEvent);

	//Render
	void render(sf::RenderTarget* target = nullptr);
	void renderCongrats(sf::RenderTarget* target = nullptr);

};

