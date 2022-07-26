#include "Slime.hpp"


Slime::Slime(int level)
{
	this->maxHp = level * 100;
	this->currentHp = maxHp;
	isAlive = true;
	curTile = Tile::SlimeBottomSecondFrame;
	//frameNumber = 0.0f;
}

void Slime::attack(Entity* hero)
{
	hero->takeDamage(5);
}