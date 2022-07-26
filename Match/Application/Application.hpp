#pragma once

#include "../Application/FieldDraw.hpp"]
#include "../Field/Field.hpp"
#include "Enemy/Enemy.hpp"
#include "EntityList.hpp"
#include "../Generator/Factories/IEnemyFactory.hpp"
#include "../Generator/Factories/TileFactory.hpp"
#include "../Connection.hpp"
#include "../Generator/Factories/ArahnidNestEnemyFactory.hpp"
#include "../Generator/Factories/SlimeRanchEnemyFactory.hpp"
#include "../Generator/Factories/VampireMansionEnemyFactory.hpp"
#include "../Generator/Factories/ÑemeteryEnemyFactory.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Network.hpp>

#include <thread>
#include <memory> // unique_ptr

class Application
{
public:
	Application();
	void run();

private:
	void processInput(sf::Time dt);
	void update(sf::Time dt);
	void render();

private:

	void renderLocationBg(sf::Vector2f start, sf::Vector2f end, sf::Texture subject);
	void renderHudElements();
	void selectNextEnemyFactory();
	void selectPreviousEnemyFactory();
	void registerEnemyFactories();
	void heroRender(Hero* hero, bool isMain);

	void realizeEndTurnEffects();

	sf::RenderWindow window;
	sf::Texture tileSet;
	sf::Texture EntitySet;
	sf::Texture bg;
	sf::Texture fieldBG;
	sf::Font font;
	sf::TcpSocket client;
	sf::TcpListener server;

	Field field;
	Hero hero, friendHero;
	EntityList EList;
	Connection myConnection;

	std::thread mainConnectionThread;
	std::unique_ptr<FieldDraw> fieldDraw;

	std::vector<IEnemyFactory*> enemyFactories;
	bool checked = false, realized = false;
	int currentEnemyFactory = 3;
};
