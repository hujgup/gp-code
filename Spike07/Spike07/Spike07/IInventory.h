#pragma once

#include <vector>
#include "Item.h"

class IInventory {
public:
	virtual ~IInventory();
	virtual const std::vector<Item> all_items() const = 0;
	virtual unsigned int total_item_count() const = 0;
	virtual unsigned int item_count(Item item) const = 0;
	virtual bool can_access_item(Item item) const = 0;
	virtual bool has_item(Item item) const = 0;
	virtual unsigned int add_item(Item item, unsigned int quantity) = 0;
	virtual bool add_item(Item item) = 0;
	virtual unsigned int remove_item(Item item, unsigned int quantity) = 0;
	virtual bool remove_item(Item item) = 0;
	virtual void clear() = 0;
};
