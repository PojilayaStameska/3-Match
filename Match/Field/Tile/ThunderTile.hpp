#pragma once
#include "ITile.hpp"

class ThunderTile :ITile
{
public:
	ThunderTile(int id);
	virtual void activate(Hero* target) override;
	int id;
};