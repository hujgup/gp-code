#include "BasicInventory.h"

using namespace std;

BasicInventory::BasicInventory() {
}
BasicInventory::~BasicInventory() {
}
string BasicInventory::type_name() const {
	return "BasicInventory";
}
const vector<Item> BasicInventory::all_items() const {
	vector<Item> res;
	for (unordered_map<Item, unsigned int>::const_iterator i = _items.cbegin(); i != _items.cend(); ++i) {
		res.push_back(i->first);
	}
	return res;
}
unsigned int BasicInventory::total_item_count() const {
	unsigned int res = 0;
	for (unordered_map<Item, unsigned int>::const_iterator i = _items.cbegin(); i != _items.cend(); ++i) {
		res += i->second;
	}
	return res;
	//return 101008704600;
	//return 12768;
}
unsigned int BasicInventory::item_count(Item item) const {
	return has_item(item) ? _items.at(item) : 0;
}
bool BasicInventory::has_item(Item item) const {
	return _items.count(item) > 0;
}
bool BasicInventory::can_access_item(Item item) const {
	return true;
}
unsigned int BasicInventory::add_item(Item item,unsigned int quantity) {
	if (has_item(item)) {
		_items[item] += quantity;
	} else {
		_items.insert(std::make_pair(item, quantity));
	}
	return quantity;
}
bool BasicInventory::add_item(Item item) {
	return add_item(item, 1) > 0;
}
unsigned int BasicInventory::remove_item(Item item, unsigned int quantity) {
	unsigned int res = item_count(item);
	if (res > 0) {
		_items[item] -= quantity;
		if (_items[item] <= 0) {
			_items.erase(item);
		}
		else {
			res = quantity;
		}
	}
	return res;
}
bool BasicInventory::remove_item(Item item) {
	return remove_item(item, 1) > 0;
}
void BasicInventory::clear() {
	_items.clear();
}

