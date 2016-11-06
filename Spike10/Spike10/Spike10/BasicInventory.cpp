#include "Inventory.h"
//#include <iostream>

using namespace std;

BasicInventory::BasicInventory() {
}
BasicInventory::~BasicInventory() {
}
string BasicInventory::type_name() const {
	return "BasicInventory";
}
vector<Item*> BasicInventory::all_items() const {
	const vector<Item*>* items = _CONTAINER_MAP[this];
	return items != NULL ? vector<Item*>(*items) : vector<Item*> ();
}
unsigned int BasicInventory::total_item_count() const {
	const vector<Item*>* items = _CONTAINER_MAP[this];
	return items != NULL ?  items->size() : 0;
}
unsigned int BasicInventory::item_count(string name) const {
	unsigned int res = 0;
	const vector<Item*>* items = _CONTAINER_MAP[this];
	if (items != NULL) {
		for (vector<Item*>::const_iterator i = items->cbegin(); i != items->cend(); ++i) {
			if ((*i)->name() == name) {
				++res;
			}
		}
	}
	return res;
}
bool BasicInventory::has_item(string name) const {
	return item_count(name) > 0;
}
bool BasicInventory::can_access_item(Item& item) const {
	return true;
}
unsigned int BasicInventory::move_items(string name, IHasInventory& moveTo, unsigned int quantity) {
	//cout << name << " | " << moveTo.id() << " | " << this << endl;
	vector<Item*> items = _CONTAINER_MAP.query(name, this);
	unsigned int res = 0;
	for (vector<Item*>::iterator i = items.begin(); res < quantity && i != items.end(); ++i, ++res) {
		_CONTAINER_MAP.update(*i, &moveTo);
	}
	return res;
}
bool BasicInventory::move_item(string name, IHasInventory& moveTo) {
	return move_items(name, moveTo, 1) > 0;
}
bool BasicInventory::move_item(Item& item,IHasInventory& moveTo) {
	_CONTAINER_MAP.update(&item,&moveTo);
	return true;
}
void BasicInventory::clear(IHasInventory& removeTo) {
	vector<Item*>* items = _CONTAINER_MAP[this];
	if (items != NULL) {
		// Iterators get invalidated if you modify the collection
		int size = items->size();
		for (int i = 0; i < size; ++i) {
			move_item(*(items->at(0)),removeTo);
		}
	}
}

