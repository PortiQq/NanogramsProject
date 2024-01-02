#include "Number.h"

// Inicjalizacja pól statycznych

sf::Color Number::textColor = sf::Color::Black;
sf::Vector2f Number::boxSize = sf::Vector2f(25.0f, 25.0f);
float Number::outlineThickness = 0.f;
float Number::boxMargin = 5.0f;
unsigned short Number::characterSize = 20;

Number::Number(sf::Font& font, sf::Color boxColor)
    : font(font), boxColor(boxColor), value(0)
{
    text.setFont(font);
    text.setCharacterSize(characterSize);
    text.setFillColor(textColor);

    textBox.setSize(boxSize);
    textBox.setOutlineThickness(outlineThickness);
    textBox.setFillColor(boxColor);
    updateText();
}

void Number::setStaticTextBoxParameters(sf::Color textColorSet, sf::Vector2f boxSizeSet, float outlineThicknessSet, float boxMarginSet, unsigned short characterSizeSet)
{
    textColor = textColorSet;
    boxSize = boxSizeSet;
    outlineThickness = outlineThicknessSet;
    boxMargin = boxMarginSet;
    characterSize = characterSizeSet;

}

//Number::Number()
//{
//	//
//}

Number::~Number()
{
	//
}

void Number::setValue(int value)
{
	this->value = value;
	updateText();
}

void Number::setTextBoxPosition(sf::Vector2f newPosition)
{
    // Ustawienie pozycji tekstu na środku kratki
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(position.x + (textBox.getSize().x - textBounds.width) / 2,
        position.y + (textBox.getSize().y - textBounds.height) / 2);

    textBox.setPosition(newPosition);
}

void Number::updateText() 
{
    std::string textString = std::to_string(value);
    text.setString(textString);
}

void Number::draw(sf::RenderWindow& target)
{
	target.draw(textBox);
	target.draw(text);
}
