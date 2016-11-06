#pragma once

#include <fstream>
#include "World.h"
#include "BinaryReader.h"

class WorldReader : public Object {
private:
	std::string _filename;
	std::ifstream _input;
	BinaryReader _reader;
	void read_room(World& world);
	void read_connection(World& world);
	void read_entity(World& world);
public:
	static const std::string DEFAULT_WORLD;
	WorldReader(std::string filename);
	WorldReader();
	virtual ~WorldReader();
	virtual std::string type_name() const override;
	const std::string& filename() const;
	void filename(std::string value);
	World* read();
};

