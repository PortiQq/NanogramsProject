#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include<string>

#define NO_OVERLINE false
#define OVERLINE true

class Clue
{
private:
	
	sf::Text text;
	sf::RectangleShape textBox;
	sf::Font font;
	sf::Vector2f position;
	unsigned short value;
	bool crossedOut;

	//pola statyczne
	static sf::Color textColor;
	static unsigned short characterSize;
	static sf::Vector2f boxSize;
	static float outlineThickness;
	static float boxMargin;
	
public:
	//konstruktor, destruktor, ustawienie parametrów statycznych
	Clue(unsigned short value, sf::Font& font);
	~Clue();
	static void setStaticCluesParameters(
		sf::Color textColorSet, 
		sf::Vector2f boxSizeSet, 
		float outlineThicknessSet, 
		float boxMarginSet,
		unsigned short characterSizeSet
	);

	//settery
	void setValue(int value);
	void setStatus(bool newStatus);
	void setCluePosition(float xValue, float yValue);
	void setNewCharacterSize(int newCharacterSize);

	//gettery
	const unsigned short getValue() const;
	static const float getBoxMargin();
	const sf::RectangleShape getTextBox() const;
	const sf::Text getText() const;

	//Inne metody publiczne
	void updateText();
	const void draw(sf::RenderTarget& target) const;
};

