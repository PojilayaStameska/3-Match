#pragma once
#include "../../Application/Enemy/Enemy.hpp"
#include "../../Utility/Rng.hpp"
#include <SFML/Graphics/Texture.hpp>

class IEnemyFactory
{
public:
	virtual Enemy* createEnemy(int level) = 0;
	virtual std::string factoryName() = 0;
	virtual sf::Texture Texture() { return bg; };

protected:
	sf::Texture bg;
	Rng randomiser;
};