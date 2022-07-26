#include "Ghost.hpp"


Ghost::Ghost(int level)
{
	this->maxHp = level * 100;
	this->currentHp = maxHp;
	isAlive = true;
	curTile = Tile::GhostBottomSecondFrame;
	/*frameNumber = 0.0f;*/
}

void Ghost::attack(Entity* hero)
{
	hero->takeDamage(0);
}