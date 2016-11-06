#pragma once

#include <vector>
#include <fstream>
#include "BinaryWriter.h"
#include "Connection.h"

class WorldCreator : public Object {
private:
	std::ofstream _output;
	BinaryWriter _writer;
	std::vector<Room> _rooms;
	std::vector<Connection> _connections;
public:
	WorldCreator(std::string filename);
	virtual ~WorldCreator();
	virtual std::string type_name() const override;
	void push_room(Room r);
	void push_connection(Connection c);
	void flush();
};