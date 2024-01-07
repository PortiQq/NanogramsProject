#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>  
#include <SFML/System.hpp>

#include "State.h"
#include "Button.h"
#include "GameState.h"


class MainMenu : public State
{
private:
	//Pola stylu menu
	sf::Texture backgroundTexture;
	sf::RectangleShape menuBackground;
	
	//Mapa przycisków
	std::map<std::string, Button*> buttons;

	void initialiseBackground();
	void initialiseButtons();

public:
	//Konstruktor, destruktor
	MainMenu(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~MainMenu();
	
	void setUpState(std::ifstream& inputFile);
	void endState();

	//Dostęp do zmiennych
	const bool checkIfSetUp() const;

	//Inne metody publiczne

	//Update
	void updateKeybinds();
	void updateButtons();
	void update();

	//Render
	void renderButtons(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target = nullptr);
};

