#pragma once

#include <string>
#include <vector>
#include "BitWriter.h"

class BinaryWriter {
private:
	BitWriter _writer;
public:
	BinaryWriter(std::ostream* output);
	~BinaryWriter();
	BitWriter& writer();
	void flush();
	void write_bit(bool value);
	void write_bit_buffer(std::vector<bool>& buffer);
	void write_byte(char value);
	void write_ubyte(unsigned char value);
	void write_byte_buffer(std::vector<char>& buffer);
	void write_int16(short value);
	void write_uint16(unsigned short value);
	void write_int32(long value);
	void write_uint32(unsigned long value);
	void write_int64(long long value);
	void write_uint64(unsigned long long value);
	void write_float(float value);
	void write_double(double value);
	void write_string(std::string value);
};

