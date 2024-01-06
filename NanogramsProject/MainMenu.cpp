#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow* window) : State(window)
{
	this->menuBackground.setSize(sf::Vector2f((float)this->window->getSize().x, (float)this->window->getSize().y));
	this->menuBackground.setFillColor(sf::Color::Black);
}


MainMenu::~MainMenu()
{

}


void MainMenu::setUpState(std::ifstream& inputFile)
{
	this->isSetUp = true;
}


void MainMenu::endState()
{
	std::cout << "Ending main menu state" << std::endl;
	std::cout << "..." << std::endl;
	std::cout << "Main menu state ended\n";
}


const bool MainMenu::checkIfSetUp() const
{
	return (this->isSetUp) ? true : false;
}


void MainMenu::updateKeybinds()
{
	this->checkQuit();	//Ustawianie wyjścia ze stanu na klawisz esc
}


void MainMenu::update(sf::Vector2f mousePosition)
{
	this->updateKeybinds();
}


void MainMenu::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->menuBackground);
}
