#pragma once
#include "State.h"
#include "MainMenu.h"

class Editor :	public State
{
private:
	sf::RectangleShape editorBackground;

	std::map<std::string, Button*> buttons;

	unsigned short rows;
	unsigned short cols;
	Board board;

	sf::Text rowsText, colsText;

	std::ofstream outputFile;
	std::ifstream inputFile;

	//Metody inicjalizacji
	void initialiseBackground();
	void initialiseButtons();
	void initialiseTexts();

	//Metody prywatne
	void saveBoard();

public:
	Editor(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~Editor();

	//Obsługa stanu
	void setUpState();
	void endState();

	//update
	void updateButtons(sf::Event& gameEvent);
	void updateTexts();
	void update(sf::Event& gameEvent);

	//render
	void renderButtons(sf::RenderTarget* target = nullptr);
	void renderTexts(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target = nullptr);

	//Inne metody
	
};

