#pragma once
#include "IEnemyFactory.hpp"

class SlimeRanchEnemyFactory :IEnemyFactory
{
public:
	SlimeRanchEnemyFactory();
	virtual Enemy* createEnemy(int level) override;
	virtual std::string factoryName() override;
};