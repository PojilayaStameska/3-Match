#include "ÑemeteryEnemyFactory.hpp"
#include "../../Application/Enemy/Ghost.hpp"
#include "../../Application/Enemy/Skeleton.hpp"
#include "../../Application/Enemy/Bat.hpp"

CemeteryEnemyFactory::CemeteryEnemyFactory()
{
	randomiser = Rng();
	if (!bg.loadFromFile("images/cemetry-bg.png"))
	{
		std::cout << "Texture load error";
	}
	this->randomiser = randomiser;
}

Enemy* CemeteryEnemyFactory::createEnemy(int level)
{
	int rngNumber = randomiser.getInt(100);

	if (rngNumber < 10) return (Enemy*)new Bat(level);
	if (rngNumber < 55) return (Enemy*)new Skeleton(level);
	return (Enemy*)new Ghost(level);

}

std::string CemeteryEnemyFactory::factoryName()
{
	return "Cemetery";
}