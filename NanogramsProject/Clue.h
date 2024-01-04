#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include<string>
class Clue
{
private:
	
	sf::Text text;
	sf::RectangleShape textBox;
	sf::Font font;
	//sf::Font& textFont;
	
	//statyczne pola skopiowane z Tile
	static sf::Color textColor;
	static unsigned short characterSize;
	static sf::Vector2f boxSize;
	static float outlineThickness;
	static float boxMargin;

	sf::Color boxColor;

	sf::Vector2f position;
	unsigned short value;
public:
	//konstruktory, destruktor, ustawienie parametrów statycznych
	Clue();
	Clue(sf::Font& font, sf::Color boxColor);
	Clue(unsigned short value);
	~Clue();
	static void setStaticTextBoxParameters(
		sf::Color textColorSet, 
		sf::Vector2f boxSizeSet, 
		float outlineThicknessSet, 
		float boxMarginSet,
		unsigned short characterSizeSet
	);

	//settery
	void setValue(int value);
	void setTextBoxPosition(sf::Vector2f newPosition);

	//gettery

	//Inne metody publiczne
	void updateText();
	void draw(sf::RenderWindow& target);
};

