#pragma once
#include "State.h"
#include "MainMenu.h"
#include "GameState.h"

class LevelSelect : public State
{
private:
	sf::RectangleShape levelSelectBackground;

	std::vector<Button*> buttons;
	Button* backButton;

	std::ifstream levelFile;

	void initialiseBackground();
	void initialiseButtons();
	void loadFile(std::string filename);
public:
	LevelSelect(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~LevelSelect();

	void setUpState();
	void endState();
	void update(sf::Event& gameEvent);
	void render(sf::RenderTarget* target = nullptr);
};

