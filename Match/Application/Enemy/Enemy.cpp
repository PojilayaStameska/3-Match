#include "Enemy.hpp"
#include "../Hero.hpp"

#include <iostream>

void Enemy::die()
{
	isAlive = false;
	std::cout << "die";
}

