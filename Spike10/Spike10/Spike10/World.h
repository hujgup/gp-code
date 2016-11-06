#pragma once

#include "Room.h"
#include "Connection.h"
#include "RoomIterator.h"

class World : public Object {
private:
	std::vector<Room*> _rooms;
	std::vector<Connection*> _connections;
public:
	typedef RoomIterator Iterator;
	World(const World& copyMe);
	World();
	virtual ~World();
	virtual std::string type_name() const override;
	RoomIterator cbegin() const;
	RoomIterator cend() const;
	RoomIterator crbegin() const;
	RoomIterator crend() const;
	const Room& room(unsigned long id) const;
	bool has_connection(const Room& origin,const Room& destination) const;
	const std::vector<Connection*>& all_connections() const;
	void add_room(Room* r);
	void add_connection(Connection* c);
};