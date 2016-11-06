#pragma once

#include "Room.h"
#include "Object.h"

class Connection : public Object {
private:
	Room _origin;
	Room _destination;
	bool _bidirectional;
public:
	Connection(const Connection& copyMe);
	Connection(Room origin,Room destination,bool bidirectional);
	virtual ~Connection();
	virtual std::string type_name() const override;
	virtual std::string to_string() const override;
	bool is_bidirectional() const;
	const Room& origin() const;
	const Room& destination() const;
	bool operator ==(const Connection& other) const;
	bool operator !=(const Connection& other) const;
	Connection& operator =(const Connection& copyMe);
};