#include "Spider.hpp"


Spider::Spider(int level)
{
	this->maxHp = level * 100;
	this->currentHp = maxHp;
	isAlive = true;
	curTile = Tile::SpiderBottomSecondFrame;
	//frameNumber = 0.0f;
}


void Spider::attack(Entity* hero)
{
	hero->takeDamage(1);
}