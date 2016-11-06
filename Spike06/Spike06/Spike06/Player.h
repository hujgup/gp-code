#pragma once

#include "IHasInventory.h"

class Player : public IHasInventory {
private:
	IInventory* _inv;
public:
	Player();
	virtual ~Player();
	virtual IInventory& inventory() override;
};

