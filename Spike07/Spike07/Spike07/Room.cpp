#include "Room.h"

using namespace std;

Room::Room(unsigned long id,string name,string desc) : _id(id), _name(name), _desc(desc) {
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
