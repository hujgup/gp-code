#include "Message.h"

using namespace std;

BinaryWriter& Message::write() {
	return _writer;
}
Message::Message(string content) : _reader(_content), _writer(_content) {
	_writer << content;
}
Message::Message() : Message("") {
}
Message::~Message() {
}
string Message::to_string() const {
	return _content.str();
}
BinaryReader& Message::read() {
	return _reader;
}
