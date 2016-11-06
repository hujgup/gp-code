#include "Room.h"

using namespace std;

Room::Room(unsigned long id,string name,string desc) : _id(id), _name(name), _desc(desc) {
}
Room::~Room() {
}
string Room::type_name() const {
	return "Room";
}
string Room::to_string() const {
	return _name + ": " + _desc;
}
IInventory& Room::inventory() {
	return _inv;
}
unsigned char Room::type_id() const {
	return 0;
}
unsigned long Room::id() const {
	return _id;
}
const string& Room::name() const {
	return _name;
}
const string& Room::desc() const {
	return _desc;
}
bool Room::operator ==(const Room& other) const {
	return _id == other._id;
}
bool Room::operator !=(const Room& other) const {
	return !(*this == other);
}
