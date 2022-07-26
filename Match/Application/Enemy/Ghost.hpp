#pragma once
#include "Enemy.hpp"

class Ghost :Enemy
{
public:
	Ghost(int level);
	void attack(Entity* hero) override;
};