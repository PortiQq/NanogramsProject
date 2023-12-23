#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>  
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <vector>

class Game
{
private:

	//Zmienne prywatne 
	sf::RenderWindow* gameWindow;
	sf::Event event;

	//Szczegóły okna gry
	sf::VideoMode videoMode;
	sf::Uint32 style;
	std::string title;
	sf::Image icon;
	sf::Color backgroundColor;

	sf::Vector2f tileSize;	//Ustalony rozmiar jednej kratki
	float tileMargin;		//margines między kratkami

	//pozycja myszy
	sf::Vector2i windowMousePosition;	//int - piksele
	sf::Vector2f viewMousePosition;		//float

	//Logika gry
	//Kolory kratek w czasie gry
	sf::Color filled;		//Wypełnione
	sf::Color unfilled;		//Niewypełnione
	bool mouseHold;


	int rows, cols;	//Tymczasowo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	//metody prywatne okna
	void initialiseVariables();
	void createWindow();
	void initialiseTiles();		//Ustalenie szczegółów pojedynczej kratki

	/////////////
	//obiekty gry

	std::vector<sf::RectangleShape> tiles;
	sf::RectangleShape tile;

	/////////////


public:
	//konstruktory destruktory
	Game();
	~Game();

	//Dostęp do zmiennych
	const bool gameRunning() const;
	const bool gameBoardRendered() const;

	//metody publiczne
	void render();
	void renderTiles();

	void update();
	void updateTiles();

	void pollEvents();
	void updateMousePosition();

	void setUpBoard();


};

