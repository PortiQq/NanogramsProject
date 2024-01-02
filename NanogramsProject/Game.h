#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>  
#include <SFML/System.hpp>

#include <iostream>
#include <vector>
#include <fstream>
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

	//Pliki poziomów;
	std::ifstream inputFile;
	sf::Font font;

	//pozycja myszy
	sf::Vector2i windowMousePosition;	//int - piksele
	sf::Vector2f viewMousePosition;		//float - dokładniejsza pozycja

	//Szczegóły dla kratek
	sf::Vector2f tileSize;				//Ustalony rozmiar jednej kratki
	sf::Color outlineColorForTiles;
	float outlineThicknessForTiles;
	float tileMargin;					//odstęp między kratkami

	//Szczegóły dla text boxów
	sf::Color textColorForTextBox;
	float outlineThicknessForTextBox;
	unsigned short characterSizeForTextBox;

	//Pola planszy
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
	const bool gameBoardCreated() const;

	//metody publiczne
	void render();		
	void renderGameBoard();
	void update();
	void updateBoard();
	void pollEvents();
	void updateMousePosition();

	void setUpGameBoard();



};

