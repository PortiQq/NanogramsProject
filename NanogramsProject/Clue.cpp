#include "Clue.h"

// Inicjalizacja pól statycznych

sf::Color Clue::textColor = sf::Color::Black;
sf::Vector2f Clue::boxSize = sf::Vector2f(25.0f, 25.0f);
float Clue::outlineThickness = 0.f;
float Clue::boxMargin = 2.5f;
unsigned short Clue::characterSize = 20;


void Clue::setStaticCluesParameters(sf::Color textColorSet, sf::Vector2f boxSizeSet, float outlineThicknessSet, float boxMarginSet, unsigned short characterSizeSet)
{
    textColor = textColorSet;
    characterSize = characterSizeSet;
    boxSize = boxSizeSet;
    outlineThickness = outlineThicknessSet;
    boxMargin = boxMarginSet;
}


Clue::Clue(unsigned short value, sf::Font& font) : 
    textBox(), position(0.0f, 0.0f), value(value), crossedOut(false)
{
    text.setCharacterSize(characterSize);
    text.setFillColor(textColor);
    this->setValue(this->value);
    text.setFont(font);

    textBox.setSize(boxSize);
    textBox.setOutlineThickness(outlineThickness);
}


Clue::~Clue()
{
	//
}


void Clue::setValue(int value)
{
	this->value = value;
	updateText();
}


void Clue::setStatus(bool newStatus)
{
    this->crossedOut = newStatus;
    (this->crossedOut) ? 
        text.setStyle(sf::Text::Style::StrikeThrough) : 
        text.setStyle(sf::Text::Style::Regular);
}


void Clue::updateText()
{
    std::string textString = std::to_string(value);
    text.setString(textString);
}


void Clue::setCluePosition(float xValue, float yValue)
{
    this->position.x = xValue;
    this->position.y = yValue;
    textBox.setPosition(position.x, position.y);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(position.x + (textBox.getSize().x - textBounds.width) / 2,
        position.y + (textBox.getSize().y - textBounds.height) / 2);
}


void Clue::setNewCharacterSize(int newCharacterSize)
{
    this->text.setCharacterSize(newCharacterSize);
}


const unsigned short Clue::getValue() const
{
    return this->value;
}


const float Clue::getBoxMargin()    
{
    return boxMargin;
}


const sf::RectangleShape Clue::getTextBox() const   //
{
    return this->textBox;
}


const sf::Text Clue::getText() const    //
{
    return this->text;
}


const void Clue::draw(sf::RenderTarget& target) const
{
	target.draw(this->text);
}
