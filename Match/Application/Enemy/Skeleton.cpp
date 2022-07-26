#include "Skeleton.hpp"


Skeleton::Skeleton(int level)
{
	this->maxHp = level * 100;
	this->currentHp = maxHp;
	isAlive = false;
	curTile = Tile::SkeletonBottomSecondFrame;
	//frameNumber = 0.0f;
}

void Skeleton::attack(Entity* hero)
{
	hero->takeDamage(1);
}