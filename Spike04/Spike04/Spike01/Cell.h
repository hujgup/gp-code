#pragma once

#include <iostream>
#include "CellOccupier.h"

class Cell {
private:
	CellOccupier* _occupier;
	unsigned int _x;
	unsigned int _y;
public:
	Cell(unsigned int x,unsigned int y,CellOccupier& occupier);
	Cell(unsigned int x,unsigned int y);
	Cell();
	bool has_occupier() const;
	CellOccupier& occupier() const;
	unsigned int x() const;
	unsigned int y() const;
	void set_occupier(CellOccupier& occupier);
	bool operator ==(const Cell& other) const;
	bool operator !=(const Cell& other) const;
	friend std::ostream& operator <<(std::ostream& stream,const Cell& cell);
};