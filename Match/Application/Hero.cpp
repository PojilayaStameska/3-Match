#pragma once
#include "Hero.hpp"

#include <SFML/Network.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>
#include <math.h>

Hero::Hero()
{
	this->isAlive = true;
	this->points = 0;
	this->maxHp = 100;
	this->currentHp = maxHp;
	this->wallet = 0;
	this->shield = 0;
	this->timeToMove = 10;
	clearTurnResult();
	isTurnEnd = false;
	rng = Rng();
}

void Hero::clearTurnResult()
{
	for (int key = 0; key < (int)Tile::Unused; key++)
		turnResult[(Tile)key] = 0;
	thunderSelfResult = 0;
	thunderEnemyResult = 0;
}

bool Hero::getAliveState()
{
	return isAlive;
}

void Hero::die()
{
	points++;
}

void Hero::setPoints(int points)
{
	this->points = points;
}

int Hero::Points()
{
	return points;
}

float Hero::Wallet()
{
	return wallet;
}

void Hero::setWallet(float setValue)
{
	wallet = setValue;
}

int Hero::Shield()
{
	return shield;
}

void Hero::setShield(int setValue)
{
	shield = setValue;
}

void Hero::attack(Entity* monster)
{
	monster->takeDamage(10);
}

bool Hero::setTime(float setValue) {
	if (setValue < 0) {
		timeToMove = 10;
		turnCooldown = 2;
		return false; 
	}
	if (setValue > 10)
	{
		timeToMove = 10;
		return true;
	}
	timeToMove = setValue; return true; 
}

void Hero::endTurn()
{
	float cloverEff = turnResult[Tile::Clover] * cloverEffect + 1;
	for (int i = 0; i < turnResult[Tile::Thunder]; i++)
	{
		if (rng.getFloat(0, 1) < pow(thunderSelfCastChange,cloverEff))
		{
			thunderSelfResult += thunderDamage;
		}else { thunderEnemyResult += thunderDamage; }
	}
	unRealizeDmg = 0;
	unRealizeDmg += fireDamage * turnResult[Tile::Fire];
	unRealizeDmg += thunderEnemyResult;
	this->setCurHp(currentHp + heartEffect * turnResult[Tile::Heart]);
	this->setShield(shield + shieldEffect * turnResult[Tile::Shield]);
	this->takeDamage(thunderSelfResult / 2);
	this->setTime(-1);
	isTurnEnd = true;
}
