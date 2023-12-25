#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>  
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <vector>
#include "Tile.h"


class Game
{
private:

	//pola prywatne 
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


	//Logika gry
	sf::Color filled;		//Kolory wypełnionych kratek w czasie gry
	sf::Color unfilled;		//Kolory niewypełnionych kratek w czasie gry 
	bool mouseHold;			//Flaga sprawdzająca czy mysz jest trzymana


	int rows, cols;	//Tymczasowo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	//metody prywatne okna
	void initialiseVariables();
	void createWindow();

	


public:

	/////////////
	//obiekty gry
	sf::Vector2f tileSize;	//Ustalony rozmiar jednej kratki
	sf::Color outlineColorForTiles;
	float outlineThicknessForTiles;
	float tileMargin;		//margines między kratkami

	std::vector<sf::RectangleShape> tiles;		//stary kod bez użycia
	sf::RectangleShape tile;					//klasy Tile

	

	//Tile tile2;									//Nowy kod po
	std::vector<Tile>tiles2;					//użyciu klasy Tile

	//konstruktory destruktory
	Game();
	~Game();


	/////////////

	//Dostęp do zmiennych
	const bool gameRunning() const;
	const bool gameBoardRendered() const;

	//metody publiczne
	void render();
	void renderTiles();

	void update();
	void updateBoard();

	void pollEvents();
	void updateMousePosition();

	void setUpBoard();


};

