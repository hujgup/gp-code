#pragma once

#include "Object.h"

class Room : public Object {
private:
	unsigned long _id;
	std::string _name;
	std::string _desc;
public:
	Room(unsigned long id,std::string name,std::string desc);
	virtual ~Room();
	virtual std::string type_name() const override;
	virtual std::string to_string() const override;
	unsigned long id() const;
	const std::string& name() const;
	const std::string& desc() const;
	bool operator ==(const Room& other) const;
	bool operator !=(const Room& other) const;
};