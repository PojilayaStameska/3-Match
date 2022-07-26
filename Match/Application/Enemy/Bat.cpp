#include "Bat.hpp"


Bat::Bat(int level)
{
	this->maxHp = level * 100;
	this->currentHp = maxHp;
	isAlive = true;
	curTile = Tile::BatBottomSecondFrame;
}

void Bat::attack(Entity* hero)
{
	hero->takeDamage(0);
}