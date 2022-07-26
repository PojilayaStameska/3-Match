#pragma once
#include "Field.hpp"

#include <algorithm> 
#include <utility> 
#include <iostream>

Field::Field(int width, int height, Rng* randomiser, Hero* hero, Connection* connect)
	: width(width)
	, height(height)
	, randomiser(randomiser)
	, tileFactory(randomiser)
	, hero(hero)
	, connect(connect)
{
	tiles.resize(width * height);
	srand(time(NULL));
	regenerate();
}

void Field::setTile(int x, int y, ITile* tile)
{
	tiles[x + y * width] = tile;
}

void Field::setTile(const sf::Vector2i& pos, ITile* tile)
{
	setTile(pos.x, pos.y, tile);
}

ITile* Field::getTile(int x, int y) const
{
	return tiles[x + y * width];
}

ITile* Field::getTile(const sf::Vector2i& pos) const
{
	return getTile(pos.x, pos.y);
}

void Field::changeTile(int id)
{
	ITile* tmp = tiles[id];
	tiles[id] = tileFactory.CreateTile();
	free(tmp);
}

bool Field::horizontalCheck(int id)
{
	int sum = 0;
	for (int i = id % width; i < width; i++)
		if (tiles[id]->Texture() == tiles[(id / width) * width + i]->Texture()) sum++;
		else break;
	for (int i = id % width; i >= 0; i--)
		if (tiles[id]->Texture() == tiles[(id / width) * width + i]->Texture()) sum++;
		else break;
	if (sum - 1 >= 3) return true;
	return false;
}

bool Field::verticalCheck(int id)
{
	int sum = 0;
	for (int i = id / width; i < height; i++)
		if (tiles[id]->Texture() == tiles[id % width + i * width]->Texture()) sum++;
		else break;
	for (int i = id / width; i >= 0; i--)
		if (tiles[id]->Texture() == tiles[id % width + i * width]->Texture()) sum++;
		else break;
	if (sum - 1 >= 3) return true;
	return false;
}

void Field::regenerate()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i] = tileFactory.CreateTile();
	}
	for (int i = 0; i < tiles.size(); i++)
	{
		while (horizontalCheck(i) || verticalCheck(i))
			changeTile(i);
	}
}

void Field::swapTiles(int idFirst, int idSecond)
{
	ITile* tmp = this->tiles[idFirst];
	this->tiles[idFirst] = this->tiles[idSecond];
	this->tiles[idSecond] = tmp;
}

bool Field::isNeighbors(int idFirst, int idSecond)
{
	bool isHorizontalNeighbors, isVerticalNeighbors;

	isHorizontalNeighbors = (idSecond + 1 == idFirst && ((idSecond % width) + 1 == (idFirst % width)))
		|| (idSecond - 1 == idFirst && ((idSecond % width) - 1 == (idFirst % width)));

	isVerticalNeighbors = idSecond + width == idFirst || idSecond - width == idFirst;

	if (isVerticalNeighbors || isHorizontalNeighbors) return true;
	return false;
}

void Field::dropCicle()
{
	for (int x = 0; x < width; x++)
	{
		int holeStartId = -1;
		int holeSize = 0;
		//find hole in this column
		for (int y = 0; y < height; y++)
		{
			if (tiles[x + y * width]->IsDead())
			{
				if (holeStartId == -1)
					holeStartId = y;
				holeSize++;
			}
		}
		for (int y = holeStartId - 1; y >= 0; y--)
		{
			swapTiles(x + y * width, x + (y + holeSize) * width);
			makeMoveIfValid(x + (y + holeSize) * width, x + (y + holeSize) * width);
		}
		for (int y = 0; y < holeSize; y++)
		{
			changeTile(x + y * width);
			makeMoveIfValid(x + y * width, x + y * width);
		}
	}
}

void Field::activateMarks()
{
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			if (tiles[x + y * width]->mark()) tiles[x + y * width]->activate(hero);
}

void Field::validMoveEffect(int idFirst, int idSecond)
{
	int idArray[2]{idFirst,idSecond};

	for (const auto& id : idArray)
	{
		if (verticalCheck(id))
		{
			for (int i = id / width; i < height; i++)
				if (tiles[id]->Texture() == tiles[id % width + i * width]->Texture()) tiles[id % width + i * width]->markTrue();
				else break;
			for (int i = id / width; i >= 0; i--)
				if (tiles[id]->Texture() == tiles[id % width + i * width]->Texture()) tiles[id % width + i * width]->markTrue();
				else break;
		}

		if (horizontalCheck(id))
		{
			for (int i = id % width; i < width; i++)
				if (tiles[id]->Texture() == tiles[(id / width) * width + i]->Texture()) tiles[(id / width) * width + i]->markTrue();
				else break;
			for (int i = id % width; i >= 0; i--)
				if (tiles[id]->Texture() == tiles[(id / width) * width + i]->Texture()) tiles[(id / width) * width + i]->markTrue();
				else break;
		}
	}
	activateMarks();
	dropCicle();
}

bool Field::makeMoveIfValid(int idFirst, int idSecond)
{

	swapTiles(idFirst, idSecond);

	if (verticalCheck(idFirst) || verticalCheck(idSecond) || horizontalCheck(idFirst) || horizontalCheck(idSecond))
	{
		validMoveEffect(idFirst, idSecond);
		return true;
	}

	swapTiles(idFirst, idSecond);
	return false;
}

bool Field::changeFocusTile(int id)
{
	if (idFocused != -1)
	{
		if (isNeighbors(id, idFocused) && ableToMove)
		{	
			if (!makeMoveIfValid(id, idFocused))
			{
				idFocused = -1;
				if (isTurnActive == true) // punishment for player mistake
					endTurn();
				return false;
			}
			if (!isTurnActive)startTurn();
			moveThisTurn++;
			hero->setTime(hero->Time() + timePerMove / sqrt(moveThisTurn));
			idFocused = -1;
			return true;
		}

		idFocused = id;
		return false;
	}

	this->idFocused = id;
	return false;
}

void Field::endTurn()
{
	isTurnActive = false;
	ableToMove = false;
	moveThisTurn = 0;
	hero->endTurn();
	connect->sendTurnEnd();
}

void Field::startTurn()
{
	isTurnActive = true;
	ableToMove = true;
	if (!connect->IsTurnActive())
	{
		connect->sendTurnStart();
	}
	connect->setTurnActive(false);
}

void Field::setTurnStatus(bool status) 
{
	if (status == true) startTurn();
	if (status == false) endTurn();
}

bool Field::turnStatus()
{ 
	return isTurnActive; 
}