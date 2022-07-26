#include "VampireMansionEnemyFactory.hpp"
#include "../../Application/Enemy/Ghost.hpp"
#include "../../Application/Enemy/Spider.hpp"
#include "../../Application/Enemy/Bat.hpp"

VampireMansionEnemyFactory::VampireMansionEnemyFactory()
{
	randomiser = Rng();
	if (!bg.loadFromFile("images/vampire-mansion-bg.png"))
	{
		std::cout << "Texture load error";
	}
	this->randomiser = randomiser;
}

Enemy* VampireMansionEnemyFactory::createEnemy(int level)
{
	int rngNumber = randomiser.getInt(100);

	if (rngNumber < 5)	return (Enemy*)new Ghost(level);
	if (rngNumber < 15) return (Enemy*)new Spider(level);
	return (Enemy*)new Bat(level);
}


std::string VampireMansionEnemyFactory::factoryName()
{
	return "Vampire mansion";
}