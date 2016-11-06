#pragma once

#include "Grid.h"
#include "Cell.h"
#include "CellOccupier.h"

class GameState {
private:
	Grid* _playspace;
	unsigned int _locationX;
	unsigned int _locationY;
public:
	GameState(Grid* playspace,unsigned int startX,unsigned int startY);
	virtual ~GameState();
	Grid& playspace() const;
	Cell& player_location() const;
	void set_player_location(unsigned int x,unsigned int y);
	void set_player_location(const Cell& location);
};


