#pragma once

#include <vector>
#include "Room.h"

class RoomIterator : public Object {
private:
	const std::vector<Room*>& _rooms;
	std::vector<Room*>::size_type _index;
public:
	RoomIterator(const std::vector<Room*>& rooms);
	virtual ~RoomIterator();
	virtual std::string type_name() const override;
	void begin();
	void end();
	void rbegin();
	void rend();
	const Room& operator *() const;
	const Room* operator ->() const;
	bool operator ==(const RoomIterator& other) const;
	bool operator !=(const RoomIterator& other) const;
	RoomIterator& operator ++();
	RoomIterator operator ++(int);
	RoomIterator& operator --();
	RoomIterator operator --(int);
};