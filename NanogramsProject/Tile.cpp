#include "Tile.h"

// Initialization of static members
sf::Color Tile::outlineColor = sf::Color::Black;
sf::Vector2f Tile::tileSize = sf::Vector2f(25.0f, 25.0f);
float Tile::outlineThickness = 2.0f;

Tile::Tile(sf::Vector2f tilePosition, short int status, bool targetStatus)
    : tilePosition(tilePosition), status(status), targetStatus(targetStatus)
{
    sf::Color fillColor = (status) ? sf::Color::Black : sf::Color::White;
    this->tile.setFillColor(fillColor);
    this->tile.setSize(tileSize);
    this->tile.setOutlineColor(this->outlineColor);
    this->tile.setOutlineThickness(this->outlineThickness);
    this->tile.setPosition(this->tilePosition);
}

Tile::Tile()
{
    //
}


Tile::~Tile()
{
    //
}

void Tile::setStaticTileParameters(sf::Color outlineColorSet, sf::Vector2f tileSizeSet, float outlineThicknessSet)
{
    outlineColor = outlineColorSet;
    tileSize = tileSizeSet;
    outlineThickness = outlineThicknessSet;
}

const sf::Vector2f Tile::getTilePosition() const
{
    return sf::Vector2f(this->tilePosition);
}

const sf::FloatRect Tile::getTileGlobalBounds() const
{
    return tile.getGlobalBounds();
}

const unsigned short int Tile::getCurrentStatus() const
{
    return (status) ? FILLED : UNFILLED;
}

const bool Tile::getTargetStatus() const
{
    return this->targetStatus;
}

const sf::RectangleShape Tile::getTile() const
{
    return tile;
}

void Tile::setTilePosition(sf::Vector2f position)
{
    this->tile.setPosition(position);
}

void Tile::setStatus(short int newStatus)
{
    this->status = newStatus;
    (newStatus) ? this->tile.setFillColor(sf::Color::Black) : this->tile.setFillColor(sf::Color::White);
    
}



