#pragma once
#include "IEnemyFactory.hpp"

class CemeteryEnemyFactory :IEnemyFactory
{
public:
	CemeteryEnemyFactory();
	virtual Enemy* createEnemy(int level) override;
	virtual std::string factoryName() override;
};