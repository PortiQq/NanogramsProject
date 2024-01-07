#include "GameState.h"
#include "MainMenu.h"


GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{

}


GameState::~GameState()
{

}


void GameState::setUpState(std::ifstream& inputFile)
{
	this->setUpGameBoard(inputFile);
	this->isSetUp = true;
}


void GameState::endState()
{
	std::cout << "Ending game state"<<std::endl;
	this->board.~Board();
	std::cout << "..." << std::endl;
	std::cout<<"Game state ended\n";
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


void GameState::update()
{
	this->updateMousePosition();
	this->updateKeybinds();
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
	this->renderGameBoard(*target);
}
