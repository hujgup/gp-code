#include "World.h"
#include <stdexcept>
#include <iostream>

using namespace std;

World::World(const World& copyMe) {
	for (vector<Room>::const_iterator i = copyMe._rooms.begin(); i != copyMe._rooms.end(); ++i) {
		_rooms.push_back(Room(*i));
	}
	for (vector<Connection>::const_iterator i = copyMe._connections.begin(); i != copyMe._connections.end(); ++i) {
		_connections.push_back(Connection(*i));
	}
}
World::World() {
}
RoomIterator World::cbegin() const {
	RoomIterator res(_rooms);
	res.begin();
	return res;
}
RoomIterator World::cend() const {
	RoomIterator res(_rooms);
	res.end();
	return res;
}
RoomIterator World::crbegin() const {
	RoomIterator res(_rooms);
	res.rbegin();
	return res;
}
RoomIterator World::crend() const {
	RoomIterator res(_rooms);
	res.rend();
	return res;
}
const Room& World::room(unsigned long id) const {
	for (vector<Room>::const_iterator i = _rooms.begin(); i != _rooms.end(); ++i) {
		if (i->id() == id) {
			return *i;
		}
	}
	throw runtime_error("No Room with that I.D. exists.");
}
bool World::has_connection(const Room& origin,const Room& destination) const {
	bool res = false;
	for (vector<Connection>::const_iterator i = _connections.begin(); i != _connections.end(); ++i) {
		//cout << i->origin().id() << " " << i->destination().id() << endl;
		if ((i->origin() == origin && i->destination() == destination) || (i->is_bidirectional() && i->origin() == destination && i->destination() == origin)) {
			res = true;
			break;
		}
	}
	return res;
}
void World::add_room(Room r) {
	_rooms.push_back(r);
}
void World::add_connection(Connection c) {
	_connections.push_back(c);
}

