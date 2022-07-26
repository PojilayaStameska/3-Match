#pragma once
#include "ITile.hpp"

class HeartTile :ITile
{
public:
	HeartTile(int id);
	virtual void activate(Hero* target) override;
	int id;
};