#include "Connection.h"

Connection::Connection(const Connection& copyMe) : _origin(copyMe._origin), _destination(copyMe._destination), _bidirectional(copyMe._bidirectional) {
}
Connection::Connection(Room origin,Room destination,bool bidirectional) : _origin(origin), _destination(destination), _bidirectional(bidirectional) {
}
Connection::~Connection() {
}
bool Connection::is_bidirectional() const {
	return _bidirectional;
}
const Room& Connection::origin() const {
	return _origin;
}
const Room& Connection::destination() const {
	return _destination;
}
bool Connection::operator ==(const Connection& other)  const {
	return _origin == other._origin && _destination == other._destination;
}
bool Connection::operator !=(const Connection& other) const {
	return !(*this == other);
}
Connection& Connection::operator =(const Connection& copyMe) {
	_origin = copyMe._origin;
	_destination = copyMe._destination;
	_bidirectional = copyMe._bidirectional;
	return *this;
}