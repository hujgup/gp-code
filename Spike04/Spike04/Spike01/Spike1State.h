#pragma once

#include "GameState.h"

class Spike1State : public GameState {
private:
	CellOccupier* _wall;
	CellOccupier* _objective;
	CellOccupier* _death;
	bool _allowMultipleObjectives;
	unsigned int _objectivesPresent;
public:
	Spike1State(Grid* playspace,unsigned int startX,unsigned int startY,bool allowMultipleObjectives);
	Spike1State(Grid* playspace,unsigned int startX,unsigned int startY);
	virtual ~Spike1State();
	CellOccupier& wall() const;
	CellOccupier& objective() const;
	CellOccupier& death() const;
	unsigned int objectives_present() const;
	bool has_objective() const;
	bool location_has_objective() const;
	bool location_has_death() const;
	void cell_give_wall(unsigned int x,unsigned int y);
	bool cell_give_objective(unsigned int x,unsigned int y);
	void cell_give_death(unsigned int x,unsigned int y);
};

