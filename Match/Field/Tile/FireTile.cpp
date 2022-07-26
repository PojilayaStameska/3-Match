#include "FireTile.hpp"

FireTile::FireTile(int id)
{
	this->id = id;
	this->texture = TileList::Fire;
	this->mainColor = sf::Color(244,147,180);
	this->borderColor = sf::Color(226, 111, 139);
}


void FireTile::activate(Hero *target)
{
	target->setTernResult(Tile::Fire, target->TurnResult(Tile::Fire) + 1);
	isDead = true;
}