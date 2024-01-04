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
	unsigned short value;
	sf::Vector2f position;

	//pola statyczne
	static sf::Color textColor;
	static unsigned short characterSize;
	static sf::Vector2f boxSize;
	static float outlineThickness;
	static float boxMargin;

	//Metoda do ładowania czcionki z pliku
	void loadFont();
	
public:
	//konstruktory, destruktor, ustawienie parametrów statycznych
	Clue();
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
	void setCluePosition(sf::Vector2f newPosition);
	void setCluePosition(float xValue, float yValue);

	//gettery
	static const float getBoxMargin();
	const sf::RectangleShape getTextBox() const;
	const sf::Text getText() const;

	//Inne metody publiczne
	void updateText();
	const void draw(sf::RenderWindow& target) const;
};

