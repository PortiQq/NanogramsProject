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

	std::ofstream outputFile;
	std::ifstream inputFile;

	//Metody inicjalizacji
	void initialiseBackground();
	void initialiseButtons();

	//Metody prywatne

public:
	Editor(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~Editor();

	//Obsługa stanu
	void setUpState();
	void endState();

	//update
	void updateButtons(sf::Event& gameEvent);
	void update(sf::Event& gameEvent);

	//render
	void renderButtons(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target = nullptr);
};

