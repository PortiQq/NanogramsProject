#include "State.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states)
{
	this->window = window;
	this->states = states;
	this->quit = false;
	this->isSetUp = false;
	loadFonts();
	loadTextures();
}

State::~State()
{

}

const bool& State::getQuit() const
{
	return this->quit;
}


void State::loadFonts()
{
	if (!font.loadFromFile("Fonts/arial.ttf")) {
		std::cerr << "STATE: Error loading font\n";
		exit(1);
	}
}


void State::loadTextures()
{
	if (!this->crossTexture.loadFromFile("Images/cross.png"))
	{
		"ERROR: Tekstura cross niewczytana w State";
	}
}


void State::quitState()
{
	this->quit = true;
}


void State::updateMousePosition()
{
	this->windowMousePosition = sf::Mouse::getPosition(*this->window);
	this->viewMousePosition = this->window->mapPixelToCoords(this->windowMousePosition);
}


const bool State::checkIfSetUp() const
{
	return (this->isSetUp) ? true : false;
}
