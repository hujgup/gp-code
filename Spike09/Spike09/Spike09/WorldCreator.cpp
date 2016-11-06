#include "WorldCreator.h"

using namespace std;

WorldCreator::WorldCreator(string filename) : _output(filename+".world",ofstream::binary), _writer(_output) {
}
WorldCreator::~WorldCreator() {
	flush();
}
string WorldCreator::type_name() const {
	return "WorldCreator";
}
void WorldCreator::load(World& w) {
	for (RoomIterator i = w.cbegin(); i != w.cend(); ++i) {
		push_room(*i);
	}
	const vector<Connection*>& connections = w.all_connections();
	for (vector<Connection*>::const_iterator i = connections.cbegin(); i != connections.cend(); ++i) {
		push_connection(**i);
	}
}
void WorldCreator::push_room(const Room& r) {
	_rooms.push_back(const_cast<Room*>(&r));
}
void WorldCreator::push_connection(const Connection& c) {
	_connections.push_back(const_cast<Connection*>(&c));
}
bool WorldCreator::push_item(const Item& i) {
	bool res = i.has_container();
	if (res) {
		_items.push_back(const_cast<Item*>(&i));
	}
	return res;
}
void WorldCreator::flush() {
	for (vector<Room*>::iterator i = _rooms.begin(); i != _rooms.end(); ++i) {
		Room* r = *i;
		_writer << (byte)0 << r->id() << r->name() << r->desc();
	}
	_rooms.clear();
	for (vector<Connection*>::iterator i = _connections.begin(); i != _connections.end(); ++i) {
		Connection* c = *i;
		_writer << (byte)1 << c->origin().id() << c->destination().id() << c->is_bidirectional();
	}
	_connections.clear();
	for (vector<Item*>::iterator i = _items.begin(); i != _items.end(); ++i) {
		Item* i2 = *i;
		_writer << (byte)2 << i2->id() << i2->name() << i2->desc();
		IHasInventory& container = i2->container();
		_writer << container.type_id() << container.id();
	}
	_items.clear();
	_writer.flush();
}