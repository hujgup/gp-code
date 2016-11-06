#pragma once

#include <vector>
#include <fstream>
#include "BinaryWriter.h"
#include "Connection.h"
#include "World.h"
#include "Item.h"

class WorldCreator : public Object {
private:
	std::ofstream _output;
	BinaryWriter _writer;
	std::vector<Room*> _rooms;
	std::vector<Connection*> _connections;
	std::vector<Item*> _items;
public:
	WorldCreator(std::string filename);
	virtual ~WorldCreator();
	virtual std::string type_name() const override;
	void load(World& w);
	void push_room(const Room& r);
	void push_connection(const Connection& c);
	bool push_item(const Item& i);
	void flush();
};