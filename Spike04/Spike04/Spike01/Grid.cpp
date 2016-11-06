#include "Grid.h"
#include <stdexcept>

using namespace std;

// Creates a new Grid of the specified size
// width = The width of the grid
// height = The height of the grid
Grid::Grid(unsigned int width,unsigned int height) {
	// Grid is row then column
	if (width == 0 || height == 0) {
		throw logic_error("Width and height must be non-zero.");
	}
	_width = width;
	_height = height;
	unsigned int x;
	for (unsigned int y = 0; y < height; ++y) {
		vector<Cell*>* row = new vector<Cell*>();
		for (x = 0; x < width; ++x) {
			row->push_back(new Cell(x,y));
		}
		_grid.push_back(row);
	}
}
// Creates a new 1x1 Grid
Grid::Grid() : Grid(1,1) {
}
// Destroys this Grid
Grid::~Grid() {
	for (unsigned int y = 0; y < _height; ++y) {
		delete _grid[y];
	}
}
// Gets the cell at the given position
// x = The x position of the cell to get
// y = The y position of the cell to get
Cell& Grid::cell_at(unsigned int x,unsigned int y) const {
	if (x >= _width || y >= _height) {
		throw logic_error("Specified position outside the bounds of this grid.");
	}
	return *(_grid.at(y)->at(x));
}
// Gets this grid's width
unsigned int Grid::width() const {
	return _width;
}
// Gets this grid's height
unsigned int Grid::height() const {
	return _height;
}
// Gets a GridIterator positioned at the top-left of the grid
GridIterator Grid::begin() {
	return GridIterator(*this);
}
// Gets a GridIterator positioned after the grid
GridIterator Grid::end() {
	GridIterator res(*this);
	res._state = GridIterator::IteratorState::AFTER;
	return res;
}
// Gets a GridIterator positioned at the bottom-right of the grid
GridIterator Grid::rbegin() {
	return --end();
}
// Gets a GridIterator positioned before the grid
GridIterator Grid::rend() {
	return --begin();
}

// Creates a new GridIterator over the specified grid
// grid = The grid to iterate over
GridIterator::GridIterator(Grid& grid) : _grid(grid) {
	_x = 0;
	_y = 0;
	_state = IteratorState::CONTENT;
}
// Gets the cell at the current iterator position
Cell& GridIterator::operator *() const {
	if (_state != IteratorState::CONTENT) {
		throw logic_error("Cannot dereference iterator when iterator is outside the bounds of its content.");
	}
	return _grid.cell_at(_x,_y);
}
// Gets the cell at the current iterator position
Cell* GridIterator::operator ->() const {
	return _state == IteratorState::CONTENT ? _grid._grid.at(_y)->at(_x) : NULL;
}
// Determines if two GridIterators are at the same location
// other = The iterator to compare to
bool GridIterator::operator ==(const GridIterator& other) const {
	bool res = _state == other._state;
	if (res && _state == IteratorState::CONTENT) {
		res = _x == other._x && _y == other._y;
	}
	return res;
}
// Determines if two GridIterators are at different locations
// other = The iterator to compare to
bool GridIterator::operator !=(const GridIterator& other) const {
	return !(*this == other);
}
// Increments the iterator and returns this instance
GridIterator& GridIterator::operator ++() {
	switch (_state) {
		case IteratorState::BEFORE:
			// Grid is guaranteed to have at least 1 cell
			_x = 0;
			_y = 0;
			break;
		case IteratorState::CONTENT:
			if (++_x >= _grid._width) {
				_x = 0;
				if (++_y >= _grid._height) {
					_state = IteratorState::AFTER;
				}
			}
			break;
			// Do nothing on state AFTER
	}
	return *this;
}
// Increments the iterator and returns an unincremented copy of this instance
GridIterator GridIterator::operator ++(int) {
	GridIterator res = *this;
	++*this;
	return res;
}
// Decrements the iterator and returns this instance
GridIterator& GridIterator::operator --() {
	switch (_state) {
		case IteratorState::AFTER:
			_x = _grid._width - 1;
			_y = _grid._height - 1;
			break;
		case IteratorState::CONTENT:
			if (_x == 0) {
				if (_y == 0) {
					_state = IteratorState::BEFORE;
				} else {
					--_y;
					_x = _grid._width - 1;
				}
			} else {
				--_x;
			}
			break;
			// Do nothing on state BEFORE
	}
	return *this;
}
// Decrements this iterator and return and undecremented copy of this instance
GridIterator GridIterator::operator --(int) {
	GridIterator res = *this;
	--*this;
	return res;
}
// Outputs the current state of this iterator
// stream = The output stream to write to
// iterator = The iterator to output the state of
ostream& operator <<(ostream& stream,const GridIterator& iterator) {
	stream << iterator._x << ", " << iterator._y << ", ";
	switch (iterator._state) {
		case GridIterator::IteratorState::BEFORE:
			stream << "BEFORE";
			break;
		case GridIterator::IteratorState::CONTENT:
			stream << "CONTENT";
			break;
		default:
			stream << "AFTER";
			break;
	}
	return stream;
}
