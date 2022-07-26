#include "ArahnidNestEnemyFactory.hpp"
#include "../../Application/Enemy/Spider.hpp"
#include "../../Application/Enemy/Skeleton.hpp"

ArahnidNestEnemyFactory::ArahnidNestEnemyFactory()
{
	randomiser = Rng();
	if (!bg.loadFromFile("images/Arahnid-nest-bg.png"))
	{
		std::cout << "Texture load error";
	}
	this->randomiser = randomiser;
}

Enemy* ArahnidNestEnemyFactory::createEnemy(int level)
{
	if (randomiser.getInt(100) < 20) return (Enemy*)new Skeleton(level);
	return (Enemy*)new Spider(level);
}

std::string ArahnidNestEnemyFactory::factoryName()
{
	return "Arahnid nest";
}