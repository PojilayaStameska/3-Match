#include "CloverTile.hpp"

CloverTile::CloverTile(int id)
{
	this->id = id;
	this->texture = TileList::Clover;
	this->borderColor = sf::Color(143, 199, 54);
	this->mainColor = sf::Color(207, 237, 108);
}


void CloverTile::activate(Hero *target)
{
	target->setTernResult(Tile::Clover, target->TurnResult(Tile::Clover) + 1);
	isDead = true;
}