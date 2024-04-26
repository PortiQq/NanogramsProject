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

	//Metody prywatne update i render
	void updateTexts();
	void updateButtons(sf::Event& gameEvent);
	void renderButtons(sf::RenderTarget* target = nullptr);
	void renderTexts(sf::RenderTarget* target = nullptr);

	void saveBoard();	//Zapisanie pliku i wyjście z edytora

public:
	Editor(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~Editor();

	//Obsługa stanu
	void setUpState();
	void endState();

	void update(sf::Event& gameEvent);
	
	void render(sf::RenderTarget* target = nullptr);
	
};

