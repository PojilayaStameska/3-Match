#pragma once
#include "IEnemyFactory.hpp"

class ArahnidNestEnemyFactory:IEnemyFactory
{
public:
	ArahnidNestEnemyFactory();
	virtual Enemy* createEnemy(int level) override;
	virtual std::string factoryName() override;
};