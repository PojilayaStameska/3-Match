#include "ShieldTile.hpp"

ShieldTile::ShieldTile(int id)
{
	this->id = id;
	this->texture = TileList::Shield;
	this->mainColor = sf::Color(175, 113, 80);
	this->borderColor = sf::Color(142, 80, 47);
}


void ShieldTile::activate(Hero *target)
{
	target->setTernResult(Tile::Shield, target->TurnResult(Tile::Shield) + 1);
	isDead = true;
}