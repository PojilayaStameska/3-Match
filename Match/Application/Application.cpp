#pragma once
#include "Application.hpp"
#include "WindowsHelper.hpp"



#include <SFML/Window/Event.hpp>

#include <iostream>


namespace 
{
	const sf::Vector2i FieldSize(12, 5);
	const sf::Vector2i tileSize(80, 80);
}

void establishConnection(Connection* connection);

Application::Application()
	: window(sf::VideoMode(1920, 1020), "Lab2OOP", sf::Style::Close),
	hero(),
	myConnection(&client, &server, &hero, &friendHero, &EList),
	field(FieldSize.x, FieldSize.y, new Rng(), &hero, &myConnection),
	EList(EntitySet)
{
	registerEnemyFactories();
	if (!tileSet.loadFromFile("images/NewSet.png"))
	{
		std::cout << "Texture load error";
	}
	if (!fieldBG.loadFromFile("images/field.png"))
	{
		std::cout << "Texture load error";
	}
	if (!EntitySet.loadFromFile("images/EntitySet.png"))
	{
		std::cout << "Texture load error";
	}

	if (!font.loadFromFile("font/OpenSans-Regular.ttf"))
	{
		std::cout << "font load error";
	}

	EList.Regenerate(enemyFactories[currentEnemyFactory]);
	EList.load();

	bg = enemyFactories[currentEnemyFactory]->Texture();

	centerWindow(window.getSystemHandle());
	window.setFramerateLimit(75);

	fieldDraw = std::make_unique<FieldDraw>(tileSet, tileSize);
	fieldDraw->load(field);
	mainConnectionThread = std::thread(establishConnection, &myConnection);
}

void establishConnection(Connection* connection)
{
	connection->startRecieve();
}

void Application::run()
{
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Time dt = clock.restart();

		processInput(dt);
		update(dt);
		render();
	}

	myConnection.sendDisconnect();
	myConnection.close();
	mainConnectionThread.detach();
}

void Application::processInput(sf::Time dt)
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2i tileNum(((event.mouseButton.x / tileSize.x) - 6), (event.mouseButton.y / tileSize.y - 8));

				if ((tileNum.x >= 0 && tileNum.y >= 0) && (tileNum.x < FieldSize.x && tileNum.y < FieldSize.y))
					if (field.changeFocusTile(tileNum.x + tileNum.y * FieldSize.x))
						myConnection.sendMove();
			}
		}
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				window.close();
				break;
			}
		}
	}
}

void Application::realizeEndTurnEffects()
{
	EList.RealizeDamage(hero.UnRealizeDmg() + friendHero.UnRealizeDmg());
	EList.Attack(&hero);
	hero.clearTurnResult();
	friendHero.clearTurnResult();
	EList.load();
	myConnection.sendStatus();
	realized = true;
}

void Application::update(sf::Time dt)
{
	fieldDraw->load(field);
	
	if (myConnection.IsTurnActive())
		field.startTurn();

	if (hero.IsTurnEnd() && (!myConnection.IsConnected() || friendHero.IsTurnEnd()) && !realized)
		realizeEndTurnEffects();

	if (field.turnStatus())
	{
		if (!hero.setTime(hero.Time() - dt.asSeconds()))
		{
			field.setTurnStatus(false);
		}
	}
	else
	{
		if ((friendHero.IsTurnEnd() || !myConnection.IsConnected()) && hero.setCooldown(hero.Cooldown() - dt.asSeconds()))
		{
			field.setAbleToMove(true);
			friendHero.setIsTurnEnd(false);
			hero.setIsTurnEnd(false);
			realized = false;
		}
	}
}

void Application::renderLocationBg(sf::Vector2f start, sf::Vector2f end, sf::Texture subject)
{
	std::vector<sf::Vertex> vertes;
	vertes.clear();
	vertes.resize(4);

	vertes[0].position = sf::Vector2f(start.x, start.y);
	vertes[1].position = sf::Vector2f(end.x, start.y); 
	vertes[2].position = sf::Vector2f(end.x, end.y);
	vertes[3].position = sf::Vector2f(start.x, end.y);

	vertes[0].texCoords = sf::Vector2f(0, 0);
	vertes[1].texCoords = sf::Vector2f(subject.getSize().x, 0);
	vertes[2].texCoords = sf::Vector2f(subject.getSize().x, subject.getSize().y);
	vertes[3].texCoords = sf::Vector2f(0, subject.getSize().y);
	sf::RenderStates states;
	states.texture = &subject;
	window.draw(&vertes[0], 4, sf::Quads, states);
}

void Application::renderHudElements()
{
	std::vector<sf::Vertex> vertes;
	vertes.clear();
	vertes.resize(8);

	vertes[0].position = sf::Vector2f(0, 520);
	vertes[1].position = sf::Vector2f(1920, 520);
	vertes[2].position = sf::Vector2f(1920, 550);
	vertes[3].position = sf::Vector2f(0, 550);

	int length = 0;
	if (hero.Time() != 10)
		length = 1920 / 2 - (hero.Time() / 20) * 1920;
	else
		length = 1920 / 2 - (hero.Cooldown() / 4) * 1920;

	vertes[4].position = sf::Vector2f(1920 - length, 550);
	vertes[5].position = sf::Vector2f(1920 - length, 520);
	vertes[6].position = sf::Vector2f(length, 520);
	vertes[7].position = sf::Vector2f(length, 550);

	for (int i = 0; i < 4; i++)
		vertes[i].color = sf::Color(89, 0, 89);
	for (int i = 4; i < vertes.size(); i++)
		vertes[i].color = sf::Color(139, 0, 139);
	sf::RenderStates states;
	window.draw(&vertes[0], vertes.size(), sf::Quads, states);
}

void Application::heroRender(Hero* hero, bool isMain)
{
	float shift = 0;
	if (!isMain) shift = 960;
	for (int key = 0; key < (int)Tile::Unused; key++)
	{
		sf::Text tmp(std::to_string(hero->TurnResult((Tile)key)), font, 30);
		tmp.setPosition(key * 100 + shift, 555);
		window.draw(tmp);
	}

	std::vector<sf::Vertex> vertes;
	vertes.clear();
	vertes.resize(8);

	vertes[0].position = sf::Vector2f(550 + shift, 560);
	vertes[1].position = sf::Vector2f(750 + shift, 560);
	vertes[2].position = sf::Vector2f(750 + shift, 590);
	vertes[3].position = sf::Vector2f(550 + shift, 590);

	int length = 200 / 2 - ((float)hero->CurHp() / (float)hero->MaxHp() / 2) * 200;

	vertes[4].position = sf::Vector2f(750 - length + shift, 590);
	vertes[5].position = sf::Vector2f(750 - length + shift, 560);
	vertes[6].position = sf::Vector2f(550 + length + shift, 560);
	vertes[7].position = sf::Vector2f(550 + length + shift, 590);

	for (int i = 0; i < 4; i++)
		vertes[i].color = sf::Color(134, 0, 0);
	for (int i = 4; i < vertes.size(); i++)
		vertes[i].color = sf::Color(255, 20, 63);
	sf::RenderStates states;
	window.draw(&vertes[0], vertes.size(), sf::Quads, states);
}

void Application::render()
{ 
	window.clear(sf::Color(44,44,44));
	renderLocationBg(sf::Vector2f(0,0),sf::Vector2f(1920,520),bg);
	window.draw(EList);
	renderHudElements();
	renderLocationBg(sf::Vector2f(0, 550), sf::Vector2f(window.getSize().x, window.getSize().y), fieldBG);
	heroRender(&hero, true);
	heroRender(&friendHero, false);
	window.draw(*fieldDraw);
	window.display();
}

void Application::selectNextEnemyFactory()
{
	currentEnemyFactory = (currentEnemyFactory + 1) % enemyFactories.size();
	//regenerate call
}

void Application::selectPreviousEnemyFactory()
{
	currentEnemyFactory = (currentEnemyFactory + enemyFactories.size() - 1) % enemyFactories.size();
	//regenerate call
}

void Application::registerEnemyFactories()
{
	//enemyFactories.emplace_back((IEnemyFactory*)new ArahnidNestEnemyFactory());
	//enemyFactories.emplace_back((IEnemyFactory*)new SlimeRanchEnemyFactory());
	//enemyFactories.emplace_back((IEnemyFactory*)new VampireMansionEnemyFactory());
	//enemyFactories.emplace_back((IEnemyFactory*)new CemeteryEnemyFactory());
}