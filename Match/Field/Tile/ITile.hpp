#pragma once

#include "SFML/Graphics/Color.hpp"

#include "../TileList.hpp"
#include "../../Application/Hero.hpp"


class ITile
{
public:

	TileList Texture() { return texture; };
	sf::Color MainColor() { if (isDead) return sf::Color(0, 0, 0); return mainColor; };
	sf::Color BorderColor() { return borderColor; };
	bool IsDead() { return isDead; };
	virtual void activate(Hero *target) = 0;

	bool mark() { return isMarked; }
	void markTrue () { isMarked = true; }
protected:
	TileList texture;
	sf::Color mainColor, borderColor;
	bool isDead = false;
	bool isMarked = false;
	int id;
};