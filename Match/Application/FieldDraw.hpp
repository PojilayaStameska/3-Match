#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Vertex.hpp>

#include <vector>

class Field;

class FieldDraw : public sf::Drawable, public sf::Transformable
{
public:
	FieldDraw(const sf::Texture& tileset, const sf::Vector2i& tileSize);

	void load(const Field& field);

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	const sf::Texture& tileset;
	const sf::Vector2i tileSize;
	std::vector<sf::CircleShape> Circles;
	std::vector<sf::Vertex> vertices;
	std::vector<sf::Vertex> verticesBg;
};
