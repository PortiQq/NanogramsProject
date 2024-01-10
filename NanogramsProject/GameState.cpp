﻿#include "GameState.h"

void GameState::initialiseBackground()
{
	this->gameStateBackground.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);
	this->gameStateBackground.setFillColor(sf::Color(180, 170, 169, 255));
}


void GameState::initialiseButtons()
{
	sf::Color idleButtonColor = sf::Color(0, 230, 230, 200);
	sf::Color hoveredButtonColor = sf::Color(0, 230, 230, 255);
	sf::Color clickedButtonColor = sf::Color(0, 162, 162, 255);

	backButton = new Button(10.f, 10.f, 150.f, 50.f,
		font, "Back to main menu", 14,
		idleButtonColor, hoveredButtonColor, clickedButtonColor);
}


GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states) : 
	State(window, states), board(crossTexture)
{
	this->initialiseBackground();
	this->initialiseButtons();
	this->loadTextures();
}


GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states, std::string inputFileName) :
	State(window, states), inputFileName(inputFileName), board(crossTexture)
{
	this->initialiseButtons();
	this->initialiseBackground();
	this->levelFile = std::ifstream(inputFileName);
		if (!levelFile.is_open())
		{
			std::cerr << "Failed to open file: " << inputFileName << std::endl;
		}
}


GameState::~GameState()
{
	delete this->backButton;
}


void GameState::setUpState()
{
	this->board.resize(sf::Vector2f(25.f, 25.f), 5.f, 12);
	board.setUpLevel(this->levelFile);

	float oneTileSize = Tile::getTileSize().x, tileMargin = Tile::getTileMargin();
		sf::Vector2u newWindowSize
		(
			(oneTileSize + tileMargin) * this->board.getGridWidth() + tileMargin,
			(oneTileSize + tileMargin) * this->board.getGridHeight() + tileMargin
		);
		this->window->setSize(newWindowSize);
		this->gameStateBackground.setSize(sf::Vector2f(newWindowSize.x, newWindowSize.y));
		
	if 
		(
			Tile::getTileSize().x * this->board.getGridHeight() > this->window->getSize().x ||
			Tile::getTileSize().y * this->board.getGridWidth() > this->window->getSize().y
		)
	{
		this->board.resize(sf::Vector2f(20.f, 20.f), 4.f, 12);	//TODO: Więcej dynamicznej zmiany rozmiaru
	}

	this->isSetUp = true;
}


void GameState::endState()
{
	std::cout << "Wychodzenie ze stanu gry\n";
	std::cout << "...\n";
	this->window->setSize(sf::Vector2u(800, 600));
	this->levelFile.close();
	std::cout<<"Stan gry zakonczony"<<std::endl;
}


void GameState::renderGameBoard(sf::RenderTarget& target)
{
	this->board.drawBoard(target);
}


void GameState::updateBoard()
{
	this->board.updateBoard(this->viewMousePosition);
	this->board.updateClues();
}


void GameState::update(sf::Event& gameEvent)
{
	this->updateMousePosition();
	this->updateBoard();

	if (this->board.checkIfCompleted())	//TODO: tu można dodać zdarzenie po ukończeniu poziomu
	{
		this->quitState();
	}
}


void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->gameStateBackground);
	this->renderGameBoard(*target);
}
