#include "State.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states)
{
	this->window = window;
	this->states = states;
	this->quit = false;
	this->isSetUp = false;
	loadFonts();
}

State::~State()
{

}

const bool& State::getQuit() const
{
	return this->quit;
}

const bool& State::getIsSetUp() const
{
	return this->isSetUp;
}

void State::loadFonts()
{
	if (!font.loadFromFile("Fonts/arial.ttf")) {
		std::cerr << "STATE: Error loading font\n";
		exit(1);
	}
}

void State::quitState()
{
	this->quit = true;
}

void State::setStateStatus()
{
	this->isSetUp = true;
}

void State::updateMousePosition()
{
	this->windowMousePosition = sf::Mouse::getPosition(*this->window);
	this->viewMousePosition = this->window->mapPixelToCoords(this->windowMousePosition);
}


void State::checkQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->quit = true;
	}
}

const bool State::checkIfSetUp() const
{
	if (this->isSetUp == true)
		return true;
	else
		return false;
}
