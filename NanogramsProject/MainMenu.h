#pragma once
#include "State.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>  
#include <SFML/System.hpp>

class MainMenu : public State
{
private:
	sf::RectangleShape menuBackground;
public:
	//Konstruktor, destruktor
	MainMenu(sf::RenderWindow* window);
	virtual ~MainMenu();
	
	void setUpState(std::ifstream& inputFile);
	void endState();

	//Dostęp do zmiennych
	const bool checkIfSetUp() const;

	//Inne metody publiczne

	//Update
	void updateKeybinds();
	void update(sf::Vector2f mousePosition);


	//Render
	void render(sf::RenderTarget* target = nullptr);
};

