#pragma once
#include <SFML/Graphics.hpp>

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
		unsigned short targetStatus;

		//Pola statyczne
		static sf::Color outlineColor;
		static sf::Vector2f tileSize;
		static float outlineThickness;
		static float tileMargin;


	public:

		//Konstruktory i destruktory
		Tile(sf::Vector2f tilePosition, unsigned short initialStatus, bool targetStatus);
		Tile();
		~Tile();

		static void setStaticTileParameters(sf::Color outlineColorSet, sf::Vector2f tileSizeSet, float outlineThicknessSet, float tileMarginSet);

		//gettery
		const sf::Vector2f getTileSize() const;
		const float getTileMargin() const;
		const sf::Vector2f getTilePosition() const;
		const sf::FloatRect getTileGlobalBounds() const;
		const unsigned short getCurrentStatus() const;
		const unsigned short getTargetStatus() const;
		const sf::RectangleShape getTile() const;

		//settery
		void setTilePosition(sf::Vector2f position);
		void setTargetStatus(unsigned short newTargetStatus);
		void setStatus(unsigned short newStatus);
		void changeStatus();

};

