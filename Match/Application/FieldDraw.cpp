#pragma once
#include "FieldDraw.hpp"
#include "../Field/Field.hpp"
#include "../Utility/Utility.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

FieldDraw::FieldDraw(const sf::Texture& tileset, const sf::Vector2i& tileSize)
	: tileset(tileset)
	, tileSize(tileSize)
{
}

void FieldDraw::load(const Field& field)
{
	vertices.clear();
	vertices.resize(field.width * field.height * 4);

	Circles.clear();
	Circles.resize(field.width * field.height);

	for (int y = 8; y < field.height + 8; ++y)
		for (int x = 6; x < field.width + 6; ++x)
		{
			int id = (x - 6 + (y - 8) * field.width);
			int tileNumber = (int)field.getTile(x-6, y - 8)->Texture();

			if (tileNumber < 0)
				continue;

			int tu = tileNumber % (tileset.getSize().x / tileSize.x);
			int tv = tileNumber / (tileset.getSize().x / tileSize.x);

			sf::Vertex* quad = &vertices[(x - 6 + (y - 8) * field.width) * 4];

			quad[0].position = sf::Vector2f((x + 0.12f) * tileSize.x, (y + 0.12f) * tileSize.y);
			quad[1].position = sf::Vector2f((x + 0.78f) * tileSize.x, (y + 0.12f) * tileSize.y);
			quad[2].position = sf::Vector2f((x + 0.78f) * tileSize.x, (y + 0.78f) * tileSize.y);
			quad[3].position = sf::Vector2f((x + 0.12f) * tileSize.x, (y + 0.78f) * tileSize.y);

			quad[0].texCoords = sf::Vector2f((tu + 0.f) * 32, (tv + 0.f) * 32);
			quad[1].texCoords = sf::Vector2f((tu + 1.f) * 32, (tv + 0.f) * 32);
			quad[2].texCoords = sf::Vector2f((tu + 1.f) * 32, (tv + 1.f) * 32);
			quad[3].texCoords = sf::Vector2f((tu + 0.f) * 32, (tv + 1.f) * 32);

			Circles[id].setPosition(sf::Vector2f((x + 0.f) * tileSize.x, (y + 0.f) * tileSize.y));
			Circles[id].setRadius(35.0);
			/*Circles[id].setPointCount(8);*/

			if (id == field.idFocused)
				Circles[id].setOutlineColor(sf::Color(255, 255, 255));
			else
				Circles[id].setOutlineColor(field.getTile(x - 6, y - 8)->BorderColor());
			Circles[id].setOutlineThickness(4);
			Circles[id].setFillColor(field.getTile(x - 6, y - 8)->MainColor());
		}
}

void FieldDraw::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &tileset;
	for (const auto& circle : Circles)
	{
		target.draw(circle);
	}
	target.draw(&vertices[0], vertices.size(), sf::Quads, states);
}
