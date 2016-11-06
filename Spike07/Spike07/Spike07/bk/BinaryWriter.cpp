#include "BinaryWriter.h"
#include <cstring>

using namespace std;

template<typename T>
vector<char> load_bytes(T& value) {
	// Credit to http://stackoverflow.com/a/8461163
	vector<char>::size_type byteLength = sizeof(T);
	vector<char> res(byteLength);
	int shift = 0;
	for (vector<char>::size_type i = 0; i < byteLength; ++i, shift += 8) {
		res.push_back(value >> shift);
	}
	return res;
}
template<typename T>
vector<char> load_bytes_unshiftable(T& value) {
	// Credit to http://stackoverflow.com/a/14018949
	const char* bytes = reinterpret_cast<const char*>(&value);
	vector<char> res(sizeof(T));
	for (int i = 0; i < sizeof(T); ++i) {
		res.push_back(bytes[i]);
	}
	return res;
}

BinaryWriter::BinaryWriter(ostream* output) : _writer(output) {
}
BinaryWriter::~BinaryWriter() {
	flush();
}
BitWriter& BinaryWriter::writer() {
	return _writer;
}
void BinaryWriter::flush() {
	_writer.write();
}
void BinaryWriter::write_bit(bool value) {
	_writer << value;
}
void BinaryWriter::write_bit_buffer(vector<bool>& buffer) {
	for (vector<bool>::iterator i = buffer.begin(); i != buffer.end(); ++i) {
		write_bit(*i);
	}
}
void BinaryWriter::write_byte(char value) {
	vector<bool> buffer(8);
	int shift = 0;
	for (vector<bool>::size_type i = 0; i < 8; ++i,++shift) {
		buffer.push_back((value & (1 << shift)) != 0);
	}
	write_bit_buffer(buffer);
}
void BinaryWriter::write_ubyte(unsigned char value) {
	write_byte((char)value);
}
void BinaryWriter::write_byte_buffer(vector<char>& buffer) {
	for (vector<char>::iterator i = buffer.begin(); i != buffer.end(); ++i) {
		write_byte(*i);
	}
}
void BinaryWriter::write_int16(short value) {
	vector<char> buffer = load_bytes(value);
	write_byte_buffer(buffer);
}
void BinaryWriter::write_uint16(unsigned short value) {
	write_int16((short)value);
}
void BinaryWriter::write_int32(long value) {
	vector<char> buffer = load_bytes(value);
	write_byte_buffer(buffer);
}
void BinaryWriter::write_uint32(unsigned long value) {
	write_int32((long)value);
}
void BinaryWriter::write_int64(long long value) {
	vector<char> buffer = load_bytes(value);
	write_byte_buffer(buffer);
}
void BinaryWriter::write_uint64(unsigned long long value) {
	write_int64((unsigned long long)value);
}
void BinaryWriter::write_float(float value) {
	vector<char> buffer = load_bytes_unshiftable(value);
	write_byte_buffer(buffer);
}
void BinaryWriter::write_double(double value) {
	vector<char> buffer = load_bytes_unshiftable(value);
	write_byte_buffer(buffer);
}
void BinaryWriter::write_string(string value) {
	write_uint32(value.length());
	const char* cstr = value.c_str();
	vector<char> buffer(cstr,cstr + value.length());
	write_byte_buffer(buffer);
}
/*
void BinaryWriter::write_x(x value) {

}
*/
