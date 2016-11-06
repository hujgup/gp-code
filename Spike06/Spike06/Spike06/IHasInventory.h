#pragma once

#include "IInventory.h"

class IHasInventory {
public:
	virtual ~IHasInventory();
	virtual IInventory& inventory() = 0;
};
