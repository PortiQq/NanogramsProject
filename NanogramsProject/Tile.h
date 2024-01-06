﻿#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#define UNFILLED 0
#define FILLED 1
#define CROSSED 2

class Tile
{
	private:
		//pola prywatne
		sf::RectangleShape tile;
		sf::Vector2f tilePosition;
		unsigned short status;
		bool targetStatus;

		//Pola statyczne
		static sf::Color outlineColor;
		static sf::Vector2f tileSize;
		static float outlineThickness;
		static float tileMargin;

		//Pola tekstur
		sf::Texture texture;
		//Metoda odczytująca tekstury z pliku
		void setTextures();

	public:

		//Konstruktory i destruktory
		Tile();
		~Tile();

		//Ustalenie ogólnych szczegółów kratek
		static void setStaticTileParameters(sf::Color outlineColorSet, sf::Vector2f tileSizeSet, float outlineThicknessSet, float tileMarginSet);

		//gettery
		const sf::Vector2f getTilePosition() const;
		const sf::FloatRect getTileGlobalBounds() const;
		const unsigned short getCurrentStatus() const;
		const bool getBoolCurrentStatus() const;	//(gdy CROSSED - zwraca false)
		const bool getTargetStatus() const;
		const sf::RectangleShape getTile() const;
		//gettery dla pól statycznych
		static const sf::Vector2f getTileSize();
		static const float getTileMargin();

		//settery
		void setTilePosition(sf::Vector2f position);
		void setTilePosition(float xValue, float yValue);
		void setTargetStatus(unsigned short newTargetStatus);
		void setStatus(unsigned short newStatus);

		//Inne metody publiczne
		const void draw(sf::RenderTarget& target) const;
};

