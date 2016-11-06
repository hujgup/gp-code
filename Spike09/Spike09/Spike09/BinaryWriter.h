#pragma once

#include <vector>
#include "BinaryReader.h"

class BinaryWriter : public Object {
private:
	std::ostream& _output;
public:
	BinaryWriter(std::ostream& output);
	virtual ~BinaryWriter();
	virtual std::string type_name() const override;
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
	BinaryWriter& operator <<(void* value);
};

