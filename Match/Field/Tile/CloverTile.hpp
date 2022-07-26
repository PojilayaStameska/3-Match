#pragma once
#include "ITile.hpp"

class CloverTile :ITile
{
public:
	CloverTile(int id);
	virtual void activate(Hero *target) override;
	int id;
};