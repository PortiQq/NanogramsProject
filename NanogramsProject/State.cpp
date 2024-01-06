#include "State.h"

State::State(sf::RenderWindow* window)
{
	this->window = window;
	this->quit = false;
	this->isSetUp = false;
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

void State::quitState()
{
	this->quit = true;
}

void State::setStateStatus()
{
	this->isSetUp = true;
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
