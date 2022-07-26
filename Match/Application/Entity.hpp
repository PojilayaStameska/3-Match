#pragma once

#include "../TileEnum.hpp"

#include <string>

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

class Entity 
{
	public:
	virtual void takeDamage(int damage);
	virtual void die() = 0;
	virtual void attack(Entity* hero) = 0;

	void setMaxHp(const int hp);
	int MaxHp();
	void setCurHp(const int hp);
	int CurHp();
	void setName(const std::string newName);
	std::string Name();
	void setIsAlive(bool aliveStatus);
	bool IsAlive();
	Tile CurTile() {return curTile;};
	void setCurTile(Tile value) { curTile = value; }

protected:
	/*float frameNumber;*/
	Tile curTile;
	std::string name;
	int maxHp, currentHp, damage;
	bool  isAlive;
};