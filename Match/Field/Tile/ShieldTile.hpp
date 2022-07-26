#pragma once
#include "ITile.hpp"

class ShieldTile :ITile
{
public:
	ShieldTile(int id);
	virtual void activate(Hero* target) override;
	int id;
};