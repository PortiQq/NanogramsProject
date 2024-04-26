#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>  
#include <SFML/System.hpp>

#include "State.h"
#include "Button.h"
#include "LevelSelect.h"
#include "Editor.h"


class MainMenu : public State
{
private:
	//Pola stylu menu
	sf::Texture backgroundTexture;
	sf::RectangleShape menuBackground;
	
	//Mapa przycisków
	std::map<std::string, Button*> buttons;

	std::string pathFolder;		//Powinien być formatu "folder/"
	

	//Inicjalizacja pól prywatnych
	void initialiseBackground();
	void initialiseButtons();

public:
	//Konstruktor, destruktor
	MainMenu(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~MainMenu();

	//Obsługa stanu
	void setUpState();
	void endState();

	//Update
	void updateButtons(sf::Event& gameEvent);
	void update(sf::Event& gameEvent);

	//Render
	void renderButtons(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target = nullptr);

};

