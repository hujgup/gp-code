#include "Cell.h"

using namespace std;

// Creates a new Cell at the given location with the given occupier
// x = This cell's x position
// y = This cell's y position
// occupier = The CellOccupier occupying this cell
Cell::Cell(unsigned int x,unsigned int y,CellOccupier& occupier) {
	_x = x;
	_y = y;
	_occupier = &occupier;
}
// Creates a new Cell at the given location
// x = This cell's x position
// y = This cell's y position
Cell::Cell(unsigned int x,unsigned int y) : Cell(x,y,*CellOccupier::EMPTY) {
}
// Creates a new Cell at the origin point
Cell::Cell() : Cell(0,0) {
}
// Returns true if this cell's occupier is anything except the EMPTY occupier
bool Cell::has_occupier() const {
	return *_occupier != *CellOccupier::EMPTY;
}
// Gets a reference to this cell's occupier
CellOccupier& Cell::occupier() const {
	return *_occupier;
}
// Gets this cell's x position
unsigned int Cell::x() const {
	return _x;
}
// Gets this cell's y position
unsigned int Cell::y() const {
	return _y;
}
// Overrides this cell's occupier with a new value
// occupier = The occupeir to place in this cell
void Cell::set_occupier(CellOccupier& occupier) {
	_occupier = &occupier;
}
// Determines if two cells are the same
// other = The other cell to compare to
bool Cell::operator ==(const Cell& other) const {
	return _x == other._x && _y == other._y;
}
// Determines of two cells are different
// other = The other cell to compare to
bool Cell::operator !=(const Cell& other) const {
	return !(*this == other);
}
// Outputs this cell's details to a stream
// stream == The stream to write to
// cell = The cell to output the details of
ostream& operator <<(ostream& stream,const Cell& cell) {
	stream << cell._x << ", " << cell._y << ", " << cell._occupier;
	return stream;
}