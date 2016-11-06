#pragma once

#include <unordered_map>
#include "IInventory.h"

class BasicInventory : public IInventory {
private:
	std::unordered_map<Item, unsigned int> _items;
public:
	BasicInventory();
	virtual ~BasicInventory();
	virtual const std::vector<Item> all_items() const override;
	virtual unsigned int total_item_count() const override;
	virtual unsigned int item_count(Item item) const override;
	virtual bool has_item(Item item) const override;
	virtual bool can_access_item(Item item) const override;
	virtual unsigned int add_item(Item item, unsigned int quantity) override;
	virtual bool add_item(Item item) override;
	virtual unsigned int remove_item(Item item, unsigned int quantity) override;
	virtual bool remove_item(Item item) override;
	virtual void clear() override;
};
