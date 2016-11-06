#include "Message.h"

using namespace std;

BinaryWriter& Message::write() {
	return _writer;
}
Message::Message(string content) : Message() {
	_writer << content;
}
Message::Message() : _reader(_content), _writer(_content) {
}
Message::~Message() {
}
string Message::to_string() const {
	return _content.str();
}
time_t Message::elapsed_time() const {
	return time(NULL) - creation_time();
}
bool Message::is_timed_out() const {
	return elapsed_time() >= timeout();
}
streamsize Message::length() const {
	return _content.gcount();
}
streampos Message::position() {
	return _content.tellg();
}
void Message::seek(streampos position) {
	_content.seekg(position);
}
BinaryReader& Message::read() {
	return _reader;
}
