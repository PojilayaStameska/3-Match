#include "ThunderTile.hpp"

ThunderTile::ThunderTile(int id)
{
	this->id = id;
	this->texture = TileList::Thunder;
	this->mainColor = sf::Color(172, 134, 255);
	this->borderColor = sf::Color(140, 102, 222);
}


void ThunderTile::activate(Hero *target)
{
	target->setTernResult(Tile::Thunder, target->TurnResult(Tile::Thunder) + 1);
	isDead = true;
}