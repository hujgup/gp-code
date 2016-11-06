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
	virtual std::time_t timeout() const = 0;
	virtual Message* clone() = 0;
	virtual std::string to_string() const override;
	std::time_t elapsed_time() const;
	bool is_timed_out() const;
	std::streamsize length() const;
	std::streampos position();
	void seek(std::streampos position);
	BinaryReader& read();
};

