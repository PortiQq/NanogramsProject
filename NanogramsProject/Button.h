#pragma once

#include<SFML/Graphics.hpp>
#include <map>

#define BTN_IDLE 0
#define BTN_HOVER 1
#define BTN_PRESSED 2

class Button
{
private:
	unsigned short buttonStatus;

	sf::RectangleShape button;
	sf::Font& font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;
public:
	Button(float x, float y, float width, float height, 
		sf::Font& font, std::string text, int characterSize,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	~Button();

	//gettery
	const bool isPressed() const;

	//Metody
	void centralisePosition(sf::Vector2u windowSize, float yPos);
	void update(sf::Vector2f mousePosition, sf::Event& event);
	void render(sf::RenderTarget& target);

};

