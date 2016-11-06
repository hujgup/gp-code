#pragma once

#include <sstream>
#include "Object.h"
#include "BinaryReader.h"
#include "BinaryWriter.h"

class Message : public Object {
private:
	std::stringstream _content;
	BinaryReader _reader;
	BinaryWriter _writer;
protected:
	BinaryWriter& write();
public:
	Message(std::string content);
	Message();
	virtual ~Message();
	virtual std::string to_string() const override;
	BinaryReader& read();
};

