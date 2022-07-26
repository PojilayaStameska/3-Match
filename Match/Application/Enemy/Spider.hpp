#pragma once
#include "Enemy.hpp"

class Spider :Enemy
{
public:
	Spider(int level);
	void attack(Entity* hero) override;
};