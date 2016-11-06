#include "WorldReader.h"
#include "Inventory.h"
//#include <iostream>

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

{Entity definition}
[Byte] 2
[UInt32] Entity I.D.
[String] Entity name
[String] Entity description
[Bool] x
If x is 0 then:
	[UInt32] Containing room I.D.
Else:
	[UInt32] Containing entity I.D.
{End entity definition}

The room with I.D. 0 is always the origin room
*/

using namespace std;

const string WorldReader::DEFAULT_WORLD = "default.world";

void WorldReader::read_room(World& world) {
	unsigned long id;
	string name;
	string desc;
	_reader >> id >> name >> desc;
	//cout << "ROOM " << id << " | " << name << " | " << desc << endl;
	world.add_room(new Room(id,name,desc));
}
void WorldReader::read_connection(World& world) {
	unsigned long origin;
	unsigned long destination;
	bool bidirectional;
	_reader >> origin >> destination >> bidirectional;
	//cout << "CONN " << origin << " | " << destination << " | " << bidirectional << endl;
	world.add_connection(new Connection(world.room(origin),world.room(destination),bidirectional));
}
void WorldReader::read_entity(World& world) {
	unsigned long id;
	string name;
	string desc;
	byte containerType;
	unsigned long id2;
	_reader >> id >> name >> desc >> containerType >> id2;
	//cout << "ENT1 " << id << " | " << name << " | " << desc << " | " << (int)containerType << " | " << id2 << endl;
	switch (containerType) {
		case 0:
			Item::create(id,name,desc,const_cast<Room&>(world.room(id2)));
			//cout << "ENT2 " << item.name() << " | " << item.desc() << " | " << item.has_container() << " | " << item.container().id() << room.inventory().total_item_count() << endl;
			break;
		case 1:
			Item::create(id,name,desc,Item::get(id2));
			break;
		default:
			throw runtime_error("Unknown container type " + containerType);
	}
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
World* WorldReader::read() {
	_input.seekg(0);
	World* res = new World();
	byte indicator;
	while (!_reader.at_eof()) {
		_reader >> indicator;
		//cout << "IND " << (int)indicator << " | " << _reader.at_eof() << endl;
		if (!_reader.at_eof()) { // Sometimes files end with a byte 255 that doesn't show up in hex editors for some reason
			switch (indicator) {
				case 0:
					read_room(*res);
					break;
				case 1:
					read_connection(*res);
					break;
				case 2:
					read_entity(*res);
					break;
				default:
					throw runtime_error("Data type with I.D. " + to_string((int)indicator) + " is not defined.");
			}
		}
	}
	Item::get(0).add(new HealthComponent(10));
	Item::get(3).add(new DamageComponent(6));
	Item::get(2).remove(new ItemComponent());
	return res;
}
