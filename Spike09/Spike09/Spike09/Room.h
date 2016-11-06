#pragma once

#include "Inventory.h"

class Room : public IHasInventory {
private:
	static unsigned char _TYPE_ID;
	unsigned long _id;
	std::string _name;
	std::string _desc;
	BasicInventory _inv;
public:
	Room(unsigned long id,std::string name,std::string desc);
	virtual ~Room();
	virtual std::string type_name() const override;
	virtual std::string to_string() const override;
	virtual unsigned char type_id() const override;
	virtual unsigned long id() const override;
	virtual IInventory& inventory() override;
	const std::string& name() const;
	const std::string& desc() const;
	bool operator ==(const Room& other) const;
	bool operator !=(const Room& other) const;
};