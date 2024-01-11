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

void GameState::initialiseTexts()
{
	congrats.setCharacterSize(20);
	congrats.setFillColor(sf::Color::Black);
	congrats.setFont(font);
}


void GameState::initialiseButtons()
{
	sf::Color idleButtonColor = sf::Color(130, 120, 129, 200);
	sf::Color hoveredButtonColor = sf::Color(130, 120, 129, 255);
	sf::Color clickedButtonColor = sf::Color(100, 90, 90, 255);

	backButton = new Button(10.f, 5.f, 100.f, 50.f,
		font, "      Back to\nLevel selection", 14,
		idleButtonColor, hoveredButtonColor, clickedButtonColor);
}

void GameState::renderButtons(sf::RenderTarget* target)
{
	backButton->render(*target);
}

void GameState::updateButtons(sf::Event& gameEvent)
{
	backButton->update(viewMousePosition, gameEvent);
	if (this->backButton->isPressed())
		quitState();
}


GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states) : 
	State(window, states), board(crossTexture)
{
	this->initialiseBackground();
	this->initialiseButtons();
	this->initialiseTexts();
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
			(oneTileSize + tileMargin) * (this->board.getGridWidth() + 1) + tileMargin,
			(oneTileSize + tileMargin) * (this->board.getGridHeight() + 1) + tileMargin * 4
		);
		this->window->setSize(newWindowSize);
		this->gameStateBackground.setSize(sf::Vector2f(newWindowSize.x, newWindowSize.y));

	this->isSetUp = true;
}


void GameState::endState()
{
	std::cout << "Wychodzenie ze stanu gry\n";
	std::cout << "...\n";
	this->window->setSize(sf::Vector2u(800, 600));
	this->board.resize(sf::Vector2f(25.f, 25.f), 5.f, 12);
	this->levelFile.close();
	std::cout<<"Stan gry zakonczony"<<std::endl;
}


void GameState::renderText(sf::RenderTarget* target)
{
	target->draw(congrats);
}

void GameState::updateText()
{
	std::string temp = "Level completed!";
	congrats.setPosition(window->getSize().x / 2.0f, 10.f);
	congrats.setString(temp);
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
	this->updateButtons(gameEvent);
	this->updateText();
	

	if (this->board.checkIfCompleted())	//TODO: tu można dodać zdarzenie po ukończeniu poziomu
	{
		visible = true;	//Tekst gratulacyjny pojawia się na ekranie
		this->quitState();
	}
}


void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->gameStateBackground);
	renderButtons(target);
	
	this->renderGameBoard(*target);

	
	//if (visible == true)
	this->renderText(target);
}
