#pragma once
#include "Enemy.hpp"

class Slime:Enemy
{
public:
	Slime(int level);
	void attack(Entity* hero) override;
};