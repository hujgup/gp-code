#pragma once

#include <vector>
#include <iostream>
#include "Cell.h"
#include "CellOccupier.h"

class GridIterator;

class Grid {
	friend class GridIterator;
private:
	unsigned int _width;
	unsigned int _height;
	std::vector<std::vector<Cell*>*> _grid;
public:
	typedef GridIterator Iterator;
	Grid(unsigned int width,unsigned int height);
	Grid();
	~Grid();
	Cell& cell_at(unsigned int x,unsigned int y) const;
	unsigned int width() const;
	unsigned int height() const;
	GridIterator begin();
	GridIterator end();
	GridIterator rbegin();
	GridIterator rend();
};

class GridIterator {
public:
	friend class Grid;
private:
	enum IteratorState {
		BEFORE,
		CONTENT,
		AFTER
	};
	Grid& _grid;
	IteratorState _state;
	unsigned int _x;
	unsigned int _y;
public:
	GridIterator(Grid& grid);
	/*
	const Cell& above() const;
	const Cell& below() const;
	const Cell& left() const;
	const Cell& right() const;
	*/
	Cell& operator *() const;
	Cell* operator ->() const;
	bool operator ==(const GridIterator& other) const;
	bool operator !=(const GridIterator& other) const;
	GridIterator& operator ++();
	GridIterator operator ++(int);
	GridIterator& operator --();
	GridIterator operator --(int);
	friend std::ostream& operator <<(std::ostream& stream,const GridIterator& iterator);
};

