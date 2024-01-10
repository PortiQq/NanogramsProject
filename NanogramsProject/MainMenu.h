#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>  
#include <SFML/System.hpp>

#include "State.h"
#include "Button.h"
#include "LevelSelect.h"


class MainMenu : public State
{
private:
	//Pola stylu menu
	sf::Texture backgroundTexture;
	sf::RectangleShape menuBackground;
	
	//Mapa przycisków
	std::map<std::string, Button*> buttons;
	

	//Inicjalizacja pól prywatnych
	void initialiseBackground();
	void initialiseButtons();

public:
	//Konstruktor, destruktor
	MainMenu(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~MainMenu();

	void setUpState(std::ifstream& inputFile);

	void endState();	//Obsługa wychodzenia ze stanu

	//Update
	void updateButtons(sf::Event& gameEvent);
	void update(sf::Event& gameEvent);

	//Render
	void renderButtons(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target = nullptr);

};

