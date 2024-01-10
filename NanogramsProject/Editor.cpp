#include "Editor.h"
#include <filesystem>
#include <Windows.h>

void Editor::initialiseBackground()
{
	this->editorBackground.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);
	this->editorBackground.setFillColor(sf::Color(130, 120, 129, 255));
}

void Editor::initialiseButtons()
{
	float xFirst = window->getSize().x - 150.f, yFirst = 30.f, yDiff = 80.f;
	float btnWidth = 100.f, btnHeight = 50.f;
	sf::Color idleButtonColor = sf::Color(0, 230, 230, 200);
	sf::Color hoveredButtonColor = sf::Color(0, 230, 230, 255);
	sf::Color clickedButtonColor = sf::Color(0, 162, 162, 255);



	this->buttons["BACK_BTN"] = new Button(xFirst, yFirst, btnWidth, btnHeight,
		this->font, "Main menu", 18,
		idleButtonColor, hoveredButtonColor, clickedButtonColor);

	this->buttons["SAVE_BTN"] = new Button(xFirst, yFirst += yDiff, btnWidth, btnHeight,
		this->font, "Save Board", 18,
		idleButtonColor, hoveredButtonColor, clickedButtonColor);

	this->buttons["LOAD_BTN"] = new Button(xFirst, yFirst += yDiff, btnWidth, btnHeight,
		this->font, "Load Board", 18,
		idleButtonColor, hoveredButtonColor, clickedButtonColor);

	this->buttons["MORE_ROWS_BTN"] = new Button(xFirst, yFirst += yDiff, 45, btnHeight,
		this->font, "v", 30,
		idleButtonColor, hoveredButtonColor, clickedButtonColor);

	this->buttons["MORE_COLS_BTN"] = new Button(xFirst + 55.f, yFirst += yDiff, 45, btnHeight,
		this->font, ">", 30,
		idleButtonColor, hoveredButtonColor, clickedButtonColor);

	this->buttons["GENERATE_BTN"] = new Button(xFirst, yFirst += yDiff/1.5f, btnWidth, btnHeight,
		this->font, "Generate", 18,
		idleButtonColor, hoveredButtonColor, clickedButtonColor);

	this->buttons["LESS_ROWS_BTN"] = new Button(xFirst, yFirst += yDiff/1.5f, 45, btnHeight,
		this->font, "^", 24,
		idleButtonColor, hoveredButtonColor, clickedButtonColor);

	this->buttons["LESS_COLS_BTN"] = new Button(xFirst + 55.f, yFirst, 45, btnHeight,
		this->font, "<", 24,
		idleButtonColor, hoveredButtonColor, clickedButtonColor);

	
}

Editor::Editor(sf::RenderWindow* window, std::stack<State*>* states) : 
	State(window,states), board(crossTexture), rows(1), cols(1)
{
	this->initialiseBackground();
	this->initialiseButtons();
}


Editor::~Editor()
{
	for (auto& pair : this->buttons)	//Zwalnianie pamięci mapy buttons
	{
		delete pair.second;
		pair.second = nullptr;
	}
	buttons.clear();
}


void Editor::setUpState()
{
	board.setUpEdited(this->rows, this->cols);
	this->isSetUp = true;
}


void Editor::endState()
{
	std::cout << "Wychodzenie ze stanu Edytora\n";
	std::cout << "...\n";
	this->outputFile.close();
	std::cout << "Stan Edytora zakonczony" << std::endl;
}


void Editor::updateButtons(sf::Event& gameEvent)
{
	for (auto& btn : this->buttons)
	{
		btn.second->update(this->viewMousePosition, gameEvent);
	}

	if (this->buttons["SAVE_BTN"]->isPressed())
	{
		this->quitState();
	}

	if (this->buttons["LOAD_BTN"]->isPressed())
	{
		this->quitState();
	}

	if (this->buttons["MORE_COLS_BTN"]->isPressed())
	{
		this->cols++;
		Sleep(100);
		this->isSetUp = false;
	}

	if (this->buttons["MORE_ROWS_BTN"]->isPressed())
	{
		this->rows++;
		Sleep(100);
		this->isSetUp = false;
	}

	if (this->buttons["LESS_COLS_BTN"]->isPressed())
	{
		if (this->cols > 1)
		{
			this->cols--;
			Sleep(100);
			this->isSetUp = false;
		}
	}

	if (this->buttons["LESS_ROWS_BTN"]->isPressed())
	{
		if (this->rows > 1)
		{
			this->rows--;
			Sleep(100);
			this->isSetUp = false;
		}
			
	}

	if (this->buttons["GENERATE_BTN"]->isPressed())
	{
		this->quitState();
	}

	if (this->buttons["BACK_BTN"]->isPressed())
	{
		this->quitState();
	}
}


void Editor::update(sf::Event& gameEvent)
{
	this->updateMousePosition();
	this->updateButtons(gameEvent);
	this->board.updateBoard(this->viewMousePosition);
}


void Editor::renderButtons(sf::RenderTarget* target)
{
	for (auto& btn : this->buttons)
	{
		btn.second->render(*target);
	}
}


void Editor::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->editorBackground);
	this->renderButtons(target);
	this->board.renderEdited(*target);
}
