#include "Tile.h"

// Inicjalizacja pól statycznych
sf::Color Tile::outlineColor = sf::Color::Black;
sf::Vector2f Tile::tileSize = sf::Vector2f(25.0f, 25.0f);
float Tile::outlineThickness = 2.0f;
float Tile::tileMargin = 5.0f;

Tile::Tile(sf::Vector2f tilePosition, unsigned short initialStatus, bool targetStatus)
    : tilePosition(tilePosition), status(initialStatus), targetStatus(targetStatus)
{
    this->setStatus(this->status);
    this->tile.setSize(tileSize);
    this->tile.setOutlineColor(outlineColor);
    this->tile.setOutlineThickness(outlineThickness);
    this->tile.setPosition(this->tilePosition);
}

Tile::Tile() : status(0), targetStatus(0)
{
    this->setStatus(this->status);
    this->tile.setSize(tileSize);
    this->tile.setOutlineColor(outlineColor);
    this->tile.setOutlineThickness(outlineThickness);
    this->tile.setPosition(this->tilePosition);
}


Tile::~Tile()
{
    //
}

void Tile::setStaticTileParameters(sf::Color outlineColorSet, sf::Vector2f tileSizeSet, float outlineThicknessSet, float tileMarginSet)
{
    outlineColor = outlineColorSet;
    tileSize = tileSizeSet;
    outlineThickness = outlineThicknessSet;
    tileMargin = tileMarginSet;
}

const sf::Vector2f Tile::getTileSize() const
{
    return this->tileSize;
}

const float Tile::getTileMargin() const
{
    return tileMargin;
}

const sf::Vector2f Tile::getTilePosition() const
{
    return sf::Vector2f(this->tilePosition);
}

const sf::FloatRect Tile::getTileGlobalBounds() const
{
    return tile.getGlobalBounds();
}

const unsigned short Tile::getCurrentStatus() const
{
    return (status) ? FILLED : UNFILLED;
}

const unsigned short Tile::getTargetStatus() const
{
    return this->targetStatus;
}

const sf::RectangleShape Tile::getTile() const
{
    return tile;
}

void Tile::setTilePosition(sf::Vector2f position)
{
    this->tilePosition = position;
    this->tile.setPosition(tilePosition);
}

void Tile::setTargetStatus(unsigned short newTargetStatus)
{
    this->targetStatus = newTargetStatus;
}

void Tile::setStatus(unsigned short newStatus)
{
    this->status = newStatus;
    (newStatus) ? this->tile.setFillColor(sf::Color::Black) : this->tile.setFillColor(sf::Color::White);
}

void Tile::changeStatus()
{
    this->status++;
    status = status % 2;
    (status) ? this->tile.setFillColor(sf::Color::Black) : this->tile.setFillColor(sf::Color::White);
}

