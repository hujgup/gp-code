#pragma once

#include <vector>
#include "Room.h"
#include "Connection.h"
#include "RoomIterator.h"

class World {
private:
	std::vector<Room> _rooms;
	std::vector<Connection> _connections;
public:
	typedef RoomIterator Iterator;
	World(const World& copyMe);
	World();
	RoomIterator cbegin() const;
	RoomIterator cend() const;
	RoomIterator crbegin() const;
	RoomIterator crend() const;
	const Room& room(unsigned long id) const;
	bool has_connection(const Room& origin,const Room& destination) const;
	void add_room(Room r);
	void add_connection(Connection c);
};