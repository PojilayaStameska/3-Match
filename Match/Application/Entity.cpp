#pragma once
#include "Entity.hpp"
#include <iostream>

void Entity::setMaxHp(const int hp)
{
	if (hp < 0)
		this->maxHp = 1;
	else
		this->maxHp = hp;
}

int Entity::MaxHp()
{
	return maxHp;
}

void Entity::setCurHp(const int hp)
{
	if (hp > maxHp)
	{
		this->currentHp = maxHp;
		return;
	}
	if (hp <= 0)
	{
		currentHp = 0;
		die();
		return;
	}
	this->currentHp = hp;
}

int Entity::CurHp()
{
	return currentHp;
}


void Entity::setName(const std::string newName)
{
	this->name = newName;
}

std::string Entity::Name()
{
	return name;
}

void Entity::takeDamage(int damage)
{
	setCurHp(CurHp() - damage);
}


bool Entity::IsAlive()
{
	return isAlive;
}

void Entity::setIsAlive(bool aliveStatus)
{
	isAlive = aliveStatus;
}
