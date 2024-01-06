#include "GameState.h"


GameState::GameState(sf::RenderWindow* window) : State(window)
{

}


GameState::~GameState()
{

}


void GameState::setUpState(std::ifstream& inputFile)
{
	this->setUpGameBoard(inputFile);
	//this->setStateStatus();
	this->isSetUp = true;
}


void GameState::endState()
{
	std::cout << "Ending game state"<<std::endl;
	std::cout << "..." << std::endl;
	std::cout<<"Game state ended\n";
}


void GameState::renderGameBoard(sf::RenderTarget& target)
{
	board.drawBoard(target);
}


void GameState::updateBoard(sf::Vector2f mousePosition)
{
	board.updateBoard(mousePosition);
	board.updateClues();
}


const bool GameState::checkIfSetUp() const
{
	return (this->isSetUp) ? true : false;
}


void GameState::setUpGameBoard(std::ifstream& inputLevel)
{
	board.setUpLevel(inputLevel);
}


void GameState::updateKeybinds()
{
	this->checkQuit();	//Ustawianie wyjścia ze stanu na klawisz esc
}


void GameState::update(sf::Vector2f mousePosition)
{
	this->updateKeybinds();
	this->updateBoard(mousePosition);

	if (this->board.checkIfCompleted())	//TODO: tu można dodać zdarzenie po ukończeniu poziomu
	{
		this->quitState();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	this->renderGameBoard(*target);
}
