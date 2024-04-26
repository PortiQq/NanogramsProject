#pragma once

#include "MainMenu.h"
#include "GameState.h"
#include "LevelSelect.h"



class Game
{
private:
	sf::RenderWindow* gameWindow;	//Wskaźnik na okno główne gry
	sf::Event event;				//Kontrola zdarzeń

	//Szczegóły okna gry
	sf::VideoMode videoMode;
	sf::Uint32 style;
	std::string title;
	sf::Image icon;
	sf::Color backgroundColor;

	//Stos stanów gry
	std::stack<State*> states;

	//pozycja myszy
	sf::Vector2i windowMousePosition;	//int - piksele
	sf::Vector2f viewMousePosition;		//float - dokładniejsza pozycja

	//Szczegóły dla kratek
	sf::Vector2f tileSize;				//Ustalony rozmiar jednej kratki
	sf::Color outlineColorForTiles;
	float outlineThicknessForTiles;
	float tileMargin;					//odstęp między kratkami

	//Szczegóły dla text boxów
	sf::Color textColorForClues;
	float outlineThicknessForClues;
	unsigned short characterSizeForClues;

	//metody prywatne okna
	void initialiseVariables();
	void createWindow();
	void initialiseStates();
	const bool gameRunning() const;

	void render();
	void update();
	void pollEvents();

public:

	//konstruktor, destruktor
	Game();
	~Game();

	//metody publiczne
	void runGame();
	void endApplication();

};

