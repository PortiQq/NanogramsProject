#include "LevelSelect.h"
//#include <filesystem>	//TODO: Można zrobić zliczanie plików leveli w folderze

void LevelSelect::initialiseBackground()
{
	this->levelSelectBackground.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);
	this->levelSelectBackground.setFillColor(sf::Color(180, 70, 69, 255));
}


void LevelSelect::initialiseButtons()		//TODO: Do poprawy pozycje
{
	sf::Color idleButtonColor = sf::Color(0, 230, 230, 200);
	sf::Color hoveredButtonColor = sf::Color(0, 230, 230, 255);
	sf::Color clickedButtonColor = sf::Color(0, 162, 162, 255);

	backButton = new Button(320.f, 30.f, 150.f, 50.f,
		font, "Back to main menu", 14,
		idleButtonColor, hoveredButtonColor, clickedButtonColor);

	int levelCount = 32;		
	
	float xInitial = 25.f, yInitial = 125.f;
	float xPos = xInitial, yPos = yInitial;
	int temp = 1;
	for (int i = 0; i < levelCount; ++i)
	{ 
		std::string buttonText = "Level\n   " + std::to_string(i + 1);
		this->buttons.push_back(new Button(xPos, yPos, 50.f, 50.f,
		font, buttonText, 14,
		idleButtonColor, hoveredButtonColor, clickedButtonColor));
	
		
		if (xPos > window->getSize().x - 100)
		{
			xPos = xInitial + 100;
			temp++;
			yPos = 125.f * temp;
		}
		xPos = xInitial + 100 * (i + 1) % window->getSize().x;
	}
}


void::LevelSelect::loadFile(std::string filename)
{
	levelFile.open(filename);
	if (!levelFile.is_open()) {
		std::cerr << "ERROR: LevelSelect: Blad odczytu pliku w funkcji LoadFile: " << std::endl;
		exit(1);
	}
}


LevelSelect::LevelSelect(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
	this->initialiseBackground();
	this->initialiseButtons();
}


LevelSelect::~LevelSelect()
{
	for (auto& button : this->buttons)
	{
		delete button;
	}
	delete this->backButton;
}


void LevelSelect::setUpState()
{
	this->isSetUp = true;
}


void LevelSelect::endState()
{
	std::cout << "Wychodzenie ze stanu wyboru poziomow\n";
	std::cout << "...\n";
	std::cout << "Stan wyboru poziomow zakonczony" << std::endl;
}


void LevelSelect::update(sf::Event& gameEvent)
{
	this->updateMousePosition();

	backButton->update(viewMousePosition, gameEvent);
	if (this->backButton->isPressed())
		quitState();

	int it = 0;		//Iterator dla nazw plików
	for (auto& button : this->buttons)
	{
		button->update(this->viewMousePosition, gameEvent);
		if (button->isPressed())
		{
			std::string filename = "Levels/level" + std::to_string(it + 1) + ".txt";
			this->states->push(new GameState(this->window, this->states, filename));
		}
		it++;
	}

	
}


void LevelSelect::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->levelSelectBackground);	//Rysowanie tła

	this->backButton->render(*target);

	for (auto& button : this->buttons)	//Wyświetlanie wszystkich przycisków
	{
		button->render(*target);
	}
}
