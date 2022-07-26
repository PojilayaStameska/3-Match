#include "HeartTile.hpp"
#include <iostream>

HeartTile::HeartTile(int id)
{
	this->id = id;
	this->texture = TileList::Heart;
	this->mainColor = sf::Color(213, 219, 239);
	this->borderColor = sf::Color(197, 189, 219);
}


void HeartTile::activate(Hero *target)
{
	target->setTernResult(Tile::Heart, target->TurnResult(Tile::Heart) + 1);
	isDead = true;
}