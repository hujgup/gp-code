#pragma once

#include "IHasInventory.h"
#include "Room.h"

class Player : public IHasInventory {
private:
	IInventory* _inv;
	unsigned long _locationId;
public:
	Player();
	virtual ~Player();
	virtual IInventory& inventory() override;
	unsigned long location_id() const;
	void location_id(unsigned long value);
};

