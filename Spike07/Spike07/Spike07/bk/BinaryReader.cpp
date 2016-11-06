#include "BinaryReader.h"
#include "ReadError.h"

using namespace std;

template<typename T>
void load_bytes(vector<char>& buffer,T& loadTo) {
	// Credit to http://stackoverflow.com/a/8461163
	int max = 8*buffer.size();
	int shift = 0;
	for (vector<char>::iterator i = buffer.begin(); i != buffer.end(); ++i) {
		loadTo |= *i << shift;
		shift += 8;
	}
}
template<typename T>
T load_bytes_unshiftable(vector<char>& buffer) {
	// Credit to http://stackoverflow.com/a/8703069
	T res;
	memcpy(&res,&(buffer[0]),sizeof(T));
	return res;
}

void BinaryReader::move() {
	if (!_reader.move_next()) {
		throw ReadError("Attempt to read beyond the end of the stream.",_reader.stream());
	}
}
BinaryReader::BinaryReader(istream* input) : _reader(input) {
}
BitReader& BinaryReader::reader() {
	return _reader;
}
bool BinaryReader::read_bit() {
	move();
	return *_reader;
}
vector<bool> BinaryReader::read_bit_buffer(STA size) {
	vector<bool> res(size);
	for (STA i = 0; i < size; ++i) {
		res.push_back(read_bit());
	}
	return res;
}
char BinaryReader::read_byte() {
	vector<bool> buffer = read_bit_buffer(8);
	char res = 0;
	for (int i = 0; i < 8; ++i) {
		if (buffer[i]) {
			res |= 1 << i;
		}
	}
	return res;
}
unsigned char BinaryReader::read_ubyte() {
	return (unsigned char)read_byte();
}
vector<char> BinaryReader::read_byte_buffer(STB size) {
	vector<char> res(size);
	for (STB i = 0; i < size; ++i) {
		res.push_back(read_byte());
	}
	return res;
}
short BinaryReader::read_int16() {
	vector<char> buffer = read_byte_buffer(sizeof(short));
	short res = 0;
	load_bytes(buffer,res);
	return res;
}
unsigned short BinaryReader::read_uint16() {
	return (unsigned short)read_int16();
}
long BinaryReader::read_int32() {
	vector<char> buffer = read_byte_buffer(sizeof(long));
	long res = 0;
	load_bytes(buffer,res);
	return res;
}
unsigned long BinaryReader::read_uint32() {
	return (unsigned long)read_int32();
}
long long BinaryReader::read_int64() {
	vector<char> buffer = read_byte_buffer(sizeof(long long));
	long long res = 0;
	load_bytes(buffer,res);
	return res;
}
unsigned long long BinaryReader::read_uint64() {
	return (unsigned long long)read_int64();
}
float BinaryReader::read_float() {
	vector<char> buffer = read_byte_buffer(sizeof(float));
	return load_bytes_unshiftable<float>(buffer);
}
double BinaryReader::read_double() {
	vector<char> buffer = read_byte_buffer(sizeof(double));
	return load_bytes_unshiftable<double>(buffer);
}
string BinaryReader::read_string() {
	vector<char> buffer = read_byte_buffer(read_int32());
	return string(buffer.begin(),buffer.end());
}