#include "CellOccupier.h"

using namespace std;

// Creates an empty occupier
CellOccupier* CellOccupier::create_empty() {
	CellOccupier* res = new CellOccupier();
	res->_empty = true;
	return res;
}
// Defines the unique occupier that signifies a cell has no occupier
const unique_ptr<CellOccupier> CellOccupier::EMPTY(create_empty());

// Creates a new CellOccupier
// name = The name of the occupier
// desc = The description of the occupier
// impassable = true if and only if the player cannot enter a cell that posesses this occupier
CellOccupier::CellOccupier(string name,string desc,bool impassable) {
	_empty = false;
	_name = name;
	_desc = desc;
	_impassable = impassable;
}
// Creates a new passable CellOccupier
// name = The name of the occupier
// desc = The description of the occupier
CellOccupier::CellOccupier(string name,string desc) : CellOccupier(name,desc,false) {
}
// Creates a new passable CellOccupier with no name or description
CellOccupier::CellOccupier() : CellOccupier("","") {
}
// Returns true if the player is not permitted to enter a cell with this occupier
bool CellOccupier::is_impassable() const {
	return _impassable;
}
// Gets the name of this occupier
string CellOccupier::name() const {
	return _name;
}
// Gets the description of this occupier
string CellOccupier::desc() const {
	return _desc;
}
// Determines if two occupiers are the same
// other = The occupier to compare to
bool CellOccupier::operator ==(const CellOccupier& other) const {
	return (_empty && other._empty) || (_name == other._name && _desc == other._desc && _impassable == other._impassable);
}
// Determines if two occupiers are different
// other = The occupier to compare to
bool CellOccupier::operator !=(const CellOccupier& other) const {
	return !(*this == other);
}
// Outputs details about this occupier
// stream = The output stream to write to
// occupier = The occupier to output the details of
ostream& operator <<(ostream& stream,const CellOccupier& occupier) {
	if (occupier._empty) {
		stream << "EMPTY";
	} else {
		stream << occupier._name << ": " << occupier._desc;
		if (occupier._impassable) {
			stream << " (IMPASSABLE)";
		}
	}
	return stream;
}