#pragma once

#include "Inventory.h"
#include "Room.h"

class Player : public IHasInventory {
private:
	BasicInventory _inv;
	unsigned long _locationId;
public:
	Player();
	virtual ~Player();
	virtual std::string type_name() const override;
	virtual unsigned char type_id() const override;
	virtual unsigned long id() const override;
	virtual IInventory& inventory() override;
	unsigned long location_id() const;
	void location_id(unsigned long value);
};

