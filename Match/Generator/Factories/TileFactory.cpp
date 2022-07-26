#pragma once
#include "TileFactory.hpp"



TileFactory::TileFactory(Rng* randomiser)
{
	this->randomiser = randomiser;
	for (int i = 0; i < sizeof(weight) / sizeof(int); i++)
	{
		weight[i] = 20;
	}
}

ITile* TileFactory::CreateTile()
{
	int weightSum = 0;
	for (int i = 0; i < sizeof(weight) / sizeof(int); i++)
	{
		weightSum += weight[i];
	}
	int rand = randomiser->getInt(weightSum);
	weightSum = 0;
	if (rand < weight[0]) return (ITile*) new ShieldTile(id++);
	if (rand < weight[0] + weight[1]) return (ITile*) new ThunderTile(id++);
	if (rand < weight[0] + weight[1] + weight[2]) return (ITile*) new CloverTile(id++);
	if (rand < weight[0] + weight[1] + weight[2] + weight[3]) return (ITile*) new FireTile(id++);
	return (ITile*) new HeartTile(id++);
}