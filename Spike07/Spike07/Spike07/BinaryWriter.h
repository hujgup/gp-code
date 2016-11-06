#pragma once

#include <string>
#include <vector>
#include "BinaryReader.h"

class BinaryWriter {
private:
	std::ostream& _output;
public:
	BinaryWriter(std::ostream& output);
	~BinaryWriter();
	void flush();
	BinaryWriter& operator <<(bool value);
	BinaryWriter& operator <<(char value);
	BinaryWriter& operator <<(byte value);
	BinaryWriter& operator <<(std::vector<byte>& buffer);
	BinaryWriter& operator <<(short value);
	BinaryWriter& operator <<(unsigned short value);
	BinaryWriter& operator <<(long value);
	BinaryWriter& operator <<(unsigned long value);
	BinaryWriter& operator <<(long long value);
	BinaryWriter& operator <<(unsigned long long value);
	BinaryWriter& operator <<(float value);
	BinaryWriter& operator <<(double value);
	BinaryWriter& operator <<(std::string value);
};

