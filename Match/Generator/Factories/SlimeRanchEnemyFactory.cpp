#include "SlimeRanchEnemyFactory.hpp"
#include "../../Application/Enemy/Slime.hpp"
#include "../../Application/Enemy/Ghost.hpp"
#include "../../Application/Enemy/Skeleton.hpp"
#include "../../Application/Enemy/Spider.hpp"
#include "../../Application/Enemy/Bat.hpp"

SlimeRanchEnemyFactory::SlimeRanchEnemyFactory()
{
	randomiser = Rng();
	if (!bg.loadFromFile("images/slime-ranch-alt-bg.png"))
	{
		std::cout << "Texture load error";
	}
	this->randomiser = randomiser;
}

Enemy* SlimeRanchEnemyFactory::createEnemy(int level)
{
	sf::Vector2f generatedMobPosition(0.0f, 0.0f);

	int rngNumber = randomiser.getInt(100);

	if (rngNumber < 2) return (Enemy*)new Skeleton(level);
	if (rngNumber < 3) return (Enemy*)new Bat(level);
	if (rngNumber < 5) return (Enemy*)new Ghost(level);
	if (rngNumber < 10) return (Enemy*)new Spider(level);
	return (Enemy*)new Slime(level);
}


std::string SlimeRanchEnemyFactory::factoryName()
{
	return "Slime ranch";
}