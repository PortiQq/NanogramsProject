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


void Clue::loadFont()
{
    if (!font.loadFromFile("Fonts/Arial.ttf"))
    {
        std::cerr << "Failed to load font from file Fonts/arial.ttf" << std::endl;
    }
}


Clue::Clue() : textBox(), position(0.0f, 0.0f), value(0), crossedOut(false)
{
    text.setCharacterSize(characterSize);
    text.setFillColor(textColor);
    this->setValue(this->value);
    
    this->loadFont();
    text.setFont(font);

    textBox.setSize(boxSize);
    textBox.setOutlineThickness(outlineThickness);
    
}

//TODO: Dodać czcionkę jako parametr
Clue::Clue(unsigned short value) : textBox(), position(0.0f, 0.0f), value(value), crossedOut(false)
{
    text.setCharacterSize(characterSize);
    text.setFillColor(textColor);
    
    this->setValue(this->value);

    this->loadFont();   //TODO: To pójdzie do usunięcia
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


void Clue::setCluePosition(sf::Vector2f newPosition)
{
    this->position = newPosition;
    textBox.setPosition(this->position);
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        position.x + (textBox.getGlobalBounds().width /2.f) - textBounds.width / 2.f,
        position.y + (textBox.getGlobalBounds().height /2.f) - textBounds.height  / 2.f );
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


const float Clue::getBoxMargin()
{
    return boxMargin;
}

const sf::RectangleShape Clue::getTextBox() const
{
    return this->textBox;
}

const sf::Text Clue::getText() const
{
    return this->text;
}

const void Clue::draw(sf::RenderTarget& target) const
{
	target.draw(this->text);
}
