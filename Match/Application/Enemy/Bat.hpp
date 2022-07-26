#pragma once
#include "Enemy.hpp"

class Bat :Enemy
{
public:
	Bat(int level);
	void attack(Entity* hero) override;
};