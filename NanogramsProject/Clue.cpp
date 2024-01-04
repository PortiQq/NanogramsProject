#include "Clue.h"

// Inicjalizacja pól statycznych

sf::Color Clue::textColor = sf::Color::Black;
sf::Vector2f Clue::boxSize = sf::Vector2f(25.0f, 25.0f);
float Clue::outlineThickness = 0.f;
float Clue::boxMargin = 5.0f;
unsigned short Clue::characterSize = 20;


void Clue::setStaticTextBoxParameters(sf::Color textColorSet, sf::Vector2f boxSizeSet, float outlineThicknessSet, float boxMarginSet, unsigned short characterSizeSet)
{
    textColor = textColorSet;
    characterSize = characterSizeSet;
    boxSize = boxSizeSet;
    outlineThickness = outlineThicknessSet;
    boxMargin = boxMarginSet;
}

Clue::Clue() : textBox(), boxColor(sf::Color::White), position(0.0f, 0.0f), value(0)
{
    text.setCharacterSize(characterSize);
    text.setFillColor(textColor);
    this->setValue(this->value);
    
    if (!font.loadFromFile("Fonts/arial.ttf"))
    {
        std::cerr << "Failed to load font from file Fonts/arial.ttf" << std::endl;
    }
    text.setFont(font);

    textBox.setSize(boxSize);
    textBox.setOutlineThickness(outlineThickness);
    textBox.setFillColor(boxColor);
    this->setTextBoxPosition(position);
}

Clue::Clue(sf::Font& font, sf::Color boxColor) : font(font), textBox(), boxColor(boxColor), position(10.0f, 10.0f), value(5)
{
    text.setCharacterSize(characterSize);
    text.setFillColor(textColor);
    this->setValue(this->value);

    text.setFont(font);

    textBox.setSize(boxSize);
    textBox.setOutlineThickness(outlineThickness);
    textBox.setFillColor(sf::Color(150, 150, 125, 255));
    this->setTextBoxPosition(position);
}

Clue::Clue(unsigned short value) : textBox(), boxColor(sf::Color::Cyan), position(0.0f, 0.0f), value(value)
{
    text.setCharacterSize(characterSize);
    text.setFillColor(textColor);
    this->setValue(this->value);
    if (!font.loadFromFile("Fonts/arial.ttf"))
    {
        std::cerr << "Failed to load font from file Fonts/arial.ttf" << std::endl;
    }
    text.setFont(font);

    textBox.setSize(boxSize);
    textBox.setOutlineThickness(outlineThickness);
    textBox.setFillColor(boxColor);
    this->setTextBoxPosition(position);
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

void Clue::setTextBoxPosition(sf::Vector2f newPosition)
{
    //TODO: Poprawić: Ustawienie pozycji tekstu na środku kratki
   
    this->position = newPosition;
    textBox.setPosition(this->position);
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(position.x + (textBox.getSize().x - textBounds.width) / 2,
        position.y + (textBox.getSize().y - textBounds.height) / 2);
}

void Clue::updateText()
{
    std::string textString = std::to_string(value);
    text.setString(textString);
}

void Clue::draw(sf::RenderWindow& target)
{
	target.draw(textBox);
	target.draw(text);
}
