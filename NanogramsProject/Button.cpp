#include "Button.h"


Button::Button(float x, float y, float width, float height, 
	sf::Font& font, std::string text, int characterSize, 
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor) :
	font(font)
{
	this->buttonStatus = 0;

	this->button.setPosition(sf::Vector2f(x, y));
	this->button.setSize(sf::Vector2f(width, height));

	this->text.setFont(this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(characterSize);
	this->text.setPosition
	(
		this->button.getPosition().x + (this->button.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->button.getPosition().y + (this->button.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f - 2.5f
	);
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
}

Button::~Button()
{

}

const bool Button::isPressed() const
{
	if(this->buttonStatus == BTN_PRESSED)
		return true;
	return false;
}

void Button::update(sf::Vector2f mousePosition, sf::Event& event)
{

	this->buttonStatus = BTN_IDLE;	//Gdy nic się nie dzieje

	if (this->button.getGlobalBounds().contains(mousePosition))	//Gdy najedziemy na przycisk
	{
		this->buttonStatus = BTN_HOVER;

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)	//Gdy wciśniemy przycisk
		{
			this->buttonStatus = BTN_PRESSED;
		}
	}

	switch (buttonStatus)
	{
	case BTN_IDLE:
		this->button.setFillColor(this->idleColor);
		break;
	case BTN_HOVER:
		this->button.setFillColor(this->hoverColor);
		break;
	case BTN_PRESSED:
		this->button.setFillColor(this->activeColor);
		break;
	default:
		break;
	}
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->button);
	target.draw(this->text);
}
