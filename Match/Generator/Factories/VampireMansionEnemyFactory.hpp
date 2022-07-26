#pragma once
#include "IEnemyFactory.hpp"

class VampireMansionEnemyFactory :IEnemyFactory
{
public:
	VampireMansionEnemyFactory();
	virtual Enemy* createEnemy(int level) override;
	virtual std::string factoryName() override;
};