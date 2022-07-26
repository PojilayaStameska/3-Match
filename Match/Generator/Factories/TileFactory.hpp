#pragma once
#include "../../Field/Tile/CloverTile.hpp"
#include "../../Field/Tile/HeartTile.hpp"
#include "../../Field/Tile/ThunderTile.hpp"
#include "../../Field/Tile/FireTile.hpp"
#include "../../Field/Tile/ShieldTile.hpp"

#include "../../Utility/Rng.hpp"



class TileFactory
{
public:
	TileFactory(Rng* randomiser);

	ITile* CreateTile();

	int Weight(int id);
	void setWeight(int setValue, int id);


private:
	int id = 0;
	Rng* randomiser;
	int weight[5];
};