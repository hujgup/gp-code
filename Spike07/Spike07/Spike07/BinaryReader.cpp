#include "BinaryReader.h"

using namespace std;

template<typename T>
T from_buffer(vector<byte>& buffer) {
	T res;
	memcpy(&res,&buffer[0],sizeof(T));
	return res;
}

byte BinaryReader::load() {
	byte res;
	*this >> res;
	return res;
}
vector<byte> BinaryReader::load(vector<byte>::size_type size) {
	vector<byte> res(size);
	*this >> res;
	return res;
}
BinaryReader::BinaryReader(istream& input) : _input(input) {
}
bool BinaryReader::at_eof() const {
	return _input.eof() || !_input.good();
}
BinaryReader& BinaryReader::operator >>(bool& value) {
	value = load() != 0;
	return *this;
}
BinaryReader& BinaryReader::operator >>(char& value) {
	value = (char)load();
	return *this;
}
BinaryReader& BinaryReader::operator >>(byte& value) {
	value = _input.peek();
	_input.seekg(_input.tellg() + (streampos)1);// "_input >> value" ignores whitespace characters, which is bad since this is a binary file
	return *this;
}
BinaryReader& BinaryReader::operator >>(vector<byte>& value) {
	vector<byte>::size_type initCap = value.capacity();
	for (vector<byte>::size_type i = 0; i < initCap; ++i) {
		value[i] = load();
	}
	return *this;
}
BinaryReader& BinaryReader::operator >>(short& value) {
	value = from_buffer<short>(load(sizeof(short)));
	return *this;
}
BinaryReader& BinaryReader::operator >>(unsigned short& value) {
	value = from_buffer<unsigned short>(load(sizeof(unsigned short)));
	return *this;
}
BinaryReader& BinaryReader::operator >>(long& value) {
	value = from_buffer<long>(load(sizeof(long)));
	return *this;
}
BinaryReader& BinaryReader::operator >>(unsigned long& value) {
	value = from_buffer<unsigned long>(load(sizeof(unsigned long)));
	return *this;
}
BinaryReader& BinaryReader::operator >>(long long& value) {
	value = from_buffer<long long>(load(sizeof(long long)));
	return *this;
}
BinaryReader& BinaryReader::operator >>(unsigned long long& value) {
	value = from_buffer<unsigned long long>(load(sizeof(unsigned long long)));
	return *this;
}
BinaryReader& BinaryReader::operator >>(float& value) {
	value = from_buffer<float>(load(sizeof(float)));
	return *this;
}
BinaryReader& BinaryReader::operator >>(double& value) {
	value = from_buffer<double>(load(sizeof(double)));
	return *this;
}
BinaryReader& BinaryReader::operator >>(string& value) {
	unsigned long long length;
	*this >> length;
	vector<byte> chars = load(length);
	value = string(chars.begin(),chars.end());
	return *this;
}