﻿#include "Tile.h"

// Inicjalizacja pól statycznych
sf::Color Tile::outlineColor = sf::Color::Black;
sf::Vector2f Tile::tileSize = sf::Vector2f(25.0f, 25.0f);
float Tile::outlineThickness = 2.0f;
float Tile::tileMargin = 5.0f;



void Tile::setTextures()
{
    if (!texture.loadFromFile("Images/cross.png"))
        std::cout << "Blad odczytu tekstury cross";
}

Tile::Tile() : status(0), targetStatus(0)
{
    this->setTextures();
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
    switch (this->status)
    {
    case UNFILLED:
        return 0;
    case FILLED:
        return 1;
    case CROSSED:
        return 2;
    default:
        return 0;
    }
}

const bool Tile::getBoolCurrentStatus() const
{
    if (this->status == FILLED)
        return true;
    else
        return false;
}

const bool Tile::getTargetStatus() const
{
    return this->targetStatus;
}

const sf::RectangleShape Tile::getTile() const
{
    return tile;
}

const sf::Vector2f Tile::getTileSize()
{
    return tileSize;
}

const float Tile::getTileMargin()
{
    return tileMargin;
}

void Tile::setTilePosition(sf::Vector2f position)
{
    this->tilePosition = position;
    this->tile.setPosition(tilePosition);
}

void Tile::setTilePosition(float xValue, float yValue)
{
    this->tilePosition.x = xValue;
    this->tilePosition.y = yValue;
    this->tile.setPosition(tilePosition.x, tilePosition.y);
}

void Tile::setTargetStatus(unsigned short newTargetStatus)
{
    this->targetStatus = newTargetStatus;
}

void Tile::setStatus(unsigned short newStatus)
{
    this->status = newStatus;

    switch (newStatus)
    {
    case UNFILLED:
        this->tile.setTexture(nullptr);
        this->tile.setFillColor(sf::Color::White);
        break;
    case FILLED:
        this->tile.setFillColor(sf::Color::Black);
        break;
    case CROSSED:
        this->tile.setFillColor(sf::Color::White);
        tile.setTexture(&texture);
        break;
    default:
        break;
    }
}

const void Tile::draw(sf::RenderTarget& target) const
{
    target.draw(this->tile);
}
