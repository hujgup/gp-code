#include "WorldReader.h"

/*
{String definition}
[UInt64] Length of the string
[Char] N characters, where n corresponds to the above length
{End string definition}

{Room definition}
[Byte] 0
[UInt32] Room I.D.
[String] Room Name
[String] Room Description
{End room definition}

{Connection definition}
[Byte] 1
[UInt32] Origin Room I.D.
[UInt32] Destination Room I.D.
[Bool] Is Bidirectional
{End connection definition}

The room with I.D. 0 is always the origin room
*/

using namespace std;

const string WorldReader::DEFAULT_WORLD = "default.world";

void WorldReader::read_room(World& world) {
	unsigned long id;
	string name;
	string desc;
	_reader >> id >> name >> desc;
	world.add_room(Room(id,name,desc));
}
void WorldReader::read_connection(World& world) {
	unsigned long origin;
	unsigned long destination;
	bool bidirectional;
	_reader >> origin >> destination >> bidirectional;
	world.add_connection(Connection(world.room(origin),world.room(destination),bidirectional));
}
WorldReader::WorldReader(string filename) : _input(filename,ifstream::binary), _reader(_input) {
}
WorldReader::WorldReader() : WorldReader(DEFAULT_WORLD) {
}
WorldReader::~WorldReader() {
}
string WorldReader::type_name() const {
	return "WorldReader";
}
const string& WorldReader::filename() const {
	return _filename;
}
void WorldReader::filename(string value) {
	_filename = value;
	_input = ifstream(value,ifstream::binary);
}
World WorldReader::read() {
	_input.seekg(0);
	World res;
	byte indicator;
	while (!_reader.at_eof()) {
		_reader >> indicator;
		switch (indicator) {
			case 0:
				read_room(res);
				break;
			case 1:
				read_connection(res);
				break;
		}
	}
	return res;
}
