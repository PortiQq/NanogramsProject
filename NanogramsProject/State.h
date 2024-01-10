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
	sf::Texture crossTexture;
	void loadFonts();
	void loadTextures();

public:
	void quitState();	//Wyjście ze stanu - quit = true

	State(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~State();

	//gettery
	const bool& getQuit() const;		//Wykorzystywane w klasie Game
	
	//Pozycja myszy
	void updateMousePosition();	//TODO: usunąłem virtual - ogarnąć czy OK

	virtual const bool checkIfSetUp() const;
	virtual void quitKeybind();			//Ustawia quit jeśli: warunek esc

	//Metody czysto wirtualne
	virtual void setUpState(std::ifstream &inputFile) = 0;
	virtual void endState() = 0;
	virtual void update(sf::Event& gameEvent) = 0;	
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

