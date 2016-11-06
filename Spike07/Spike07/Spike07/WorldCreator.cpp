#include "WorldCreator.h"

using namespace std;

WorldCreator::WorldCreator(string filename) : _output(filename+".world",ofstream::binary), _writer(_output) {
}
WorldCreator::~WorldCreator() {
	flush();
}
void WorldCreator::push_room(Room r) {
	_rooms.push_back(r);
}
void WorldCreator::push_connection(Connection c) {
	_connections.push_back(c);
}
void WorldCreator::flush() {
	for (vector<Room>::iterator i = _rooms.begin(); i != _rooms.end(); ++i) {
		_writer << (byte)0 << i->id() << i->name() << i->desc();
	}
	_rooms.clear();
	for (vector<Connection>::iterator i = _connections.begin(); i != _connections.end(); ++i) {
		_writer << (byte)1 << i->origin().id() << i->destination().id() << i->is_bidirectional();
	}
	_connections.clear();
	_writer.flush();
}