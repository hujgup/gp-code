#include "RoomIterator.h"

using namespace std;

RoomIterator::RoomIterator(const vector<Room>& rooms) : _rooms(rooms) {
}
RoomIterator::~RoomIterator() {
}
string RoomIterator::type_name() const {
	return "RoomIterator";
}
void RoomIterator::begin() {
	_index = 0;
}
void RoomIterator::end() {
	_index = _rooms.size();
}
void RoomIterator::rbegin() {
	end();
	--_index;
}
void RoomIterator::rend() {
	begin();
	--_index;
}
const Room& RoomIterator::operator *() const {
	return _rooms[_index];
}
const Room* RoomIterator::operator ->() const {
	return &(_rooms[_index]);
}
bool RoomIterator::operator ==(const RoomIterator& other) const {
	return _index == other._index || (_index < 0 && other._index < 0) || (_index >= _rooms.size() && other._index >= _rooms.size());
}
bool RoomIterator::operator !=(const RoomIterator& other) const {
	return !(*this == other);
}
RoomIterator& RoomIterator::operator ++() {
	++_index;
	return *this;
}
RoomIterator RoomIterator::operator ++(int) {
	RoomIterator res = *this;
	++(*this);
	return res;
}
RoomIterator& RoomIterator::operator --() {
	--_index;
	return *this;
}
RoomIterator RoomIterator::operator --(int) {
	RoomIterator res = *this;
	--(*this);
	return res;
}