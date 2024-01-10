#include "MainMenu.h"

void MainMenu::initialiseBackground()
{
	this->menuBackground.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);
	if (!this->backgroundTexture.loadFromFile("Images/background.png"))
	{
		std::cout << "ERROR: blad odczytu pliku background.png";
	}
	this->menuBackground.setTexture(&this->backgroundTexture);
}


void MainMenu::initialiseButtons()
{
	float xFirst = 320, yFirst = 80, yDiff = 100;
	sf::Color idleButtonColor = sf::Color(0, 230, 230, 200);
	sf::Color hoveredButtonColor = sf::Color(0, 230, 230, 255);
	sf::Color clickedButtonColor = sf::Color(0, 162, 162, 255);

	this->buttons["PLAY_BTN"] = new Button(320, yFirst+=yDiff, 150, 50,
		this->font, "Play Game", 20,
		idleButtonColor, hoveredButtonColor, clickedButtonColor);

	this->buttons["USER_BTN"] = new Button(320, yFirst += yDiff, 150, 50,
		this->font, "User Levels", 20,
		idleButtonColor, hoveredButtonColor, clickedButtonColor);

	this->buttons["EDITOR_BTN"] = new Button(320, yFirst += yDiff, 150, 50,
		this->font, "Level Editor", 20,
		idleButtonColor, hoveredButtonColor, clickedButtonColor);

	this->buttons["EXIT_BTN"] = new Button(320, yFirst += yDiff, 150, 50,
		this->font, "Exit Game", 20,
		idleButtonColor, hoveredButtonColor, clickedButtonColor);
}


MainMenu::MainMenu(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
	this->initialiseBackground();
	this->initialiseButtons();
}


MainMenu::~MainMenu()
{
	for (auto& pair : this->buttons)	//Zwalnianie pamięci mapy buttons
	{
		delete pair.second;
		pair.second = nullptr;
	}
	buttons.clear();
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


void MainMenu::updateButtons(sf::Event& gameEvent)
{
	
	for (auto& btn : this->buttons)
	{
		btn.second->update(this->viewMousePosition, gameEvent);
	}

	if (this->buttons["PLAY_BTN"]->isPressed())
	{
		this->states->push(new LevelSelect((this->window), this->states));
	}

	if (this->buttons["USER_BTN"]->isPressed())
	{
		//
	}

	if (this->buttons["EDITOR_BTN"]->isPressed())
	{
		//
	}

	//Przycisk wyjścia z gry
	if (this->buttons["EXIT_BTN"]->isPressed())
	{
		this->quitState();
	}
}


void MainMenu::update(sf::Event& gameEvent)
{
	
	this->updateMousePosition();
	this->updateButtons(gameEvent);
}


void MainMenu::renderButtons(sf::RenderTarget* target)
{
	for (auto& btn : this->buttons)
	{
		btn.second->render(*target);
	}
}


void MainMenu::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->menuBackground);
	this->renderButtons(target);
}
