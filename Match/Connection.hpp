#pragma once

#include "MessageEnum.hpp"
#include "Application/Hero.hpp"
#include "Application/EntityList.hpp"
#include <SFML/Network.hpp>

#include <thread>
#include <iostream>
#include <atomic>

class Connection
{
public:
	Connection(sf::TcpSocket* socket, sf::TcpListener* listener, Hero* hero, Hero* friendHero, EntityList* EList);// add EntityList Her partyMember;
	void close() { isActive = false; listener->close();}
	void startRecieve();

	bool sendConnect();
	bool sendDisconnect();
	bool sendMove();
	bool sendStatus();
	bool sendTurnEnd();
	bool sendTurnStart();
	bool sendEntityList();

	bool IsTurnActive() { return isTurnActive; }
	void setTurnActive(bool value) { isTurnActive = value; }

	bool IsConnected() { return isConnected; }
	int IsServer() { return isServer; }

private:

	void reaction(sf::Packet);

	sf::TcpSocket* socket;
	sf::TcpListener* listener;

	std::thread connectionThread;
	Hero* hero, *friendHero;
	EntityList* EList;

	std::atomic_bool isConnected = false;
	std::atomic_bool isTurnActive = false;
	std::atomic_bool ableToMove = true;
	std::atomic_int isServer = -1;

	std::atomic_bool isActive = true;
	int messageId = 0;
};


