#pragma once
#include "Enemy.hpp"
class Skeleton :Enemy
{
public:
	Skeleton(int level);
	void attack(Entity* hero) override;
};