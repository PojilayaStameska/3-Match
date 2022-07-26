#pragma once
#include "Connection.hpp"

#include <iostream>

Connection::Connection(sf::TcpSocket* socket, sf::TcpListener* listener, Hero* hero, Hero* friendHero, EntityList* EList) :
	socket(socket),
	listener(listener),
	hero(hero),
	friendHero(friendHero),
	EList(EList)
{

}


void Connection::startRecieve()
{
	sf::IpAddress ip = sf::IpAddress("92.223.34.102");// here coonection ip
	sf::Time timeout = sf::milliseconds(3000);
	if (socket->connect(ip, 2000, timeout) == sf::Socket::Status::Error)
	{
		isServer = 1;
		listener->listen(443);
		listener->accept(*socket);
	}
	else
	{
		isConnected = true;
		isServer = 0;
		sendConnect();
	}

	while (isActive)
	{
		sf::Packet recieved;
		socket->receive(recieved);
		if (true)
		{
			reaction(recieved);
		}
		if (!isConnected)
		{
			isServer = 1;
			listener->listen(443);
			listener->accept(*socket);
		}
	}
}

bool Connection::sendConnect(){ // add call
	sf::Packet toSend;
	toSend << (int)MessageEnum::Connect << hero->MaxHp() << hero->CurHp() << hero->Shield();
	//toSend << (int)Version; to update
	socket->send(toSend);
	return true;
}

bool Connection::sendDisconnect(){ // add call
	sf::Packet toSend;
	toSend << (int)MessageEnum::Disconnect;
	socket->send(toSend);
	return true;
}

bool Connection::sendMove(){
	sf::Packet toSend;
	toSend << (int)MessageEnum::ValidMove;
	for (int key = 0; key < (int)Tile::Unused; key++)
		toSend << (int)hero->TurnResult((Tile)key);
	socket->send(toSend);
	return true;
}

bool Connection::sendStatus(){ // add call
	sf::Packet toSend;
	toSend << (int)MessageEnum::Status << hero->MaxHp() << hero->CurHp() << hero->Shield();
	socket->send(toSend);
	return true;
}

bool Connection::sendTurnEnd(){
	sf::Packet toSend;
	isTurnActive = false;
	toSend << (int)MessageEnum::TurnEnd << (int)(hero->UnRealizeDmg()) << (int)(hero->ThunderSelfResult() / 2);
	toSend << (int)(hero->TurnResult(Tile::Shield) * hero->ShieldEffect() / 2);
	toSend << (int)(hero->TurnResult(Tile::Heart) * hero->HeartEffect() / 2);
	socket->send(toSend);
	return true;
}

bool Connection::sendTurnStart(){
	sf::Packet toSend;
	isTurnActive = true;
	toSend << (int)MessageEnum::TurnStart;
	socket->send(toSend);
	return true;
}

bool Connection::sendEntityList()
{
	sf::Packet toSend;
	toSend << (int)MessageEnum::EntityList;
	for (int i = 0; i < EList->list.size(); i++)
	{
		toSend << EList->list[i]->Name() << EList->list[i]->IsAlive() << EList->list[i]->MaxHp() << EList->list[i]->CurHp() << (int)EList->list[i]->CurTile();
	}
	socket->send(toSend);
	return true;
}

void Connection::reaction(sf::Packet pack){
	int type;
	std::string textValue;
	int value = 0;
	bool boolValue = false;
	pack >> type;
	switch (type)

	{
	case (int)MessageEnum::ValidMove:
		for (int key = 0; key < (int)Tile::Unused; key++)
		{
			pack >> value;
			friendHero->setTernResult((Tile)key, value);
		}
		break;
	case (int)MessageEnum::TurnStart:
		isTurnActive = true;
		break;
	case (int)MessageEnum::TurnEnd:
		pack >> value;
		friendHero->setUnrealizeDmg(value);
		pack >> value;
		hero->takeDamage(value);
		pack >> value;
		hero->setShield(hero->Shield());
		pack << value;
		hero->setCurHp(hero->CurHp() + value);
		friendHero->setIsTurnEnd(true);
		break;
	case (int)MessageEnum::EntityList:
		for (int i = 0; i < EList->list.size(); i++)
		{
			while (EList->list[i] == nullptr)
			{

			}
			pack >> textValue;
			EList->list[i]->setName(textValue);
			pack >> boolValue;
			EList->list[i]->setIsAlive(boolValue);
			pack >> value;
			EList->list[i]->setMaxHp(value);
			pack >> value;
			EList->list[i]->setCurHp(value);
			pack >> value;
			EList->list[i]->setCurTile((Tile)value);
		}
		EList->load();
		break;
	case (int)MessageEnum::Status:
		pack >> value;
		friendHero->setMaxHp(value);
		pack >> value;
		friendHero->setCurHp(value);
		pack >> value;
		friendHero->setShield(value);
		break;
	case (int)MessageEnum::Connect:
		isConnected = true;
		pack >> value;
		friendHero->setMaxHp(value);
		pack >> value;
		friendHero->setCurHp(value);
		pack >> value;
		friendHero->setShield(value);
		sendEntityList();
		sendStatus();
		break;
	case (int)MessageEnum::Disconnect:
		isConnected = false;
		break;
	default:

		break;
	}
}