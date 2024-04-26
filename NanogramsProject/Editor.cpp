#include "Editor.h"
#include <Windows.h>

void Editor::initialiseBackground()
{
	this->window->setSize(sf::Vector2u(800.f, 650.f));
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

	this->buttons["CLEAR_BTN"] = new Button(xFirst, yFirst +=yDiff, btnWidth, btnHeight,
		this->font, "Clear board", 18,
		idleButtonColor, hoveredButtonColor, clickedButtonColor);

	this->buttons["RESET_BTN"] = new Button(xFirst, yFirst+= yDiff, btnWidth, btnHeight,
		this->font, "Reset", 18,
		idleButtonColor, hoveredButtonColor, clickedButtonColor);

	this->buttons["SUB_ROWS_BTN"] = new Button(xFirst + 28.5f, yFirst += yDiff, 45, btnHeight,
		this->font, "^", 28,
		idleButtonColor, hoveredButtonColor, clickedButtonColor);

	this->buttons["SUB_COLS_BTN"] = new Button(xFirst, yFirst +=yDiff / 1.5f, 45, btnHeight,
		this->font, "<", 24,
		idleButtonColor, hoveredButtonColor, clickedButtonColor);

	this->buttons["ADD_COLS_BTN"] = new Button(xFirst + 55.f, yFirst, 45, btnHeight,
		this->font, ">", 24,
		idleButtonColor, hoveredButtonColor, clickedButtonColor);

	this->buttons["ADD_ROWS_BTN"] = new Button(xFirst + 28.5f, yFirst += yDiff/1.5f, 45, btnHeight,
		this->font, "v", 24,
		idleButtonColor, hoveredButtonColor, clickedButtonColor);

	this->buttons["SAVE_BTN"] = new Button(xFirst, yFirst += yDiff, btnWidth, btnHeight,
		this->font, "Save Board", 18,
		idleButtonColor, hoveredButtonColor, clickedButtonColor);
	
	rowsText.setPosition(sf::Vector2f(xFirst, yFirst += yDiff));
	colsText.setPosition(sf::Vector2f(xFirst, yFirst += 25.f));
}


void Editor::initialiseTexts()
{
	rowsText.setCharacterSize(16);
	rowsText.setFillColor(sf::Color::Black);
	rowsText.setFont(font);

	colsText.setCharacterSize(16);
	colsText.setFillColor(sf::Color::Black);
	colsText.setFont(font);
}


Editor::Editor(sf::RenderWindow* window, std::stack<State*>* states) : 
	State(window,states), board(crossTexture), rows(1), cols(1)
{
	this->initialiseBackground();
	this->initialiseButtons();
	this->initialiseTexts();
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
	this->window->setSize(sf::Vector2u(800.f, 600.f));
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
		this->saveBoard();
		this->quitState();
	}

	if (this->buttons["CLEAR_BTN"]->isPressed())
	{
		for (auto& tileRow : this->board.getBoard())
		{
			for (auto& tile : tileRow)
			{
				tile->setStatus(0);
			}
		}
	}
	
	if (this->buttons["RESET_BTN"]->isPressed())
	{
		this->rows = 1;
		this->cols = 1;
		this->isSetUp = false;
		Sleep(100);
	}

	if (this->buttons["ADD_COLS_BTN"]->isPressed())
	{
		if (cols < 20)
		{
			this->cols++;
			this->board.addColumn();
			Sleep(100);
		}
	}

	if (this->buttons["ADD_ROWS_BTN"]->isPressed())
	{
		if (rows < 20)
		{
			this->rows++;
			this->board.addRow();
			Sleep(100);
		}
		
	}

	if (this->buttons["SUB_COLS_BTN"]->isPressed())
	{
		if (this->cols > 1)
		{
			this->cols--;
			this->board.subtractColumn();
			Sleep(100);
		}
	}

	if (this->buttons["SUB_ROWS_BTN"]->isPressed())
	{
		if (this->rows > 1)
		{
			this->rows--;
			this->board.subtractRow();
			Sleep(100);
		}
	}

	if (this->buttons["BACK_BTN"]->isPressed())
	{
		this->quitState();
	}
}


void Editor::updateTexts()
{
	std::string rowString = "Rows: " + std::to_string(rows);
	std::string colString = "Cols: " + std::to_string(cols);
	rowsText.setString(rowString);
	colsText.setString(colString);
}


void Editor::update(sf::Event& gameEvent)
{
	
	this->updateMousePosition();
	this->updateButtons(gameEvent);
	this->board.updateEdited(this->viewMousePosition);
	this->updateTexts();
}


void Editor::renderButtons(sf::RenderTarget* target)
{
	for (auto& btn : this->buttons)
	{
		btn.second->render(*target);
	}
}


void Editor::renderTexts(sf::RenderTarget* target)
{
	target->draw(rowsText);
	target->draw(colsText);
}


void Editor::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->editorBackground);
	this->renderTexts(target);
	this->renderButtons(target);
	this->board.renderEdited(*target);
}


void Editor::saveBoard()
{
	int count = 0;

	try {
		for (const auto& entry : std::filesystem::directory_iterator("UserLevels")) {
			if (std::filesystem::is_regular_file(entry.path())) {
				count++;
			}
		}
	}
	catch (const std::filesystem::filesystem_error& e) {
		std::cerr << "ERROR: Blad dostepu do folderu: " << e.what() << std::endl;
	}

	std::string filename = "UserLevels/level" + std::to_string(count + 1) + ".txt";
	outputFile.open(filename, std::ios::app);
	if (outputFile.is_open()) {

		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->cols; j++)
			{
				if (board.getBoard()[i][j]->getCurrentStatus() == 1)
				{
					outputFile << i << " " << j << std::endl;
				}
			}
		}


		outputFile.close();
		std::cout << "Editor: Zapisano do pliku" << std::endl;
	}
	else {
		std::cerr << "ERROR: Editor: Blad otwarcia pliku" << std::endl;
	}

}
