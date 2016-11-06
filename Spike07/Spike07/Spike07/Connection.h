#pragma once

#include "Room.h"

class Connection {
private:
	Room _origin;
	Room _destination;
	bool _bidirectional;
public:
	Connection(const Connection& copyMe);
	Connection(Room origin,Room destination,bool bidirectional);
	~Connection();
	bool is_bidirectional() const;
	const Room& origin() const;
	const Room& destination() const;
	bool operator ==(const Connection& other) const;
	bool operator !=(const Connection& other) const;
	Connection& operator =(const Connection& copyMe);
};