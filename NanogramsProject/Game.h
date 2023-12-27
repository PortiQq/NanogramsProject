#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>  
#include <SFML/System.hpp>

#include <iostream>
#include <vector>
#include "Tile.h"
#include "Board.h"


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

	//pozycja myszy
	sf::Vector2i windowMousePosition;	//int - piksele
	sf::Vector2f viewMousePosition;		//float

	//Szczegóły dla kratek
	sf::Vector2f tileSize;				//Ustalony rozmiar jednej kratki
	sf::Color outlineColorForTiles;
	float outlineThicknessForTiles;
	float tileMargin;					//margines między kratkami

	//Logika gry
	sf::Color filled;		//Kolory wypełnionych kratek w czasie gry
	sf::Color unfilled;		//Kolory niewypełnionych kratek w czasie gry 

	int rows, cols;	//Tymczasowo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	Board board;

	//metody prywatne okna
	void initialiseVariables();
	void createWindow();


public:
	

	//konstruktory destruktory
	Game();
	~Game();

	//Dostęp do zmiennych
	const bool gameRunning() const;
	const bool gameBoardRendered() const;

	//metody publiczne
	void render();
	void renderGameBoard();
	void update();
	void updateBoard();
	void pollEvents();
	void updateMousePosition();

	void setUpBoard();


};

