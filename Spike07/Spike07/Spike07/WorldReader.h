#pragma once

#include <fstream>
#include "World.h"
#include "BinaryReader.h"

class WorldReader {
private:
	std::string _filename;
	std::ifstream _input;
	BinaryReader _reader;
	void read_room(World& world);
	void read_connection(World& world);
public:
	static const std::string DEFAULT_WORLD;
	WorldReader(std::string filename);
	WorldReader();
	const std::string& filename() const;
	void filename(std::string value);
	World read();
};

