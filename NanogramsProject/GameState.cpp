#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states, std::string inputFileName) :
	State(window, states), inputFileName(inputFileName), board(crossTexture)
{
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
	//delete this->nextLevelButton;
}


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
	congratsRect.setFillColor(sf::Color(200, 200, 200, 230));
	congratsRect.setPosition
	(
		0.f,
		window->getSize().y / 2.f - (congratsRect.getGlobalBounds().height / 2.f)
	);
	sf::Vector2f rectSize = sf::Vector2f(window->getSize().x, window->getSize().y / 8.f);
	int textSize = window->getSize().x / 15;
	congratsRect.setSize(rectSize);
	(textSize > 16) ? congrats.setCharacterSize(textSize) : congrats.setCharacterSize(16);
	congrats.setFillColor(sf::Color::Black);
	congrats.setFont(this->font);
}


void GameState::initialiseButtons()
{
	sf::Color idleButtonColor = sf::Color(130, 120, 129, 200);
	sf::Color hoveredButtonColor = sf::Color(130, 120, 129, 255);
	sf::Color clickedButtonColor = sf::Color(100, 90, 90, 255);

	backButton = new Button(10.f, 5.f, 100.f, 50.f,
		font, "      Back to\nLevel selection", 14,
		idleButtonColor, hoveredButtonColor, clickedButtonColor);

	/*nextLevelButton = new Button(window->getSize().x - 85.f, 5.f, 80.f, 50.f,
		font, "Next level", 14,
		idleButtonColor, hoveredButtonColor, clickedButtonColor);*/
}


void GameState::renderButtons(sf::RenderTarget* target)
{
	//this->nextLevelButton->render(*target);
}


void GameState::updateButtons(sf::Event& gameEvent)
{
	backButton->update(viewMousePosition, gameEvent);
	if (this->backButton->isPressed())
		quitState();
	//nextLevelButton->update(viewMousePosition, gameEvent);
	//if (this->nextLevelButton->isPressed())
	//{
	//	//this->states->push(new GameState(this->window, this->states, filename));
	//	quitState();
	//}
		
	
}


void GameState::setUpState()
{
	this->board.resize(sf::Vector2f(25.f, 25.f), 5.f, 12);
	board.setUpLevel(this->levelFile, this->font);

	float oneTileSize = Tile::getTileSize().x, tileMargin = Tile::getTileMargin();
		sf::Vector2u newWindowSize
		(
			(oneTileSize + tileMargin) * (this->board.getGridWidth() + 1) + tileMargin,
			(oneTileSize + tileMargin) * (this->board.getGridHeight() + 1) + tileMargin * 6
		);
	this->window->setSize(newWindowSize);
	this->gameStateBackground.setSize(sf::Vector2f(newWindowSize.x, newWindowSize.y));

	this->initialiseTexts();
	this->initialiseButtons();
	backButton->centralisePosition(newWindowSize, 5.f);
	
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
	congrats.setPosition
	(
		this->congratsRect.getPosition().x + (this->congratsRect.getGlobalBounds().width / 2.f) - this->congrats.getGlobalBounds().width / 2.f,
		this->congratsRect.getPosition().y + (this->congratsRect.getGlobalBounds().height / 2.f) - this->congrats.getGlobalBounds().height / 2.f - 2.f
	);
	congrats.setString(temp);
}


void GameState::renderGameBoard(sf::RenderTarget& target)
{
	this->board.drawBoard(target);
}


void GameState::updateBoard()
{
	this->board.updateBoard(this->viewMousePosition);
	//this->board.updateClues();
}


void GameState::update(sf::Event& gameEvent)
{
	this->updateMousePosition();
	this->updateBoard();
	this->updateButtons(gameEvent);
	this->updateText();
	

	if (this->board.checkIfCompleted())
	{
		visible = true;	//Tekst gratulacyjny pojawia się na ekranie
	}
	else
		visible = false;
}


void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->gameStateBackground);
	
	this->backButton->render(*target);
	this->renderGameBoard(*target);

	if (visible)
	{
		this->renderCongrats(target);
		renderButtons(target);
	}
		
}

void GameState::renderCongrats(sf::RenderTarget* target)
{
	target->draw(congratsRect);
	target->draw(congrats);
}
