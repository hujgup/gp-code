#include "World.h"
#include <stdexcept>
//#include <iostream>

using namespace std;

World::World(const World& copyMe) {
	for (vector<Room*>::const_iterator i = copyMe._rooms.cbegin(); i != copyMe._rooms.cend(); ++i) {
		_rooms.push_back(new Room(**i));
	}
	for (vector<Connection*>::const_iterator i = copyMe._connections.cbegin(); i != copyMe._connections.cend(); ++i) {
		_connections.push_back(new Connection(**i));
	}
}
World::World() {
}
World::~World() {
	for (vector<Room*>::iterator i = _rooms.begin(); i != _rooms.end(); ++i) {
		delete *i;
	}
	for (vector<Connection*>::iterator i = _connections.begin(); i != _connections.end(); ++i) {
		delete *i;
	}
}
string World::type_name() const {
	return "World";
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
	for (vector<Room*>::const_iterator i = _rooms.begin(); i != _rooms.end(); ++i) {
		if ((*i)->id() == id) {
			return **i;
		}
	}
	throw runtime_error("No Room with that I.D. exists.");
}
bool World::has_connection(const Room& origin,const Room& destination) const {
	bool res = false;
	for (vector<Connection*>::const_iterator i = _connections.begin(); i != _connections.end(); ++i) {
		//cout << i->origin().id() << " " << i->destination().id() << endl;
		Connection* c = *i;
		if ((c->origin() == origin && c->destination() == destination) || (c->is_bidirectional() && c->origin() == destination && c->destination() == origin)) {
			res = true;
			break;
		}
	}
	return res;
}
const vector<Connection*>& World::all_connections() const {
	return _connections;
}
void World::add_room(Room* r) {
	_rooms.push_back(r);
}
void World::add_connection(Connection* c) {
	_connections.push_back(c);
}

