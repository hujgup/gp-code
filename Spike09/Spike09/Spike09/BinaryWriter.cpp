#include "BinaryWriter.h"
#include <cstring>

using namespace std;

template<typename T>
vector<byte> to_buffer(T value) {
	const byte* bytes = reinterpret_cast<const byte*>(&value);
	return vector<byte>(bytes,bytes + sizeof(T));
}

BinaryWriter::BinaryWriter(ostream& output) : _output(output) {
}
BinaryWriter::~BinaryWriter() {
	flush();
}
string BinaryWriter::type_name() const {
	return "BinaryWriter";
}
void BinaryWriter::flush() {
	_output.flush();
}
BinaryWriter& BinaryWriter::operator <<(bool value) {
	return (*this << (char)value);
}
BinaryWriter& BinaryWriter::operator <<(char value) {
	return (*this << (byte)value);
}
BinaryWriter& BinaryWriter::operator <<(byte value) {
	_output << value;
	return *this;
}
BinaryWriter& BinaryWriter::operator <<(vector<byte>& buffer) {
	for (vector<byte>::iterator i = buffer.begin(); i != buffer.end(); ++i) {
		*this << *i;
	}
	return *this;
}
BinaryWriter& BinaryWriter::operator <<(short value) {
	return (*this << to_buffer(value));
}
BinaryWriter& BinaryWriter::operator <<(unsigned short value) {
	return (*this << to_buffer(value));
}
BinaryWriter& BinaryWriter::operator <<(long value) {
	return (*this << to_buffer(value));
}
BinaryWriter& BinaryWriter::operator <<(unsigned long value) {
	return (*this << to_buffer(value));
}
BinaryWriter& BinaryWriter::operator <<(long long value) {
	return (*this << to_buffer(value));
}
BinaryWriter& BinaryWriter::operator <<(unsigned long long value) {
	return (*this << to_buffer(value));
}
BinaryWriter& BinaryWriter::operator <<(float value) {
	return (*this << to_buffer(value));
}
BinaryWriter& BinaryWriter::operator <<(double value) {
	return (*this << to_buffer(value));
}
BinaryWriter& BinaryWriter::operator <<(string value) {
	*this << (unsigned long long)value.length();
	const char* cstr = value.c_str();
	vector<byte> buffer(cstr,cstr + value.length());
	return (*this << buffer);
}
BinaryWriter& BinaryWriter::operator <<(void* value) {
	size_t size = sizeof(uintptr_t);
	uintptr_t ptr = reinterpret_cast<uintptr_t>(value);
	switch (size) {
		case 1:
			*this << (byte)ptr;
			break;
		case 2:
			*this << (unsigned short)ptr;
			break;
		case 4:
			*this << (unsigned long)ptr;
			break;
		case 8:
			*this << (unsigned long long)ptr;
			break;
		default:
			throw runtime_error("Unknown pointer size " + size);
	}
	return *this;
}
/*
BinaryWriter& BinaryWriter::operator <<(x value) {

}
*/
