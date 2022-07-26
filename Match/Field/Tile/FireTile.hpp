#pragma once
#include "ITile.hpp"

class FireTile :ITile
{
public:
	FireTile(int id);
	virtual void activate(Hero* target) override;
	int id;
};