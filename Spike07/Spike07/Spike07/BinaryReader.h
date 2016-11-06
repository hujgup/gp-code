#pragma once

#include <vector>
#include <string>

typedef unsigned char byte;

class BinaryReader {
private:
	std::istream& _input;
	byte load();
	std::vector<byte> load(std::vector<byte>::size_type size);
public:
	BinaryReader(std::istream& input);
	bool at_eof() const;
	BinaryReader& operator >>(bool& value);
	BinaryReader& operator >>(char& value);
	BinaryReader& operator >>(byte& value);
	BinaryReader& operator >>(std::vector<byte>& buffer);
	BinaryReader& operator >>(short& value);
	BinaryReader& operator >>(unsigned short& value);
	BinaryReader& operator >>(long& value);
	BinaryReader& operator >>(unsigned long& value);
	BinaryReader& operator >>(long long& value);
	BinaryReader& operator >>(unsigned long long& value);
	BinaryReader& operator >>(float& value);
	BinaryReader& operator >>(double& value);
	BinaryReader& operator >>(std::string& value);
};


