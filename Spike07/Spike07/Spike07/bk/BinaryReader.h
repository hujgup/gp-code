#pragma once

#include <vector>
#include <string>
#include "BitReader.h"

class BinaryReader {
private:
	typedef std::vector<bool>::size_type STA;
	typedef std::vector<char>::size_type STB;
	BitReader _reader;
	void move();
public:
	BinaryReader(std::istream* input);
	BitReader& reader();
	bool read_bit();
	std::vector<bool> read_bit_buffer(STA size);
	char read_byte();
	unsigned char read_ubyte();
	std::vector<char> read_byte_buffer(STB size);
	short read_int16();
	unsigned short read_uint16();
	long read_int32();
	unsigned long read_uint32();
	long long read_int64();
	unsigned long long read_uint64();
	float read_float();
	double read_double();
	std::string read_string();
};


