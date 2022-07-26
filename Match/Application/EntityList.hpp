#pragma once
#include "Entity.hpp"
#include "../TileEnum.hpp"
#include "../Generator/Factories/IEnemyFactory.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Vertex.hpp>

#include <iostream>
#include <vector>

class EntityList : public sf::Drawable, public sf::Transformable
{
public:
	EntityList(const sf::Texture& tileset);
	bool RealizeDamage(int DamageToRealize);
	void Regenerate(IEnemyFactory* tool);
	void Attack(Entity* target);
	std::vector<Entity*> list;
	void load();
private:

	struct MonsterPlace
	{
		float startX, endX, startY, endY;
	};
	MonsterPlace places[7];
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	std::vector<sf::Vertex> vertices;
	std::vector<sf::Vertex> verticesHp;
	const sf::Texture& tileSet;
};