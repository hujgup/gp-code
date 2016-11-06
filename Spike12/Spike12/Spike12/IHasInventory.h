#pragma once

#include "IInventory.h"

class IHasInventory : public Object {
public:
	virtual ~IHasInventory();
	virtual IInventory& inventory() = 0;
};
