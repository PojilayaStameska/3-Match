#pragma once

#include "Tile/ITile.hpp"
#include "../Utility/Rng.hpp"
#include "../Connection.hpp"
#include "../Generator/Factories/TileFactory.hpp"

#include <SFML/System/Vector2.hpp>

#include <vector>

class Field
{
public:
	Field(int width, int height, Rng* randomiser, Hero* hero, Connection* connect);


	void setTile(int x, int y, ITile* tile);
	void setTile(const sf::Vector2i& pos, ITile* tile);

	ITile* getTile(int x, int y) const;
	ITile* getTile(const sf::Vector2i& pos) const;
	

	void changeTile(int id);
	bool horizontalCheck(int id);
	bool verticalCheck(int id);
	bool changeFocusTile(int id);
	void regenerate();

	void setTurnStatus(bool status);
	bool turnStatus();
	void endTurn();
	void startTurn();

	void setAbleToMove(bool setValue) { ableToMove = setValue; };
	bool AbleToMove() { return ableToMove; }

public:
	const int width, height;
	std::vector<ITile*> tiles;
	int idFocused = -1;
private:

	void swapTiles(int idFirst, int idSecond);
	bool isNeighbors(int idFirst, int idSecond);
	void dropCicle();
	void activateMarks();

	bool makeMoveIfValid(int idFirst, int idSecond);
	void validMoveEffect(int idFirst, int idSecond);

	bool isTurnActive = false, ableToMove = true;
	int moveThisTurn = 0, timePerMove = 2;
	Rng* randomiser;
	Hero* hero;
	TileFactory tileFactory;
	Connection* connect;
};
