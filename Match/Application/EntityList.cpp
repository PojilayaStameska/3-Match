#pragma once
#include "EntityList.hpp"


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

EntityList::EntityList(const sf::Texture& tileset):
	tileSet(tileset)
{
	list.resize(7);
	for (int i = 0; i < 4; i++)
	{
		places[i].startX = 500 + 250 * i;
		places[i].endX = 620 + 250 * i;
		places[i].startY = 100;
		places[i].endY = 220;
	}
	for (int i = 4; i < 7; i++)
	{
		places[i].startX = 620 + 250 * (i-4);
		places[i].endX = 750 + 250 * (i-4);
		places[i].startY = 280;
		places[i].endY = 400;
	}
}

bool EntityList::RealizeDamage(int DamageToRealize)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (DamageToRealize >= list[i]->CurHp())
		{
			DamageToRealize -= list[i]->CurHp();
			list[i]->takeDamage(list[i]->CurHp());
		}
		else
		{
			list[i]->takeDamage(DamageToRealize);
			DamageToRealize = 0;
			break;
		}
	}
	return true;
}

template <typename T>
void delete_pointed_to(T* const ptr)
{
	delete ptr;
}

void EntityList::Regenerate(IEnemyFactory* tool)
{
	std::for_each(list.begin(), list.end(), delete_pointed_to<Entity>);
	for (int i = 0; i < list.size(); i++)
	{
		list[i] = tool->createEnemy(1);
	}

}

void EntityList::Attack(Entity* target)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i]->IsAlive())
		{
			list[i]->attack(target);
		}
	}
}

void EntityList::load()
{
	vertices.clear();
	verticesHp.clear();
	verticesHp.resize(list.size() * 8);
	vertices.resize(list.size() * 4);

	for (int i = 0; i < list.size(); i++)
	{
		int tileNumber = (int)list[i]->CurTile();

		int tu = tileNumber % (tileSet.getSize().x / 16);
		int tv = tileNumber / (tileSet.getSize().x / 16);

		sf::Vertex* quad = &vertices[ i * 4];

		quad[0].position = sf::Vector2f(places[i].startX, places[i].startY);
		quad[1].position = sf::Vector2f(places[i].endX, places[i].startY);
		quad[2].position = sf::Vector2f(places[i].endX, places[i].endY);
		quad[3].position = sf::Vector2f(places[i].startX, places[i].endY);

		quad[0].texCoords = sf::Vector2f((tu + 0.f) * 16, (tv + 0.f) * 16);
		quad[1].texCoords = sf::Vector2f((tu + 1.f) * 16, (tv + 0.f) * 16);
		quad[2].texCoords = sf::Vector2f((tu + 1.f) * 16, (tv + 1.f) * 16);
		quad[3].texCoords = sf::Vector2f((tu + 0.f) * 16, (tv + 1.f) * 16);


		sf::Vertex* quads = &verticesHp[i * 8];
		int length = places[i].endX - places[i].startX;
		length = length * ((float)list[i]->CurHp() / (float)list[i]->MaxHp());
		quads[0].position = sf::Vector2f(places[i].startX, places[i].endY);
		quads[1].position = sf::Vector2f(places[i].endX, places[i].endY);
		quads[2].position = sf::Vector2f(places[i].endX, places[i].endY + 20);
		quads[3].position = sf::Vector2f(places[i].startX, places[i].endY + 20);

		quads[4].position = sf::Vector2f(places[i].startX, places[i].endY + 20);
		quads[5].position = sf::Vector2f(places[i].startX, places[i].endY);
		quads[6].position = sf::Vector2f(places[i].startX + length , places[i].endY);
		quads[7].position = sf::Vector2f(places[i].startX + length , places[i].endY + 20);

		quads[4].color = sf::Color(255, 20, 63, 120);
		quads[5].color = sf::Color(255, 20, 63, 120);
		quads[6].color = sf::Color(255, 20, 63, 120);
		quads[7].color = sf::Color(255, 20, 63, 120);

		quads[0].color = sf::Color(0, 0, 0);
		quads[1].color = sf::Color(0, 0, 0);
		quads[2].color = sf::Color(0, 0, 0);
		quads[3].color = sf::Color(0, 0, 0);

	}
}

void EntityList::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &tileSet;
	target.draw(&vertices[0], vertices.size(), sf::Quads, states);
	target.draw(&verticesHp[0], verticesHp.size(), sf::Quads);
}
