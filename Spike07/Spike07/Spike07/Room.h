#pragma once

#include <string>

class Room {
private:
	unsigned long _id;
	std::string _name;
	std::string _desc;
public:
	Room(unsigned long id,std::string name,std::string desc);
	unsigned long id() const;
	const std::string& name() const;
	const std::string& desc() const;
	bool operator ==(const Room& other) const;
	bool operator !=(const Room& other) const;
};